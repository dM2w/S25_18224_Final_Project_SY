// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{

    // Tear down scope hierarchy
    __Vhier.remove(0, &__Vscope_fp_subtract);

}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_TOP.configure(this, name(), "TOP", "TOP", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_fp_subtract.configure(this, name(), "fp_subtract", "fp_subtract", -9, VerilatedScope::SCOPE_MODULE);
    __Vscope_fp_subtract__unnamedblk1.configure(this, name(), "fp_subtract.unnamedblk1", "unnamedblk1", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_fp_subtract__unnamedblk2.configure(this, name(), "fp_subtract.unnamedblk2", "unnamedblk2", -9, VerilatedScope::SCOPE_OTHER);

    // Set up scope hierarchy
    __Vhier.add(0, &__Vscope_fp_subtract);

    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TOP.varInsert(__Vfinal,"a", &(TOP.a), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"b", &(TOP.b), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"clk", &(TOP.clk), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0);
        __Vscope_TOP.varInsert(__Vfinal,"data_valid", &(TOP.data_valid), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0);
        __Vscope_TOP.varInsert(__Vfinal,"diff", &(TOP.diff), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"error", &(TOP.error), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0);
        __Vscope_TOP.varInsert(__Vfinal,"rst", &(TOP.rst), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"DEF_RND", const_cast<void*>(static_cast<const void*>(&(TOP.fp_subtract__DOT__DEF_RND))), true, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,6,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"a", &(TOP.fp_subtract__DOT__a), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"b", &(TOP.fp_subtract__DOT__b), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"carry_out", &(TOP.fp_subtract__DOT__carry_out), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"carry_out_nxt", &(TOP.fp_subtract__DOT__carry_out_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"clk", &(TOP.fp_subtract__DOT__clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"cur_st", &(TOP.fp_subtract__DOT__cur_st), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,2,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"data_valid", &(TOP.fp_subtract__DOT__data_valid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"diff", &(TOP.fp_subtract__DOT__diff), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"error", &(TOP.fp_subtract__DOT__error), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"exp_diff", &(TOP.fp_subtract__DOT__exp_diff), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,7,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"ext_man_A", &(TOP.fp_subtract__DOT__ext_man_A), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"ext_man_B", &(TOP.fp_subtract__DOT__ext_man_B), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"guard", &(TOP.fp_subtract__DOT__guard), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"guard_nxt", &(TOP.fp_subtract__DOT__guard_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"invalid_flag", &(TOP.fp_subtract__DOT__invalid_flag), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"invalid_flag_nxt", &(TOP.fp_subtract__DOT__invalid_flag_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"norm_exp", &(TOP.fp_subtract__DOT__norm_exp), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,7,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"norm_exp_nxt", &(TOP.fp_subtract__DOT__norm_exp_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,7,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"norm_man", &(TOP.fp_subtract__DOT__norm_man), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"norm_man_nxt", &(TOP.fp_subtract__DOT__norm_man_nxt), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"nxt_st", &(TOP.fp_subtract__DOT__nxt_st), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,2,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"overflow_flag", &(TOP.fp_subtract__DOT__overflow_flag), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"overflow_flag_nxt", &(TOP.fp_subtract__DOT__overflow_flag_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"res_exp", &(TOP.fp_subtract__DOT__res_exp), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,7,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"res_exp_nxt", &(TOP.fp_subtract__DOT__res_exp_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,7,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"res_man", &(TOP.fp_subtract__DOT__res_man), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"res_man_nxt", &(TOP.fp_subtract__DOT__res_man_nxt), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"res_sign", &(TOP.fp_subtract__DOT__res_sign), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"res_sign_nxt", &(TOP.fp_subtract__DOT__res_sign_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"rnd_sel", &(TOP.fp_subtract__DOT__rnd_sel), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,6,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"rnd_sel_nxt", &(TOP.fp_subtract__DOT__rnd_sel_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,6,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"round_bit", &(TOP.fp_subtract__DOT__round_bit), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"round_bit_nxt", &(TOP.fp_subtract__DOT__round_bit_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"rst", &(TOP.fp_subtract__DOT__rst), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"start_sig", &(TOP.fp_subtract__DOT__start_sig), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"stick_mask", &(TOP.fp_subtract__DOT__stick_mask), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sticky", &(TOP.fp_subtract__DOT__sticky), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sticky_nxt", &(TOP.fp_subtract__DOT__sticky_nxt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_a_bigger", &(TOP.fp_subtract__DOT__sub_a_bigger), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_exp_a", &(TOP.fp_subtract__DOT__sub_exp_a), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,7,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_exp_b", &(TOP.fp_subtract__DOT__sub_exp_b), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1 ,7,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_inf_a", &(TOP.fp_subtract__DOT__sub_inf_a), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_inf_b", &(TOP.fp_subtract__DOT__sub_inf_b), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_man_a", &(TOP.fp_subtract__DOT__sub_man_a), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,22,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_man_b", &(TOP.fp_subtract__DOT__sub_man_b), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,22,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_nan_a", &(TOP.fp_subtract__DOT__sub_nan_a), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_nan_b", &(TOP.fp_subtract__DOT__sub_nan_b), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_op_subtract", &(TOP.fp_subtract__DOT__sub_op_subtract), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_sign_a", &(TOP.fp_subtract__DOT__sub_sign_a), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract.varInsert(__Vfinal,"sub_sign_b", &(TOP.fp_subtract__DOT__sub_sign_b), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_fp_subtract__unnamedblk1.varInsert(__Vfinal,"qnan", const_cast<void*>(static_cast<const void*>(&(TOP.fp_subtract__DOT__unnamedblk1__DOT__qnan))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_fp_subtract__unnamedblk2.varInsert(__Vfinal,"k", &(TOP.fp_subtract__DOT__unnamedblk2__DOT__k), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY,1 ,31,0);
    }
}
