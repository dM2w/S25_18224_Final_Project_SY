module fp_mult (
   input  logic clk,
   input  logic rst,
   input  logic [31:0]  a,
   input  logic [31:0]  b,
   input  logic data_valid,
   output logic [31:0]  mult,
   output logic error
);

   //====================================================
   // Operand Decomposition
   //====================================================
   logic         mul_sign_a, mul_sign_b;
   logic  [7:0]  mul_exp_a,  mul_exp_b;
   logic [22:0]  mul_frac_a, mul_frac_b;
   
   assign mul_sign_a = a[31];
   assign mul_exp_a = a[30:23];
   assign mul_frac_a = a[22:0];
   
   assign mul_sign_b = b[31];
   assign mul_exp_b = b[30:23];
   assign mul_frac_b = b[22:0];
   
   logic mul_infty_a, mul_infty_b, mul_nan_a, mul_nan_b, mul_zero_a, mul_zero_b;

   assign mul_infty_a = (mul_exp_a == 8'hff) && (mul_frac_a == 23'b0);
   assign mul_infty_b = (mul_exp_b == 8'hff) && (mul_frac_b == 23'b0);
   assign mul_nan_a = (mul_exp_a == 8'hff) && (mul_frac_a != 23'b0);
   assign mul_nan_b = (mul_exp_b == 8'hff) && (mul_frac_b != 23'b0);
   assign mul_zero_a = (mul_exp_a == 8'b0)  && (mul_frac_a == 23'b0);
   assign mul_zero_b = (mul_exp_b == 8'b0)  && (mul_frac_b == 23'b0);

   logic [23:0] mul_frac_ext_a, mul_frac_ext_b;
   assign mul_frac_ext_a = {1'b1, mul_frac_a};
   assign mul_frac_ext_b = {1'b1, mul_frac_b};

   //====================================================
   // FSM
   //====================================================
   typedef enum logic [3:0] {
         ST_LAT,
         ST_SP,
         ST_MUL,
         ST_NORM,
         ST_RND,
         ST_VAL,
         ST_OUT,
         ST_INF,
         ST_ERR
   } state_t;
   
   state_t state, next_state;
   
   logic  m_sign, m_sign_next;
   logic [8:0] m_exp, m_exp_next;
   logic [47:0] m_prod, m_prod_next;
   logic [23:0] m_norm, m_norm_next;
   logic [8:0] m_norm_exp, m_norm_exp_next;
   logic [6:0] m_rnd, m_rnd_next;
   logic  m_guard, m_guard_next;
   logic  m_rbit, m_rbit_next;
   logic  m_sticky, m_sticky_next;
   logic  m_invalid, m_invalid_next;
   logic  m_overflow, m_overflow_next;
   
   logic [6:0] DEF_RND;
   assign DEF_RND = 7'b1;
   logic [31:0] mult_reg;

   always_ff @(posedge clk) begin
      if (rst) begin
         m_sign <= 1'b0;
         m_exp <= 9'b0;
         m_prod <= 48'b0;
         m_norm <= 24'b0;
         m_norm_exp <= 9'b0;
         m_guard <= 1'b0;
         m_rbit <= 1'b0;
         m_sticky <= 1'b0;
         m_rnd <= DEF_RND;
         m_invalid <= 1'b0;
         m_overflow <= 1'b0;
         state <= ST_LAT;
         mult_reg <= 32'b0;
      end else begin
         m_sign  <= m_sign_next;
         m_exp <= m_exp_next;
         m_prod<= m_prod_next;
         m_norm <= m_norm_next;
         m_norm_exp <= m_norm_exp_next;
         m_guard <= m_guard_next;
         m_rbit <= m_rbit_next;
         m_sticky <= m_sticky_next;
         m_rnd <= m_rnd_next;
         m_invalid <= m_invalid_next;
         m_overflow <= m_overflow_next;
         state <= next_state;
         // go to final state
         if (state == ST_OUT) begin
            mult_reg <= {m_sign, m_norm_exp_next[7:0], m_norm_next[22:0]};
         end
      end
   end

   logic [31:0] qnan;
   assign qnan = 'b0;
   always_comb begin
      m_sign_next = m_sign;
      m_exp_next = m_exp;
      m_prod_next = m_prod;
      m_norm_next = m_norm;
      m_norm_exp_next = m_norm_exp;
      m_guard_next = m_guard;
      m_rbit_next= m_rbit;
      m_sticky_next = m_sticky;
      m_rnd_next = m_rnd;
      m_invalid_next = m_invalid;
      m_overflow_next = m_overflow;
      next_state = state;

      case (state)
         ST_LAT: if (data_valid) begin
            m_sign_next = mul_sign_a ^ mul_sign_b;
            m_exp_next = (mul_exp_a + mul_exp_b) - 9'd127;
            m_rnd_next = DEF_RND;
            next_state = ST_SP;
         end

         ST_SP: begin
            if (mul_nan_a || mul_nan_b)
               next_state = ST_ERR;
            // else if (mul_infty_a || mul_infty_b)
            else if ((mul_infty_a || mul_infty_b) && !(mul_zero_a || mul_zero_b))
               next_state = ST_INF;
            else if (mul_zero_a || mul_zero_b) begin
               m_sign_next = mul_sign_b;
               m_exp_next = 9'b0;
               m_norm_next = 24'b0;
               m_norm_exp_next = 9'b0;
               next_state = ST_OUT;
            end else begin
               next_state = ST_MUL;
            end
         end

         ST_MUL: begin
            m_prod_next = mul_frac_ext_a * mul_frac_ext_b;
            next_state  = ST_NORM;
         end

         ST_NORM: begin
            if (m_prod[47]) begin
               m_norm_next = m_prod[46:23];
               m_norm_exp_next = m_exp + 1;
               m_guard_next = m_prod[22];
               m_rbit_next= m_prod[21];
               m_sticky_next= |m_prod[20:0];
            end else begin
               m_norm_next = m_prod[45:22];
               m_norm_exp_next = m_exp;
               m_guard_next = m_prod[21];
               m_rbit_next = m_prod[20];
               m_sticky_next = |m_prod[19:0];
            end
            next_state = (m_rnd == DEF_RND) ? ST_RND : ST_VAL;
         end

         ST_RND: begin
            if (m_guard && (m_rbit || m_sticky || m_norm_next[0])) begin
               m_norm_next = m_norm_next + 1;
               if (m_norm_next[22:0] == 23'h7fffff)
                  m_norm_exp_next = m_exp + 1;
            end
            next_state = ST_VAL;
         end

         ST_VAL: begin
            m_overflow_next = 1'b0;
            if (m_norm_exp_next[8] && !m_norm_exp_next[7]) begin
               m_norm_exp_next = 9'h1FF;
               m_norm_next = 24'b0;
               m_overflow_next = 1'b1;
            end
            next_state = ST_OUT;
         end

         ST_OUT: next_state = ST_LAT;

         ST_INF: begin
            m_norm_exp_next = 9'h1FF;
            m_norm_next = 24'b0;
            next_state = ST_OUT;
         end

         ST_ERR: begin
            qnan = 32'h7fffffff;
            m_sign_next = qnan[31];
            m_norm_exp_next = {1'b0, qnan[30:23]};
            m_norm_next = {1'b0, qnan[22:0]};
            m_invalid_next = 1'b1;
            m_overflow_next = 1'b0;
            next_state = ST_OUT;
         end

         default: next_state = ST_LAT;
      endcase
   end

   assign mult  = mult_reg;
   assign error = m_invalid;

endmodule
