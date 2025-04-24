module fp_div (
    input  logic        clk,
    input  logic        rst,
    input  logic        data_valid,
    input  logic [31:0] a,
    input  logic [31:0] b,
    output logic [31:0] div,
    output logic        error
);

    //==========================================================================
    // Operand Decomposition
    //==========================================================================
    logic fa_sign_a, fa_sign_b;
    logic [7:0] fa_exp_a, fa_exp_b;
    logic [22:0] fa_man_a, fa_man_b;
    logic fa_inf_a, fa_inf_b;
    logic fa_nan_a, fa_nan_b;
    logic fa_zero_a, fa_zero_b;

    assign fa_sign_a = a[31];
    assign fa_exp_a = a[30:23];
    assign fa_man_a = a[22:0];

    assign fa_sign_b = b[31];
    assign fa_exp_b = b[30:23];
    assign fa_man_b = b[22:0];

    assign fa_inf_a = (fa_exp_a == 8'hFF) && (fa_man_a == 0);
    assign fa_inf_b = (fa_exp_b == 8'hFF) && (fa_man_b == 0);
    assign fa_nan_a = (fa_exp_a == 8'hFF) && (fa_man_a != 0);
    assign fa_nan_b = (fa_exp_b == 8'hFF) && (fa_man_b != 0);
    assign fa_zero_a = (fa_exp_a == 8'h00) && (fa_man_a == 0);
    assign fa_zero_b = (fa_exp_b == 8'h00) && (fa_man_b == 0);

    // interface signals
    logic mul_req, mul_ack;
    logic [31:0] mul_op1, mul_op2, mul_res;
    logic mul_overf;

    logic add_req, add_ack;
    logic [31:0] add_op1, add_op2, add_res;
    logic add_overf;

    // mul instantiation
    fp_mult MUL_I (
        .clk(clk),
        .rst(rst),
        .a(mul_op1),
        .b(mul_op2),
        .data_valid(mul_req),
        .mult(mul_res),
        .error(mul_overf)
    );

    // add instantiation
    fp_adder ADD_I (
        .clk(clk),
        .rst(rst),
        .a(add_op1),
        .b(add_op2),
        .data_valid(add_req),
        .sum(add_res),
        .error(add_overf)
    );

    // FSM registers
    typedef enum logic [3:0] {
        ST_IDLE, ST_INIT1, ST_INIT2,
        ST_ITER1, ST_ITER2, ST_ITER3,
        ST_FINAL, ST_ZERO, ST_DIVZERO,
        ST_INFCASE, ST_NANCASE, ST_OVRFLW, ST_DONE
    } state_t;

    state_t state, state_n;
    logic [31:0] reg_num, reg_den, reg_tmp, reg_est;
    logic [6:0] rnd_sel, rnd_sel_n;
    logic [1:0] iter_cnt, iter_cnt_n;
    logic phase, phase_n;
    logic inv_f, inv_f_n;
    logic ovf_f, ovf_f_n;
    logic [31:0] reg_num_n, reg_den_n, reg_tmp_n, reg_est_n;
    logic [31:0] div_reg;
    logic error_reg;

    logic [31:0] COEFF1;
    assign COEFF1 = 32'h3FF0F0F1;
    logic [31:0] COEFF2;
    assign COEFF2 = 32'h4034B4B5;
    logic [31:0] INF_CONST;
    assign INF_CONST = 32'h7F800000;

    always_ff @(posedge clk) begin
        if (rst) begin
            state <= ST_IDLE;
            reg_num <= 0;
            reg_den <= 0;
            reg_tmp <= 0;
            reg_est <= 0;
            rnd_sel <= 0;
            iter_cnt <= 0;
            phase <= 0;
            inv_f <= 0;
            ovf_f <= 0;
            div_reg <= 0;
            error_reg <= 0;
        end else begin
            state <= state_n;
            reg_num <= reg_num_n;
            reg_den <= reg_den_n;
            reg_tmp <= reg_tmp_n;
            reg_est <= reg_est_n;
            rnd_sel <= rnd_sel_n;
            iter_cnt <= iter_cnt_n;
            phase <= phase_n;
            inv_f <= inv_f_n;
            ovf_f <= ovf_f_n;
            if (state == ST_DONE) begin
                div_reg <= reg_tmp;
                error_reg <= inv_f;
            end
        end
    end

    always_comb begin
        state_n = state;
        reg_num_n = reg_num;
        reg_den_n = reg_den;
        reg_tmp_n = reg_tmp;
        reg_est_n = reg_est;
        rnd_sel_n = rnd_sel;
        iter_cnt_n = iter_cnt;
        phase_n = phase;
        inv_f_n = inv_f;
        ovf_f_n = ovf_f;
        mul_req = 0;
        add_req = 0;
        mul_op1 = '0;
        mul_op2 = '0;
        add_op1 = '0;
        add_op2 = '0;

        if (!data_valid) begin
            state_n = ST_IDLE;
        end else begin
            case (state)
                ST_IDLE: begin
                    if (fa_nan_a || fa_nan_b || (fa_inf_a && fa_inf_b)) begin
                        inv_f_n = 1;
                        state_n = ST_NANCASE;
                    end else if (fa_zero_b) begin
                        inv_f_n = 1;
                        state_n = ST_DIVZERO;
                    end else if (fa_zero_a) begin
                        state_n = ST_ZERO;
                    end else if (fa_inf_a ^ fa_inf_b) begin
                        state_n = ST_INFCASE;
                    end else begin
                        reg_num_n = a;
                        reg_den_n = b;
                        phase_n = 0;
                        state_n = ST_INIT1;
                    end
                end

                ST_INIT1: begin
                    mul_op1 = COEFF1;
                    mul_op2 = {reg_den[31], 8'd126, reg_den[22:0]};
                    mul_req = 1;
                    if (mul_overf !== 1'bx || 1'b1) begin
                        reg_est_n = mul_res;
                        phase_n = 0;
                        state_n = ST_INIT2;
                    end
                end

                ST_INIT2: begin
                    add_op1 = COEFF2;
                    add_op2 = {~reg_est[31], reg_est[30:0]};
                    add_req = 1;
                    if (add_overf !== 1'bx || 1'b1) begin
                        reg_tmp_n = add_res;
                        iter_cnt_n = 0;
                        phase_n = 0;
                        state_n = ST_ITER1;
                    end
                end

                ST_ITER1: begin
                    mul_op1 = reg_tmp;
                    mul_op2 = {reg_den[31], 8'd126, reg_den[22:0]};
                    mul_req = 1;
                    if (mul_overf !== 1'bx || 1'b1) begin
                        reg_tmp_n = mul_res;
                        state_n = ST_ITER2;
                    end
                end

                ST_ITER2: begin
                    add_op1 = 32'h40000000;
                    add_op2 = {~reg_tmp[31], reg_tmp[30:0]};
                    add_req = 1;
                    if (add_overf !== 1'bx || 1'b1) begin
                        reg_tmp_n = add_res;
                        state_n = ST_ITER3;
                    end
                end

                ST_ITER3: begin
                    mul_op1 = reg_est;
                    mul_op2 = reg_tmp;
                    mul_req = 1;
                    if (mul_overf !== 1'bx || 1'b1) begin
                        reg_est_n = mul_res;
                        state_n = (iter_cnt == 2) ? ST_FINAL : ST_ITER1;
                        iter_cnt_n = iter_cnt + 1;
                    end
                end

                ST_FINAL: begin
                    mul_op1 = a;
                    mul_op2 = reg_est;
                    mul_req = 1;
                    if (mul_overf !== 1'bx || 1'b1) begin
                        reg_tmp_n = mul_res;
                        state_n = mul_overf ? ST_OVRFLW : ST_DONE;
                    end
                end

                ST_ZERO: state_n = ST_DONE;
                ST_DIVZERO: state_n = ST_DONE;
                ST_INFCASE: state_n = ST_DONE;
                ST_NANCASE: state_n = ST_DONE;
                ST_OVRFLW: state_n = ST_DONE;
                default: state_n = ST_IDLE;
            endcase
        end
    end

    //output assignments
    assign div = div_reg;
    assign error = error_reg;

endmodule
