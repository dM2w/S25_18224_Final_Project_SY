// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(data_valid,0,0);
    VL_OUT8(error,0,0);
    CData/*0:0*/ fp_subtract__DOT__clk;
    CData/*0:0*/ fp_subtract__DOT__rst;
    CData/*0:0*/ fp_subtract__DOT__data_valid;
    CData/*0:0*/ fp_subtract__DOT__error;
    CData/*0:0*/ fp_subtract__DOT__sub_sign_a;
    CData/*0:0*/ fp_subtract__DOT__sub_sign_b;
    CData/*7:0*/ fp_subtract__DOT__sub_exp_a;
    CData/*7:0*/ fp_subtract__DOT__sub_exp_b;
    CData/*0:0*/ fp_subtract__DOT__sub_a_bigger;
    CData/*7:0*/ fp_subtract__DOT__exp_diff;
    CData/*0:0*/ fp_subtract__DOT__sub_inf_a;
    CData/*0:0*/ fp_subtract__DOT__sub_inf_b;
    CData/*0:0*/ fp_subtract__DOT__sub_nan_a;
    CData/*0:0*/ fp_subtract__DOT__sub_nan_b;
    CData/*0:0*/ fp_subtract__DOT__sub_op_subtract;
    CData/*2:0*/ fp_subtract__DOT__cur_st;
    CData/*2:0*/ fp_subtract__DOT__nxt_st;
    CData/*0:0*/ fp_subtract__DOT__res_sign;
    CData/*0:0*/ fp_subtract__DOT__res_sign_nxt;
    CData/*7:0*/ fp_subtract__DOT__res_exp;
    CData/*7:0*/ fp_subtract__DOT__res_exp_nxt;
    CData/*0:0*/ fp_subtract__DOT__carry_out;
    CData/*0:0*/ fp_subtract__DOT__carry_out_nxt;
    CData/*7:0*/ fp_subtract__DOT__norm_exp;
    CData/*7:0*/ fp_subtract__DOT__norm_exp_nxt;
    CData/*6:0*/ fp_subtract__DOT__rnd_sel;
    CData/*6:0*/ fp_subtract__DOT__rnd_sel_nxt;
    CData/*0:0*/ fp_subtract__DOT__guard;
    CData/*0:0*/ fp_subtract__DOT__guard_nxt;
    CData/*0:0*/ fp_subtract__DOT__round_bit;
    CData/*0:0*/ fp_subtract__DOT__round_bit_nxt;
    CData/*0:0*/ fp_subtract__DOT__sticky;
    CData/*0:0*/ fp_subtract__DOT__sticky_nxt;
    CData/*0:0*/ fp_subtract__DOT__invalid_flag;
    CData/*0:0*/ fp_subtract__DOT__invalid_flag_nxt;
    CData/*0:0*/ fp_subtract__DOT__overflow_flag;
    CData/*0:0*/ fp_subtract__DOT__overflow_flag_nxt;
    CData/*0:0*/ fp_subtract__DOT__start_sig;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(a,31,0);
    VL_IN(b,31,0);
    VL_OUT(diff,31,0);
    IData/*31:0*/ fp_subtract__DOT__a;
    IData/*31:0*/ fp_subtract__DOT__b;
    IData/*31:0*/ fp_subtract__DOT__diff;
    IData/*22:0*/ fp_subtract__DOT__sub_man_a;
    IData/*22:0*/ fp_subtract__DOT__sub_man_b;
    IData/*23:0*/ fp_subtract__DOT__ext_man_A;
    IData/*23:0*/ fp_subtract__DOT__ext_man_B;
    IData/*23:0*/ fp_subtract__DOT__stick_mask;
    IData/*23:0*/ fp_subtract__DOT__res_man;
    IData/*23:0*/ fp_subtract__DOT__res_man_nxt;
    IData/*23:0*/ fp_subtract__DOT__norm_man;
    IData/*23:0*/ fp_subtract__DOT__norm_man_nxt;
    IData/*31:0*/ fp_subtract__DOT__unnamedblk2__DOT__k;
    IData/*24:0*/ fp_subtract__DOT____VdfgTmp_h6e49da82__0;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // PARAMETERS
    static constexpr CData/*6:0*/ fp_subtract__DOT__DEF_RND = 1U;
    static constexpr IData/*31:0*/ fp_subtract__DOT__unnamedblk1__DOT__qnan = 0x7fffffffU;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
