module fpu_spi #(
    parameter integer FPU_LATENCY = 12
)(
    input  logic        clk,        // system clock for FPU
    input  logic        rst,        // synchronous reset
    input  logic        SCLK,       // serial clock from master
    input  logic        CS_N,       // chip‑select (active low)
    input  logic        MOSI,       // master→slave data
    output logic        MISO        // slave→master data
);

    //--------------------------------------------------------------------------
    // 1) Frame‑in: shift 66 bits (2‑bit opcode + 32‑bit A + 32‑bit B)
    //--------------------------------------------------------------------------
    typedef enum logic [1:0] {
        OP_ADD = 2'b00,
        OP_SUB = 2'b01,
        OP_MUL = 2'b10,
        OP_DIV = 2'b11
    } op_t;

    logic [65:0] rx_shift;
    logic [6:0]  bit_cnt;
    // logic frame_temp;
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

    // once frame_done, A B opcode to reg
    op_t  opcode;
    logic [31:0] op_a, op_b;
    always_ff @(posedge clk) begin
        if (rst) begin
            opcode <= OP_ADD;
            op_a <= 32'h0;
            op_b <= 32'h0;
        end else if (frame_done) begin
            opcode <= op_t'(rx_shift[65:64]);
            op_a <= rx_shift[63:32];
            op_b <= rx_shift[31: 0];
        end
    end


    //--------------------------------------------------------------------------
    // 2) Instantiate the three FPUs (realize sub can reuse add)
    //--------------------------------------------------------------------------
    logic  f_add_valid, f_mul_valid, f_div_valid;
    logic [31:0] f_add_res, f_mul_res, f_div_res;
    logic e_add, e_mul, e_div;

    // instantiation of the fpu modules
    fp_adder U_ADD (
        .clk        (clk),
        .rst        (rst),
        .a          (op_a),
        .b          (opcode == OP_SUB ? ~op_b + 1 : op_b),
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
    // 3) Control FSM to fire one op and wait FPU_LATENCY cycles
    //--------------------------------------------------------------------------
    typedef enum logic [1:0] {
        S_IDLE = 2'd0,
        S_WAIT = 2'd1,
        S_SEND = 2'd2
    } state_t;

    state_t  state, state_n;
    logic [31:0] wait_cnt;
    logic [31:0]fpu_out;
    logic fpu_err;

    // strobe data_valid for exactly one clk when start an operation
    always_ff @(posedge clk) begin
        if (rst) begin
            f_add_valid <= 0;
            f_mul_valid <= 0;
            f_div_valid <= 0;
        end else begin
            f_add_valid <= (state == S_IDLE && frame_done &&
                            (opcode == OP_ADD || opcode == OP_SUB));
            f_mul_valid <= (state == S_IDLE && frame_done && opcode == OP_MUL);
            f_div_valid <= (state == S_IDLE && frame_done && opcode == OP_DIV);
        end
    end

    // counter down
    always_ff @(posedge clk) begin
        if (rst)
            wait_cnt <= 0;
        else if (state == S_IDLE && frame_done)
            wait_cnt <= FPU_LATENCY;
        else if (state == S_WAIT && wait_cnt != 0)
            wait_cnt <= wait_cnt - 1;
    end

    // state reg
    always_ff @(posedge clk or posedge rst) begin
        if (rst)
            state <= S_IDLE;
        else
            state <= state_n;
    end

    // next state, FPU’s result
    always_comb begin
        state_n  = state;
        fpu_out  = 32'd0;
        fpu_err  = 1'b0;

        case (state)
            S_IDLE: 
                if (frame_done) begin
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

            S_WAIT: if (wait_cnt == 0) state_n = S_SEND;

            S_SEND: if (CS_N) state_n = S_IDLE;
            endcase
    end


    //--------------------------------------------------------------------------
    // 4) Shift‑out {err, fpu_out[31:0]} on SCLK
    //--------------------------------------------------------------------------
    logic [1:0]  prev_state;
    logic [32:0] tx_shift;

    // detect WAIT to SEND
    always_ff @(posedge clk, posedge rst) begin
        if (rst)
            prev_state <= S_IDLE;
        else
            prev_state <= state;
    end

    // on the cycle enter SEND,load the shift register
    always_ff @(posedge clk, posedge rst) begin
        if (rst)
            tx_shift <= 33'd0;
        else if (state == S_SEND && prev_state == S_WAIT)
            tx_shift <= {fpu_err, fpu_out};
    end

    // shift one bit out per falling SCLK
    always_ff @(negedge SCLK) begin
        if (!CS_N && state == S_SEND) begin
            MISO<= tx_shift[32];
            tx_shift <={tx_shift[31:0], 1'b0};
        end
    end

endmodule
