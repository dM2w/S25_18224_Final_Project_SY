module fp_subtract (
  input  logic clk,
  input  logic rst,   // Synchronous reset
  input  logic [31:0] a,     // 32-bit IEEE-754 operand A
  input  logic [31:0] b,     // 32-bit IEEE-754 operand B
  input logic data_valid,
  output logic [31:0] diff,  // 32-bit IEEE-754 result (a - b)
  output logic error  // error flag (set for invalid operands)
);

  //==========================================================================
  // Operand Decomposition
  //==========================================================================
  // compute a - b as a + (-b). invert the sign of b
  logic        sub_sign_a, sub_sign_b;
  logic [7:0]  sub_exp_a,  sub_exp_b;
  logic [22:0] sub_man_a,  sub_man_b;
  
  assign sub_sign_a = a[31];
  // invert b's sign to form the negative
  assign sub_sign_b = ~b[31]; 
  assign sub_exp_a  = a[30:23];
  assign sub_exp_b  = b[30:23];
  assign sub_man_a  = a[22:0];
  assign sub_man_b  = b[22:0];
  
  // which operand is larger by magnitude
  logic sub_a_bigger;
  assign sub_a_bigger = (sub_exp_a == sub_exp_b) ? (sub_man_a > sub_man_b) : (sub_exp_a > sub_exp_b);
  
  // the absolute difference in exponents
  logic [7:0] exp_diff;
  assign exp_diff = sub_a_bigger ? (sub_exp_a - sub_exp_b) : (sub_exp_b - sub_exp_a);
  
  logic sub_inf_a, sub_inf_b, sub_nan_a, sub_nan_b;
  assign sub_inf_a = (sub_exp_a == 8'hff && sub_man_a == 23'b0);
  assign sub_inf_b = (sub_exp_b == 8'hff && sub_man_b == 23'b0);
  assign sub_nan_a = (sub_exp_a == 8'hff && sub_man_a != 23'b0);
  assign sub_nan_b = (sub_exp_b == 8'hff && sub_man_b != 23'b0);
  
  //==========================================================================
  // Floating–Point Subtraction Core (similar to add logic)
  //==========================================================================

  logic [23:0] ext_man_A, ext_man_B;
  assign ext_man_A = {1'b1, (sub_a_bigger ? sub_man_a : sub_man_b)};
  assign ext_man_B = {1'b1, (sub_a_bigger ? sub_man_b : sub_man_a)};
  
  // Determine the operation mode. For subtraction we always add the modified B.
  logic sub_op_subtract;
  assign sub_op_subtract = (sub_sign_a ^ sub_sign_b); // This now reflects subtraction since b's sign was inverted.
  
  // Create a mask to extract a sticky bit (used for rounding).
  logic [23:0] stick_mask;
  assign stick_mask = 23'h7FFFFF >> (23 - exp_diff + 2);
  
  //-------------------------------------------------------------------------
  // State machine
  //-------------------------------------------------------------------------
  typedef enum logic [2:0] {
    START_UP,
    SHIFT_ALIGN,
    EVEN_ADJUST,
    FINAL_CHECK,
    SPECIAL_INF,
    SPECIAL_ERR,
    OUTPUT_READY
  } sub_state_t;
  
  sub_state_t cur_st, nxt_st;
  
  //internal registers
  logic res_sign, res_sign_nxt;
  logic [7:0]  res_exp,  res_exp_nxt;
  logic [23:0] res_man,  res_man_nxt;
  logic carry_out, carry_out_nxt;
  logic [7:0]  norm_exp, norm_exp_nxt;
  logic [23:0] norm_man, norm_man_nxt;
  
  // rounding
  logic [6:0]  rnd_sel, rnd_sel_nxt;
  logic guard,   guard_nxt;
  logic round_bit, round_bit_nxt;
  logic  sticky,  sticky_nxt;
  localparam [6:0] DEF_RND = 7'd1;
  
  // Exception flags.
  logic invalid_flag, invalid_flag_nxt;
  logic overflow_flag, overflow_flag_nxt;
  
  //-------------------------------------------------------------------------
  // Synchronous state update here
  //-------------------------------------------------------------------------
  always_ff @(posedge clk) begin
    if (rst) begin
      res_sign <= 1'b0;
      res_exp <= 8'b0;
      res_man <= 24'b0;
      carry_out <= 1'b0;
      norm_exp <= 8'b0;
      norm_man <= 24'b0;
      rnd_sel <= 7'b0;
      guard <= 1'b0;
      round_bit <= 1'b0;
      sticky <= 1'b0;
      invalid_flag <= 1'b0;
      overflow_flag <= 1'b0;
      cur_st <= START_UP;
    end else begin
      res_sign <= res_sign_nxt;
      res_exp <= res_exp_nxt;
      res_man <= res_man_nxt;
      carry_out <= carry_out_nxt;
      norm_exp <= norm_exp_nxt;
      norm_man <= norm_man_nxt;
      rnd_sel <= rnd_sel_nxt;
      guard <= guard_nxt;
      round_bit <= round_bit_nxt;
      sticky <= sticky_nxt;
      invalid_flag <= invalid_flag_nxt;
      overflow_flag <= overflow_flag_nxt;
      cur_st <= nxt_st;
    end
  end
  
  //-------------------------------------------------------------------------
  // Combinational state transition and output
  //-------------------------------------------------------------------------
  logic start_sig;
  assign start_sig = data_valid;
  // for reomve break
  logic found_msb;
  found_msb = 1'b0;
  always_comb begin
    res_sign_nxt    = res_sign;
    res_exp_nxt     = res_exp;
    res_man_nxt     = res_man;
    carry_out_nxt   = carry_out;
    norm_exp_nxt    = norm_exp;
    norm_man_nxt    = norm_man;
    rnd_sel_nxt     = rnd_sel;
    guard_nxt       = guard;
    round_bit_nxt   = round_bit;
    sticky_nxt      = sticky;
    invalid_flag_nxt = invalid_flag;
    overflow_flag_nxt = overflow_flag;
    nxt_st = cur_st;
    
    case (cur_st)
      SPECIAL_ERR: begin
        // a quiet NaN
        localparam logic [31:0] qnan = 32'h7fffffff;
        res_sign_nxt = qnan[31];
        norm_exp_nxt = qnan[30:23];
        norm_man_nxt = {1'b0, qnan[22:0]};
        invalid_flag_nxt = 1'b1;
        overflow_flag_nxt = 1'b0;
        nxt_st = OUTPUT_READY;
      end

      SPECIAL_INF: begin
        // infinite
        res_sign_nxt = (sub_inf_a ? sub_sign_a : sub_sign_b);
        norm_exp_nxt = 8'hff;
        norm_man_nxt = 24'b0;
        nxt_st = OUTPUT_READY;
      end

      OUTPUT_READY: begin
         // final pack result
         diff = {res_sign, norm_exp, norm_man[22:0]};
         error = invalid_flag;
         nxt_st = START_UP;
      end

      FINAL_CHECK: begin
        // check for exponent overflow
        overflow_flag_nxt = 1'b0;
        if (norm_exp === 8'hff) begin
          res_sign_nxt = 1'b0;
          norm_man_nxt = 24'b0;
          overflow_flag_nxt = 1'b1;
        end
        nxt_st = OUTPUT_READY;
      end

      EVEN_ADJUST: begin
        if (guard && (round_bit || sticky || norm_man[0])) begin
          norm_man_nxt = norm_man + 1;
          if (norm_man_nxt[22:0] == 23'h7fffff)
            norm_exp_nxt = res_exp + 1;
        end
        nxt_st = FINAL_CHECK;
      end

      SHIFT_ALIGN: begin
        // alignment and normalization
        norm_exp_nxt = res_exp;
        norm_man_nxt = res_man;
        guard_nxt    = guard;
        round_bit_nxt = round_bit;
        sticky_nxt   = sticky;
        
        if (carry_out) begin
          // if an extra carry, right shift
          norm_man_nxt = res_man >> 1;
          norm_man_nxt[23] = 1'b1;
          norm_exp_nxt = res_exp + 1;
          guard_nxt = norm_man[0];
          round_bit_nxt = guard;
          sticky_nxt = sticky | round_bit;
        end else begin
          int k;
          for (k = 23; k >= 0; k--) begin
            if (!found_msb&&res_man[k]) begin
              norm_man_nxt = res_man << (23 - k);
              norm_exp_nxt = res_exp - (23 - k);
              // break;
              found_msb = 1'b1;
            end
          end
          if (rnd_sel_nxt != 0) begin
            norm_man_nxt[0] = guard_nxt;
            guard_nxt = round_bit_nxt;
            round_bit_nxt = 1'b0;
          end
        end
        invalid_flag_nxt = 1'b0;
        if (rnd_sel_nxt == 7'd1)
          nxt_st = EVEN_ADJUST;
        else
          nxt_st = FINAL_CHECK;
      end

      START_UP: begin
        if (rst) begin
          diff = 32'b0;
          error = 1'b0;
        end else if (start_sig) begin
          res_sign_nxt = (sub_a_bigger ? sub_sign_a : sub_sign_b);
          res_exp_nxt  = (sub_a_bigger ? sub_exp_a  : sub_exp_b);
          {carry_out_nxt, res_man_nxt} = sub_op_subtract ? 
            ext_man_A - (ext_man_B >> exp_diff) : 
            ext_man_A + (ext_man_B >> exp_diff);
              
          rnd_sel_nxt = DEF_RND;
          guard_nxt = (ext_man_B >> (exp_diff - 1)) & 1'b1;
          round_bit_nxt = (ext_man_B >> (exp_diff - 2)) & 1'b1;
          sticky_nxt = |(ext_man_B & stick_mask);
          
          if ((sub_inf_a && sub_inf_b) || (sub_nan_a || sub_nan_b))
            nxt_st = SPECIAL_ERR;
          else if (sub_inf_a ^ sub_inf_b)
            nxt_st = SPECIAL_INF;
          else
            nxt_st = SHIFT_ALIGN;
        end
      end

      default: nxt_st = START_UP;
    endcase
  end

endmodule
