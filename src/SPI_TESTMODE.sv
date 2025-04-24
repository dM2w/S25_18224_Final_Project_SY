`timescale 1ns/1ps
module fpu_spi_test #(
  parameter integer FPU_LATENCY = 12,
  parameter TEST_MODE = 1
)(
  input  logic        clk,
  input  logic        rst,
  // SPI interface (mode‑0):
  input  logic        SCLK,       // serial clock from master
  input  logic        CS_N,       // chip‑select (active low)
  input  logic        MOSI,       // master→slave data
  output logic        MISO,       // slave→master data

  // -----------------------------------------------------------------------
  // !! test ports!!
  // -----------------------------------------------------------------------
  input  logic        tb_valid, 
  input  logic [1:0]  tb_opcode,
  input  logic [31:0] tb_a,
  input  logic [31:0] tb_b
);

  typedef enum logic [1:0] {
    OP_ADD = 2'b00,
    OP_SUB = 2'b01,
    OP_MUL = 2'b10,
    OP_DIV = 2'b11
  } op_t;

  logic [65:0] rx_shift;
  logic [6:0]  bit_cnt;
  logic frame_done;

  always_ff @(posedge SCLK, posedge CS_N) begin
    if (CS_N) begin
      bit_cnt    <= 0;
      frame_done <= 0;
    end else begin
      rx_shift <= {rx_shift[64:0], MOSI};
      if (bit_cnt == 7'd65) begin
        frame_done <= 1;
        bit_cnt    <= 0;
      end else begin
        bit_cnt <= bit_cnt + 1;
      end
    end
  end

 
  op_t  opcode;
  logic [31:0] op_a, op_b;
  always_ff @(posedge clk) begin
    if (rst) begin
      opcode <= OP_ADD;
      op_a <= 32'h0;
      op_b <= 32'h0;
    end else if (TEST_MODE) begin
      opcode <= op_t'(tb_opcode);
      op_a <= tb_a;
      op_b <= (tb_opcode == OP_SUB ? ~tb_b + 1 : tb_b);
    end else if (frame_done) begin
      opcode <= op_t'(rx_shift[65:64]);
      op_a <= rx_shift[63:32];
      op_b <= rx_shift[31: 0];
    end
  end

  //--------------------------------------------------------------------------
  // 2) Instantiate FPU
  //--------------------------------------------------------------------------
  logic f_add_valid, f_mul_valid, f_div_valid;
  logic [31:0] f_add_res, f_mul_res, f_div_res;
  logic e_add, e_mul, e_div;

  fp_adder U_ADD (
    .clk        (clk),
    .rst        (rst),
    .a          (op_a),
    .b          (op_b),
    .data_valid (f_add_valid),
    .sum        (f_add_res),
    .error      (e_add)
  );

  fp_mult U_MUL (
    .clk        (clk),
    .rst        (rst),
    .a          (op_a),
    .b          (op_b),
    .data_valid (f_mul_valid),
    .mult       (f_mul_res),
    .error      (e_mul)
  );

  fp_div U_DIV (
    .clk        (clk),
    .rst        (rst),
    .a          (op_a),
    .b          (op_b),
    .data_valid (f_div_valid),
    .div        (f_div_res),
    .error      (e_div)
  );

  //--------------------------------------------------------------------------
  // 3) Control FSM to ex one op and wait FPU_LATENCY cycles
  //--------------------------------------------------------------------------
  typedef enum logic [1:0] {
    S_IDLE = 2'd0,
    S_WAIT = 2'd1,
    S_SEND = 2'd2
  } state_t;

  state_t state, state_n;
  logic [31:0] wait_cnt;
  logic [31:0] fpu_out;
  logic fpu_err;

  // strobe data_valid for exactly one clk when we start an operation
  always_ff @(posedge clk) begin
    if (rst) begin
      f_add_valid <= 0;
      f_mul_valid <= 0;
      f_div_valid <= 0;
    end else if (TEST_MODE) begin
      f_add_valid <= tb_valid && (tb_opcode == OP_ADD  || tb_opcode == OP_SUB);
      f_mul_valid <= tb_valid && (tb_opcode == OP_MUL);
      f_div_valid <= tb_valid && (tb_opcode == OP_DIV);
    end else begin
      f_add_valid <= (state == S_IDLE && frame_done &&
                      (opcode == OP_ADD || opcode == OP_SUB));
      f_mul_valid <= (state == S_IDLE && frame_done && opcode == OP_MUL);
      f_div_valid <= (state == S_IDLE && frame_done && opcode == OP_DIV);
    end
  end

  //  latency counter
  always_ff @(posedge clk) begin
    if (rst)
      wait_cnt <= 0;
    else if (state == S_IDLE && (TEST_MODE ? tb_valid : frame_done))
      wait_cnt <= FPU_LATENCY;
    else if (state == S_WAIT && wait_cnt != 0)
      wait_cnt <= wait_cnt - 1;
  end

  // state register
  always_ff @(posedge clk or posedge rst) begin
    if (rst)
      state <= S_IDLE;
    else
      state <= state_n;
  end


  always_comb begin
    state_n  = state;
    fpu_out  = 32'd0;
    fpu_err  = 1'b0;

    case (state)
      S_IDLE:
        if (TEST_MODE ? tb_valid : frame_done) begin
          unique case (opcode)
            OP_ADD, OP_SUB: begin 
              fpu_out = f_add_res; 
              fpu_err = e_add; 
            end
            OP_MUL: begin 
              fpu_out = f_mul_res; 
              fpu_err = e_mul; 
            end
            OP_DIV: begin 
              fpu_out = f_div_res; 
              fpu_err = e_div; 
            end
          endcase
          state_n = S_WAIT;
        end

      S_WAIT:
        if (wait_cnt == 0)
          state_n = S_SEND;

      S_SEND:
        if (CS_N)
          state_n = S_IDLE;
    endcase
  end

  //--------------------------------------------------------------------------
  // 4) Shift‑out {err, fpu_out[31:0]}
  //--------------------------------------------------------------------------
  logic [1:0]  prev_state;
  logic [32:0] tx_shift;

  always_ff @(posedge clk or posedge rst) begin
    if (rst)
      prev_state <= S_IDLE;
    else
      prev_state <= state;
  end

  always_ff @(posedge clk or posedge rst) begin
    if (rst)
      tx_shift <= 33'd0;
    else if (!TEST_MODE && state == S_SEND && prev_state == S_WAIT)
      tx_shift <= {fpu_err, fpu_out};
  end

  always_ff @(negedge SCLK) begin
    if (!CS_N && state == S_SEND && !TEST_MODE) begin
      MISO     <= tx_shift[32];
      tx_shift <= {tx_shift[31:0], 1'b0};
    end
  end

endmodule
