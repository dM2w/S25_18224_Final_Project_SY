module fp_adder (
  input  logic clk,
  input  logic rst,   // synchronous reset
  input  logic [31:0] a,     // 32-bit IEEE-754 operand A
  input  logic [31:0] b,     // 32-bit IEEE-754 operand B
  input logic  data_valid,
  output logic [31:0] sum,   // 32-bit IEEE-754 result
  output logic error  // Error flag
);

  //==========================================================================
  // Operand Decomposition
  //==========================================================================
  // make each 32-bit operand into sign, exponent, and mantissa
  logic fa_sign_a, fa_sign_b;
  logic [7:0]  fa_exp_a,  fa_exp_b;
  logic [22:0] fa_man_a,  fa_man_b;
  
  assign fa_sign_a = a[31];
  assign fa_sign_b = b[31];
  assign fa_exp_a = a[30:23];
  assign fa_exp_b = b[30:23];
  assign fa_man_a = a[22:0];
  assign fa_man_b = b[22:0];
  
  //which operand is larger
  logic fa_a_bigger;
  assign fa_a_bigger = (fa_exp_a == fa_exp_b) ? (fa_man_a > fa_man_b) : (fa_exp_a > fa_exp_b);
  
  // the exponent difference
  logic [7:0] exp_delta;
  assign exp_delta = fa_a_bigger ? (fa_exp_a - fa_exp_b) : (fa_exp_b - fa_exp_a);
  
  // generate flags for infinity and NaN
  logic fa_inf_a, fa_inf_b, fa_nan_a, fa_nan_b;
  assign fa_inf_a = (fa_exp_a == 8'hff && fa_man_a == 23'b0);
  assign fa_inf_b = (fa_exp_b == 8'hff && fa_man_b == 23'b0);
  assign fa_nan_a = (fa_exp_a == 8'hff && fa_man_a != 23'b0);
  assign fa_nan_b = (fa_exp_b == 8'hff && fa_man_b != 23'b0);
  
  //==========================================================================
  // Floating–Point Adder Core
  //==========================================================================
  
  logic [23:0] ext_man_A, ext_man_B;
  assign ext_man_A = {1'b1, (fa_a_bigger ? fa_man_a : fa_man_b)};
  assign ext_man_B = {1'b1, (fa_a_bigger ? fa_man_b : fa_man_a)};
  
  // whether perform subtraction
  logic do_sub;
  assign do_sub = (fa_sign_a ^ fa_sign_b);
  
  // ceate a sticky–bit mask
  logic [23:0] sticky_mask;
  assign sticky_mask = 23'h7FFFFF >> (23 - exp_delta + 2);
  
  //-------------------------------------------------------------------------
  // FSM
  //-------------------------------------------------------------------------
  typedef enum logic [2:0] {
      IDLE, // initial wait state
      ALIGNMENT, // bit‐alignment and normalization
      EVEN_ROUND, // round-to-even
      RESULT_CHECK,// result validation
      EXCEPTION_INF, // handle infinite inputs
      EXCEPTION_INVALID,// handle NaN/invalid inputs
      FINISH  // pack final result
  } fpa_state_t;
  
  fpa_state_t cur_state, next_state;

  logic start_sig;
  assign start_sig = data_valid;
  
  // internal registers
  logic  res_sign, res_sign_nxt;
  logic [7:0]  res_exp, res_exp_nxt;
  logic [23:0] mant_res, mant_res_nxt;
  logic carry_flag, carry_flag_nxt;
  logic [7:0]  norm_exp, norm_exp_nxt;
  logic [23:0] norm_man, norm_man_nxt;
  
  // rounding signals
  logic [6:0] rnd_mode, rnd_mode_nxt;
  logic gbit, gbit_nxt;
  logic rbit, rbit_nxt;
  logic sbit, sbit_nxt;
  logic [6:0] DEFAULT_RND;
  assign DEFAULT_RND = 7'b1;
  
  // exception flags
  logic inv_op_flag, inv_op_flag_nxt;
  logic ovfl_flag, ovfl_flag_nxt;
  
  always_ff @(posedge clk) begin
    if (rst) begin
      res_sign <= 1'b0;
      res_exp <= 8'b0;
      mant_res<= 24'b0;
      carry_flag <= 1'b0;
      norm_exp <= 8'b0;
      norm_man <= 24'b0;
      rnd_mode <= 7'b0;
      gbit <= 1'b0;
      rbit <= 1'b0;
      sbit <= 1'b0;
      inv_op_flag <= 1'b0;
      ovfl_flag <= 1'b0;
      cur_state <= IDLE;
      sum <= 32'b0;
      // error <= 1'b0;
    end else begin
      res_sign <= res_sign_nxt;
      res_exp <= res_exp_nxt;
      mant_res <= mant_res_nxt;
      carry_flag <= carry_flag_nxt;
      norm_exp <= norm_exp_nxt;
      norm_man <= norm_man_nxt;
      rnd_mode <= rnd_mode_nxt;
      gbit <= gbit_nxt;
      rbit <= rbit_nxt;
      sbit <= sbit_nxt;
      inv_op_flag <= inv_op_flag_nxt;
      ovfl_flag <= ovfl_flag_nxt;
      cur_state <= next_state;
      if (next_state == FINISH) begin
        sum <= {res_sign, norm_exp, norm_man[22:0]};
        // error <= inv_op_flag;
      end
    end
  end
  
  //-------------------------------------------------------------------------
  // combinational state transition and output logic
  //-------------------------------------------------------------------------

  // to delete break
  logic found_msb;
  int j;
  always_comb begin
    res_sign_nxt = res_sign;
    res_exp_nxt = res_exp;
    mant_res_nxt = mant_res;
    carry_flag_nxt = carry_flag;
    norm_exp_nxt = norm_exp;
    norm_man_nxt = norm_man;
    rnd_mode_nxt = rnd_mode;
    gbit_nxt = gbit;
    rbit_nxt = rbit;
    sbit_nxt = sbit;
    inv_op_flag_nxt = inv_op_flag;
    ovfl_flag_nxt = ovfl_flag;
    next_state = cur_state;
    error = 'b0;
    found_msb = 1'b0;
    j=0;
    
    case (cur_state)
      EXCEPTION_INVALID: begin
        // a quiet NaN
        localparam logic [31:0] qnan_val = 32'h7fffffff;
        res_sign_nxt = qnan_val[31];
        norm_exp_nxt = qnan_val[30:23];
        norm_man_nxt = {1'b0, qnan_val[22:0]};
        inv_op_flag_nxt = 1'b1;
        ovfl_flag_nxt = 1'b0;
        next_state = FINISH;
      end

      EXCEPTION_INF: begin
        // one input is infinite
        res_sign_nxt = (fa_inf_a ? fa_sign_a : fa_sign_b);
        norm_exp_nxt= 8'hff;
        norm_man_nxt = 24'b0;
        next_state = FINISH;
      end

      FINISH: begin
        // pack the final result
        // sum = {res_sign, norm_exp, norm_man[22:0]};
        error = inv_op_flag;
        next_state = IDLE;
      end

      RESULT_CHECK: begin
        // check for exponent overflow
        ovfl_flag_nxt = 1'b0;
        if (norm_exp == 8'hff) begin
          res_sign_nxt = 1'b0;
          norm_man_nxt = 24'b0;
          ovfl_flag_nxt = 1'b1;
        end
        next_state = FINISH;
      end

      EVEN_ROUND: begin
        // round-to-even
        if (gbit && (rbit || sbit || norm_man[0])) begin
          norm_man_nxt = norm_man + 1;
          if (norm_man_nxt[22:0] == 23'h7fffff)
            norm_exp_nxt = res_exp + 1;
        end
        next_state = RESULT_CHECK;
      end

      ALIGNMENT: begin
        norm_exp_nxt = res_exp;
        norm_man_nxt = mant_res;
        gbit_nxt = 1'b0;
        rbit_nxt = 1'b0;
        sbit_nxt = 1'b0;
        inv_op_flag_nxt = 1'b0;

        if (carry_flag) begin
          norm_man_nxt = mant_res >> 1;
          norm_man_nxt[23] = 1'b1;
          norm_exp_nxt = res_exp + 1;

          gbit_nxt = norm_man[0];
          rbit_nxt = gbit;
          sbit_nxt = sbit | rbit;
        end else begin
          // int j;
          // found_msb = 1'b0;
          for (j = 23; j >= 0; j--) begin
            if (!found_msb && mant_res[j]) begin
              norm_man_nxt = mant_res << (23 - j);
              norm_exp_nxt = res_exp - (23 - j);
              found_msb = 1'b1;
            end
          end

          if (rnd_mode_nxt != 0) begin
            norm_man_nxt[0] = gbit;      // Save current gbit into LSB
            gbit_nxt = rbit;
            rbit_nxt = 1'b0;
            sbit_nxt = 1'b0;
          end
        end

        // next state
        if (rnd_mode_nxt == 7'd1)
          next_state = EVEN_ROUND;
        else
          next_state = RESULT_CHECK;
      end

      IDLE: begin
        if (rst) begin
          // sum ='b0;
          error = 1'b0;
        end else if (start_sig) begin
          res_sign_nxt = (fa_a_bigger ? fa_sign_a : fa_sign_b);
          res_exp_nxt  = (fa_a_bigger ? fa_exp_a  : fa_exp_b);
          {carry_flag_nxt, mant_res_nxt} = do_sub ? 
              ext_man_A - (ext_man_B >> exp_delta) : 
              ext_man_A + (ext_man_B >> exp_delta);
              
          rnd_mode_nxt = DEFAULT_RND;
          gbit_nxt = (ext_man_B >> (exp_delta - 1)) & 1'b1;
          rbit_nxt = (ext_man_B >> (exp_delta - 2)) & 1'b1;
          sbit_nxt = |(ext_man_B & sticky_mask);
          
          if ((fa_inf_a && fa_inf_b) || (fa_nan_a || fa_nan_b))
            next_state = EXCEPTION_INVALID;
          else if (fa_inf_a ^ fa_inf_b)
            next_state = EXCEPTION_INF;
          else
            next_state = ALIGNMENT;
        end
      end

      default: next_state = IDLE;
    endcase
  end

endmodule
