// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Init
    IData/*22:0*/ fp_subtract__DOT____VdfgTmp_h2128558a__0;
    fp_subtract__DOT____VdfgTmp_h2128558a__0 = 0;
    IData/*22:0*/ fp_subtract__DOT____VdfgTmp_hb1c11dad__0;
    fp_subtract__DOT____VdfgTmp_hb1c11dad__0 = 0;
    IData/*24:0*/ fp_subtract__DOT____VdfgTmp_h24cc83e0__0;
    fp_subtract__DOT____VdfgTmp_h24cc83e0__0 = 0;
    // Body
    vlSelf->fp_subtract__DOT__clk = vlSelf->clk;
    vlSelf->fp_subtract__DOT__rst = vlSelf->rst;
    vlSelf->fp_subtract__DOT__a = vlSelf->a;
    vlSelf->fp_subtract__DOT__b = vlSelf->b;
    vlSelf->fp_subtract__DOT__data_valid = vlSelf->data_valid;
    vlSelf->fp_subtract__DOT__start_sig = vlSelf->data_valid;
    vlSelf->fp_subtract__DOT__sub_sign_a = (vlSelf->a 
                                            >> 0x1fU);
    vlSelf->fp_subtract__DOT__sub_sign_b = (1U & (~ 
                                                  (vlSelf->b 
                                                   >> 0x1fU)));
    vlSelf->fp_subtract__DOT__sub_man_a = (0x7fffffU 
                                           & vlSelf->a);
    vlSelf->fp_subtract__DOT__sub_man_b = (0x7fffffU 
                                           & vlSelf->b);
    vlSelf->fp_subtract__DOT__sub_exp_a = (0xffU & 
                                           (vlSelf->a 
                                            >> 0x17U));
    vlSelf->fp_subtract__DOT__sub_exp_b = (0xffU & 
                                           (vlSelf->b 
                                            >> 0x17U));
    vlSelf->fp_subtract__DOT__sub_op_subtract = ((IData)(vlSelf->fp_subtract__DOT__sub_sign_b) 
                                                 ^ (IData)(vlSelf->fp_subtract__DOT__sub_sign_a));
    vlSelf->fp_subtract__DOT__sub_inf_a = ((0xffU == (IData)(vlSelf->fp_subtract__DOT__sub_exp_a)) 
                                           & (0U == vlSelf->fp_subtract__DOT__sub_man_a));
    vlSelf->fp_subtract__DOT__sub_nan_a = ((0xffU == (IData)(vlSelf->fp_subtract__DOT__sub_exp_a)) 
                                           & (0U != vlSelf->fp_subtract__DOT__sub_man_a));
    vlSelf->fp_subtract__DOT__sub_inf_b = ((0xffU == (IData)(vlSelf->fp_subtract__DOT__sub_exp_b)) 
                                           & (0U == vlSelf->fp_subtract__DOT__sub_man_b));
    vlSelf->fp_subtract__DOT__sub_nan_b = ((0xffU == (IData)(vlSelf->fp_subtract__DOT__sub_exp_b)) 
                                           & (0U != vlSelf->fp_subtract__DOT__sub_man_b));
    vlSelf->fp_subtract__DOT__sub_a_bigger = (((IData)(vlSelf->fp_subtract__DOT__sub_exp_a) 
                                               == (IData)(vlSelf->fp_subtract__DOT__sub_exp_b))
                                               ? (vlSelf->fp_subtract__DOT__sub_man_a 
                                                  > vlSelf->fp_subtract__DOT__sub_man_b)
                                               : ((IData)(vlSelf->fp_subtract__DOT__sub_exp_a) 
                                                  > (IData)(vlSelf->fp_subtract__DOT__sub_exp_b)));
    if (vlSelf->fp_subtract__DOT__sub_a_bigger) {
        fp_subtract__DOT____VdfgTmp_h2128558a__0 = vlSelf->fp_subtract__DOT__sub_man_a;
        fp_subtract__DOT____VdfgTmp_hb1c11dad__0 = vlSelf->fp_subtract__DOT__sub_man_b;
        vlSelf->fp_subtract__DOT__exp_diff = (0xffU 
                                              & ((IData)(vlSelf->fp_subtract__DOT__sub_exp_a) 
                                                 - (IData)(vlSelf->fp_subtract__DOT__sub_exp_b)));
    } else {
        fp_subtract__DOT____VdfgTmp_h2128558a__0 = vlSelf->fp_subtract__DOT__sub_man_b;
        fp_subtract__DOT____VdfgTmp_hb1c11dad__0 = vlSelf->fp_subtract__DOT__sub_man_a;
        vlSelf->fp_subtract__DOT__exp_diff = (0xffU 
                                              & ((IData)(vlSelf->fp_subtract__DOT__sub_exp_b) 
                                                 - (IData)(vlSelf->fp_subtract__DOT__sub_exp_a)));
    }
    vlSelf->fp_subtract__DOT__ext_man_A = (0x800000U 
                                           | fp_subtract__DOT____VdfgTmp_h2128558a__0);
    vlSelf->fp_subtract__DOT__ext_man_B = (0x800000U 
                                           | fp_subtract__DOT____VdfgTmp_hb1c11dad__0);
    vlSelf->fp_subtract__DOT__stick_mask = (0xffffffU 
                                            & VL_SHIFTR_III(24,24,32, 0x7fffffU, 
                                                            ((IData)(2U) 
                                                             + 
                                                             ((IData)(0x17U) 
                                                              - (IData)(vlSelf->fp_subtract__DOT__exp_diff)))));
    fp_subtract__DOT____VdfgTmp_h24cc83e0__0 = (0x1ffffffU 
                                                & VL_SHIFTR_III(25,25,8, 
                                                                (0x800000U 
                                                                 | fp_subtract__DOT____VdfgTmp_hb1c11dad__0), (IData)(vlSelf->fp_subtract__DOT__exp_diff)));
    vlSelf->fp_subtract__DOT____VdfgTmp_h6e49da82__0 
        = (0x1ffffffU & ((IData)(vlSelf->fp_subtract__DOT__sub_op_subtract)
                          ? ((0x800000U | fp_subtract__DOT____VdfgTmp_h2128558a__0) 
                             - fp_subtract__DOT____VdfgTmp_h24cc83e0__0)
                          : ((0x800000U | fp_subtract__DOT____VdfgTmp_h2128558a__0) 
                             + fp_subtract__DOT____VdfgTmp_h24cc83e0__0)));
    vlSelf->fp_subtract__DOT__res_sign_nxt = vlSelf->fp_subtract__DOT__res_sign;
    vlSelf->fp_subtract__DOT__res_exp_nxt = vlSelf->fp_subtract__DOT__res_exp;
    vlSelf->fp_subtract__DOT__res_man_nxt = vlSelf->fp_subtract__DOT__res_man;
    vlSelf->fp_subtract__DOT__carry_out_nxt = vlSelf->fp_subtract__DOT__carry_out;
    vlSelf->fp_subtract__DOT__norm_exp_nxt = vlSelf->fp_subtract__DOT__norm_exp;
    vlSelf->fp_subtract__DOT__norm_man_nxt = vlSelf->fp_subtract__DOT__norm_man;
    vlSelf->fp_subtract__DOT__rnd_sel_nxt = vlSelf->fp_subtract__DOT__rnd_sel;
    vlSelf->fp_subtract__DOT__guard_nxt = vlSelf->fp_subtract__DOT__guard;
    vlSelf->fp_subtract__DOT__round_bit_nxt = vlSelf->fp_subtract__DOT__round_bit;
    vlSelf->fp_subtract__DOT__sticky_nxt = vlSelf->fp_subtract__DOT__sticky;
    vlSelf->fp_subtract__DOT__invalid_flag_nxt = vlSelf->fp_subtract__DOT__invalid_flag;
    vlSelf->fp_subtract__DOT__overflow_flag_nxt = vlSelf->fp_subtract__DOT__overflow_flag;
    vlSelf->fp_subtract__DOT__nxt_st = vlSelf->fp_subtract__DOT__cur_st;
    if ((4U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
        if ((2U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
            if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
                vlSelf->fp_subtract__DOT__nxt_st = 0U;
            } else {
                vlSelf->fp_subtract__DOT__diff = (((IData)(vlSelf->fp_subtract__DOT__res_sign) 
                                                   << 0x1fU) 
                                                  | (((IData)(vlSelf->fp_subtract__DOT__norm_exp) 
                                                      << 0x17U) 
                                                     | (0x7fffffU 
                                                        & vlSelf->fp_subtract__DOT__norm_man)));
                vlSelf->fp_subtract__DOT__error = vlSelf->fp_subtract__DOT__invalid_flag;
                vlSelf->fp_subtract__DOT__nxt_st = 0U;
            }
        } else if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
            vlSelf->fp_subtract__DOT__res_sign_nxt = 0U;
            vlSelf->fp_subtract__DOT__norm_exp_nxt = 0xffU;
            vlSelf->fp_subtract__DOT__norm_man_nxt = 0x7fffffU;
            vlSelf->fp_subtract__DOT__invalid_flag_nxt = 1U;
            vlSelf->fp_subtract__DOT__overflow_flag_nxt = 0U;
            vlSelf->fp_subtract__DOT__nxt_st = 6U;
        } else {
            vlSelf->fp_subtract__DOT__res_sign_nxt 
                = ((IData)(vlSelf->fp_subtract__DOT__sub_inf_a)
                    ? (IData)(vlSelf->fp_subtract__DOT__sub_sign_a)
                    : (IData)(vlSelf->fp_subtract__DOT__sub_sign_b));
            vlSelf->fp_subtract__DOT__norm_exp_nxt = 0xffU;
            vlSelf->fp_subtract__DOT__norm_man_nxt = 0U;
            vlSelf->fp_subtract__DOT__nxt_st = 6U;
        }
    } else if ((2U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
        if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
            vlSelf->fp_subtract__DOT__overflow_flag_nxt = 0U;
            vlSelf->fp_subtract__DOT__nxt_st = 6U;
            if ((0xffU == (IData)(vlSelf->fp_subtract__DOT__norm_exp))) {
                vlSelf->fp_subtract__DOT__res_sign_nxt = 0U;
                vlSelf->fp_subtract__DOT__norm_man_nxt = 0U;
                vlSelf->fp_subtract__DOT__overflow_flag_nxt = 1U;
            }
        } else {
            if (((IData)(vlSelf->fp_subtract__DOT__guard) 
                 & (((IData)(vlSelf->fp_subtract__DOT__round_bit) 
                     | (IData)(vlSelf->fp_subtract__DOT__sticky)) 
                    | vlSelf->fp_subtract__DOT__norm_man))) {
                vlSelf->fp_subtract__DOT__norm_man_nxt 
                    = (0xffffffU & ((IData)(1U) + vlSelf->fp_subtract__DOT__norm_man));
                if ((0x7fffffU == (0x7fffffU & vlSelf->fp_subtract__DOT__norm_man_nxt))) {
                    vlSelf->fp_subtract__DOT__norm_exp_nxt 
                        = (0xffU & ((IData)(1U) + (IData)(vlSelf->fp_subtract__DOT__res_exp)));
                }
            }
            vlSelf->fp_subtract__DOT__nxt_st = 3U;
        }
    } else if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
        vlSelf->fp_subtract__DOT__norm_exp_nxt = vlSelf->fp_subtract__DOT__res_exp;
        vlSelf->fp_subtract__DOT__norm_man_nxt = vlSelf->fp_subtract__DOT__res_man;
        vlSelf->fp_subtract__DOT__guard_nxt = vlSelf->fp_subtract__DOT__guard;
        vlSelf->fp_subtract__DOT__round_bit_nxt = vlSelf->fp_subtract__DOT__round_bit;
        vlSelf->fp_subtract__DOT__sticky_nxt = vlSelf->fp_subtract__DOT__sticky;
        if (vlSelf->fp_subtract__DOT__carry_out) {
            vlSelf->fp_subtract__DOT__norm_man_nxt 
                = (0xffffffU & VL_SHIFTR_III(24,24,32, vlSelf->fp_subtract__DOT__res_man, 1U));
            vlSelf->fp_subtract__DOT__norm_exp_nxt 
                = (0xffU & ((IData)(1U) + (IData)(vlSelf->fp_subtract__DOT__res_exp)));
            vlSelf->fp_subtract__DOT__guard_nxt = (1U 
                                                   & vlSelf->fp_subtract__DOT__norm_man);
            vlSelf->fp_subtract__DOT__round_bit_nxt 
                = vlSelf->fp_subtract__DOT__guard;
            vlSelf->fp_subtract__DOT__sticky_nxt = 
                ((IData)(vlSelf->fp_subtract__DOT__sticky) 
                 | (IData)(vlSelf->fp_subtract__DOT__round_bit));
            vlSelf->fp_subtract__DOT__norm_man_nxt 
                = (0x800000U | vlSelf->fp_subtract__DOT__norm_man_nxt);
        } else {
            vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k = 0x17U;
            {
                while (VL_LTES_III(32, 0U, vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)) {
                    if (((0x17U >= (0x1fU & vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)) 
                         && (1U & (vlSelf->fp_subtract__DOT__res_man 
                                   >> (0x1fU & vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k))))) {
                        vlSelf->fp_subtract__DOT__norm_man_nxt 
                            = (0xffffffU & VL_SHIFTL_III(24,24,32, vlSelf->fp_subtract__DOT__res_man, 
                                                         ((IData)(0x17U) 
                                                          - vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)));
                        vlSelf->fp_subtract__DOT__norm_exp_nxt 
                            = (0xffU & ((IData)(vlSelf->fp_subtract__DOT__res_exp) 
                                        - ((IData)(0x17U) 
                                           - vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)));
                        goto __Vlabel1;
                    }
                    vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k 
                        = (vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k 
                           - (IData)(1U));
                }
                __Vlabel1: ;
            }
            if ((0U != (IData)(vlSelf->fp_subtract__DOT__rnd_sel_nxt))) {
                vlSelf->fp_subtract__DOT__norm_man_nxt 
                    = ((0xfffffeU & vlSelf->fp_subtract__DOT__norm_man_nxt) 
                       | (IData)(vlSelf->fp_subtract__DOT__guard_nxt));
                vlSelf->fp_subtract__DOT__guard_nxt 
                    = vlSelf->fp_subtract__DOT__round_bit_nxt;
                vlSelf->fp_subtract__DOT__round_bit_nxt = 0U;
            }
        }
        vlSelf->fp_subtract__DOT__invalid_flag_nxt = 0U;
        vlSelf->fp_subtract__DOT__nxt_st = ((1U == (IData)(vlSelf->fp_subtract__DOT__rnd_sel_nxt))
                                             ? 2U : 3U);
    } else if (vlSelf->rst) {
        vlSelf->fp_subtract__DOT__diff = 0U;
        vlSelf->fp_subtract__DOT__error = 0U;
    } else if (vlSelf->fp_subtract__DOT__start_sig) {
        if (vlSelf->fp_subtract__DOT__sub_a_bigger) {
            vlSelf->fp_subtract__DOT__res_sign_nxt 
                = vlSelf->fp_subtract__DOT__sub_sign_a;
            vlSelf->fp_subtract__DOT__res_exp_nxt = vlSelf->fp_subtract__DOT__sub_exp_a;
        } else {
            vlSelf->fp_subtract__DOT__res_sign_nxt 
                = vlSelf->fp_subtract__DOT__sub_sign_b;
            vlSelf->fp_subtract__DOT__res_exp_nxt = vlSelf->fp_subtract__DOT__sub_exp_b;
        }
        vlSelf->fp_subtract__DOT__carry_out_nxt = (1U 
                                                   & (vlSelf->fp_subtract__DOT____VdfgTmp_h6e49da82__0 
                                                      >> 0x18U));
        vlSelf->fp_subtract__DOT__res_man_nxt = (0xffffffU 
                                                 & vlSelf->fp_subtract__DOT____VdfgTmp_h6e49da82__0);
        vlSelf->fp_subtract__DOT__rnd_sel_nxt = 1U;
        vlSelf->fp_subtract__DOT__guard_nxt = (1U & 
                                               VL_SHIFTR_III(24,24,32, vlSelf->fp_subtract__DOT__ext_man_B, 
                                                             ((IData)(vlSelf->fp_subtract__DOT__exp_diff) 
                                                              - (IData)(1U))));
        vlSelf->fp_subtract__DOT__round_bit_nxt = (1U 
                                                   & VL_SHIFTR_III(24,24,32, vlSelf->fp_subtract__DOT__ext_man_B, 
                                                                   ((IData)(vlSelf->fp_subtract__DOT__exp_diff) 
                                                                    - (IData)(2U))));
        vlSelf->fp_subtract__DOT__sticky_nxt = (0U 
                                                != 
                                                (vlSelf->fp_subtract__DOT__ext_man_B 
                                                 & vlSelf->fp_subtract__DOT__stick_mask));
        vlSelf->fp_subtract__DOT__nxt_st = ((((IData)(vlSelf->fp_subtract__DOT__sub_inf_a) 
                                              & (IData)(vlSelf->fp_subtract__DOT__sub_inf_b)) 
                                             | ((IData)(vlSelf->fp_subtract__DOT__sub_nan_a) 
                                                | (IData)(vlSelf->fp_subtract__DOT__sub_nan_b)))
                                             ? 5U : 
                                            (((IData)(vlSelf->fp_subtract__DOT__sub_inf_a) 
                                              ^ (IData)(vlSelf->fp_subtract__DOT__sub_inf_b))
                                              ? 4U : 1U));
    }
    vlSelf->diff = vlSelf->fp_subtract__DOT__diff;
    vlSelf->error = vlSelf->fp_subtract__DOT__error;
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->rst) {
        vlSelf->fp_subtract__DOT__cur_st = 0U;
        vlSelf->fp_subtract__DOT__res_man = 0U;
        vlSelf->fp_subtract__DOT__res_exp = 0U;
        vlSelf->fp_subtract__DOT__norm_exp = 0U;
        vlSelf->fp_subtract__DOT__norm_man = 0U;
        vlSelf->fp_subtract__DOT__rnd_sel = 0U;
    } else {
        vlSelf->fp_subtract__DOT__cur_st = vlSelf->fp_subtract__DOT__nxt_st;
        vlSelf->fp_subtract__DOT__res_man = vlSelf->fp_subtract__DOT__res_man_nxt;
        vlSelf->fp_subtract__DOT__res_exp = vlSelf->fp_subtract__DOT__res_exp_nxt;
        vlSelf->fp_subtract__DOT__norm_exp = vlSelf->fp_subtract__DOT__norm_exp_nxt;
        vlSelf->fp_subtract__DOT__norm_man = vlSelf->fp_subtract__DOT__norm_man_nxt;
        vlSelf->fp_subtract__DOT__rnd_sel = vlSelf->fp_subtract__DOT__rnd_sel_nxt;
    }
    vlSelf->fp_subtract__DOT__overflow_flag = ((1U 
                                                & (~ (IData)(vlSelf->rst))) 
                                               && (IData)(vlSelf->fp_subtract__DOT__overflow_flag_nxt));
    vlSelf->fp_subtract__DOT__invalid_flag = ((1U & 
                                               (~ (IData)(vlSelf->rst))) 
                                              && (IData)(vlSelf->fp_subtract__DOT__invalid_flag_nxt));
    vlSelf->fp_subtract__DOT__carry_out = ((1U & (~ (IData)(vlSelf->rst))) 
                                           && (IData)(vlSelf->fp_subtract__DOT__carry_out_nxt));
    vlSelf->fp_subtract__DOT__res_sign = ((1U & (~ (IData)(vlSelf->rst))) 
                                          && (IData)(vlSelf->fp_subtract__DOT__res_sign_nxt));
    vlSelf->fp_subtract__DOT__guard = ((1U & (~ (IData)(vlSelf->rst))) 
                                       && (IData)(vlSelf->fp_subtract__DOT__guard_nxt));
    vlSelf->fp_subtract__DOT__round_bit = ((1U & (~ (IData)(vlSelf->rst))) 
                                           && (IData)(vlSelf->fp_subtract__DOT__round_bit_nxt));
    vlSelf->fp_subtract__DOT__sticky = ((1U & (~ (IData)(vlSelf->rst))) 
                                        && (IData)(vlSelf->fp_subtract__DOT__sticky_nxt));
    vlSelf->fp_subtract__DOT__res_sign_nxt = vlSelf->fp_subtract__DOT__res_sign;
    vlSelf->fp_subtract__DOT__res_exp_nxt = vlSelf->fp_subtract__DOT__res_exp;
    vlSelf->fp_subtract__DOT__res_man_nxt = vlSelf->fp_subtract__DOT__res_man;
    vlSelf->fp_subtract__DOT__carry_out_nxt = vlSelf->fp_subtract__DOT__carry_out;
    vlSelf->fp_subtract__DOT__norm_exp_nxt = vlSelf->fp_subtract__DOT__norm_exp;
    vlSelf->fp_subtract__DOT__norm_man_nxt = vlSelf->fp_subtract__DOT__norm_man;
    vlSelf->fp_subtract__DOT__rnd_sel_nxt = vlSelf->fp_subtract__DOT__rnd_sel;
    vlSelf->fp_subtract__DOT__guard_nxt = vlSelf->fp_subtract__DOT__guard;
    vlSelf->fp_subtract__DOT__round_bit_nxt = vlSelf->fp_subtract__DOT__round_bit;
    vlSelf->fp_subtract__DOT__sticky_nxt = vlSelf->fp_subtract__DOT__sticky;
    vlSelf->fp_subtract__DOT__invalid_flag_nxt = vlSelf->fp_subtract__DOT__invalid_flag;
    vlSelf->fp_subtract__DOT__overflow_flag_nxt = vlSelf->fp_subtract__DOT__overflow_flag;
    vlSelf->fp_subtract__DOT__nxt_st = vlSelf->fp_subtract__DOT__cur_st;
    if ((4U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
        if ((2U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
            if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
                vlSelf->fp_subtract__DOT__nxt_st = 0U;
            } else {
                vlSelf->fp_subtract__DOT__diff = (((IData)(vlSelf->fp_subtract__DOT__res_sign) 
                                                   << 0x1fU) 
                                                  | (((IData)(vlSelf->fp_subtract__DOT__norm_exp) 
                                                      << 0x17U) 
                                                     | (0x7fffffU 
                                                        & vlSelf->fp_subtract__DOT__norm_man)));
                vlSelf->fp_subtract__DOT__error = vlSelf->fp_subtract__DOT__invalid_flag;
                vlSelf->fp_subtract__DOT__nxt_st = 0U;
            }
        } else if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
            vlSelf->fp_subtract__DOT__res_sign_nxt = 0U;
            vlSelf->fp_subtract__DOT__norm_exp_nxt = 0xffU;
            vlSelf->fp_subtract__DOT__norm_man_nxt = 0x7fffffU;
            vlSelf->fp_subtract__DOT__invalid_flag_nxt = 1U;
            vlSelf->fp_subtract__DOT__overflow_flag_nxt = 0U;
            vlSelf->fp_subtract__DOT__nxt_st = 6U;
        } else {
            vlSelf->fp_subtract__DOT__res_sign_nxt 
                = ((IData)(vlSelf->fp_subtract__DOT__sub_inf_a)
                    ? (IData)(vlSelf->fp_subtract__DOT__sub_sign_a)
                    : (IData)(vlSelf->fp_subtract__DOT__sub_sign_b));
            vlSelf->fp_subtract__DOT__norm_exp_nxt = 0xffU;
            vlSelf->fp_subtract__DOT__norm_man_nxt = 0U;
            vlSelf->fp_subtract__DOT__nxt_st = 6U;
        }
    } else if ((2U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
        if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
            vlSelf->fp_subtract__DOT__overflow_flag_nxt = 0U;
            vlSelf->fp_subtract__DOT__nxt_st = 6U;
            if ((0xffU == (IData)(vlSelf->fp_subtract__DOT__norm_exp))) {
                vlSelf->fp_subtract__DOT__res_sign_nxt = 0U;
                vlSelf->fp_subtract__DOT__norm_man_nxt = 0U;
                vlSelf->fp_subtract__DOT__overflow_flag_nxt = 1U;
            }
        } else {
            if (((IData)(vlSelf->fp_subtract__DOT__guard) 
                 & (((IData)(vlSelf->fp_subtract__DOT__round_bit) 
                     | (IData)(vlSelf->fp_subtract__DOT__sticky)) 
                    | vlSelf->fp_subtract__DOT__norm_man))) {
                vlSelf->fp_subtract__DOT__norm_man_nxt 
                    = (0xffffffU & ((IData)(1U) + vlSelf->fp_subtract__DOT__norm_man));
                if ((0x7fffffU == (0x7fffffU & vlSelf->fp_subtract__DOT__norm_man_nxt))) {
                    vlSelf->fp_subtract__DOT__norm_exp_nxt 
                        = (0xffU & ((IData)(1U) + (IData)(vlSelf->fp_subtract__DOT__res_exp)));
                }
            }
            vlSelf->fp_subtract__DOT__nxt_st = 3U;
        }
    } else if ((1U & (IData)(vlSelf->fp_subtract__DOT__cur_st))) {
        vlSelf->fp_subtract__DOT__norm_exp_nxt = vlSelf->fp_subtract__DOT__res_exp;
        vlSelf->fp_subtract__DOT__norm_man_nxt = vlSelf->fp_subtract__DOT__res_man;
        vlSelf->fp_subtract__DOT__guard_nxt = vlSelf->fp_subtract__DOT__guard;
        vlSelf->fp_subtract__DOT__round_bit_nxt = vlSelf->fp_subtract__DOT__round_bit;
        vlSelf->fp_subtract__DOT__sticky_nxt = vlSelf->fp_subtract__DOT__sticky;
        if (vlSelf->fp_subtract__DOT__carry_out) {
            vlSelf->fp_subtract__DOT__norm_man_nxt 
                = (0xffffffU & VL_SHIFTR_III(24,24,32, vlSelf->fp_subtract__DOT__res_man, 1U));
            vlSelf->fp_subtract__DOT__norm_exp_nxt 
                = (0xffU & ((IData)(1U) + (IData)(vlSelf->fp_subtract__DOT__res_exp)));
            vlSelf->fp_subtract__DOT__guard_nxt = (1U 
                                                   & vlSelf->fp_subtract__DOT__norm_man);
            vlSelf->fp_subtract__DOT__round_bit_nxt 
                = vlSelf->fp_subtract__DOT__guard;
            vlSelf->fp_subtract__DOT__sticky_nxt = 
                ((IData)(vlSelf->fp_subtract__DOT__sticky) 
                 | (IData)(vlSelf->fp_subtract__DOT__round_bit));
            vlSelf->fp_subtract__DOT__norm_man_nxt 
                = (0x800000U | vlSelf->fp_subtract__DOT__norm_man_nxt);
        } else {
            vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k = 0x17U;
            {
                while (VL_LTES_III(32, 0U, vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)) {
                    if (((0x17U >= (0x1fU & vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)) 
                         && (1U & (vlSelf->fp_subtract__DOT__res_man 
                                   >> (0x1fU & vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k))))) {
                        vlSelf->fp_subtract__DOT__norm_man_nxt 
                            = (0xffffffU & VL_SHIFTL_III(24,24,32, vlSelf->fp_subtract__DOT__res_man, 
                                                         ((IData)(0x17U) 
                                                          - vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)));
                        vlSelf->fp_subtract__DOT__norm_exp_nxt 
                            = (0xffU & ((IData)(vlSelf->fp_subtract__DOT__res_exp) 
                                        - ((IData)(0x17U) 
                                           - vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k)));
                        goto __Vlabel2;
                    }
                    vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k 
                        = (vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k 
                           - (IData)(1U));
                }
                __Vlabel2: ;
            }
            if ((0U != (IData)(vlSelf->fp_subtract__DOT__rnd_sel_nxt))) {
                vlSelf->fp_subtract__DOT__norm_man_nxt 
                    = ((0xfffffeU & vlSelf->fp_subtract__DOT__norm_man_nxt) 
                       | (IData)(vlSelf->fp_subtract__DOT__guard_nxt));
                vlSelf->fp_subtract__DOT__guard_nxt 
                    = vlSelf->fp_subtract__DOT__round_bit_nxt;
                vlSelf->fp_subtract__DOT__round_bit_nxt = 0U;
            }
        }
        vlSelf->fp_subtract__DOT__invalid_flag_nxt = 0U;
        vlSelf->fp_subtract__DOT__nxt_st = ((1U == (IData)(vlSelf->fp_subtract__DOT__rnd_sel_nxt))
                                             ? 2U : 3U);
    } else if (vlSelf->rst) {
        vlSelf->fp_subtract__DOT__diff = 0U;
        vlSelf->fp_subtract__DOT__error = 0U;
    } else if (vlSelf->fp_subtract__DOT__start_sig) {
        if (vlSelf->fp_subtract__DOT__sub_a_bigger) {
            vlSelf->fp_subtract__DOT__res_sign_nxt 
                = vlSelf->fp_subtract__DOT__sub_sign_a;
            vlSelf->fp_subtract__DOT__res_exp_nxt = vlSelf->fp_subtract__DOT__sub_exp_a;
        } else {
            vlSelf->fp_subtract__DOT__res_sign_nxt 
                = vlSelf->fp_subtract__DOT__sub_sign_b;
            vlSelf->fp_subtract__DOT__res_exp_nxt = vlSelf->fp_subtract__DOT__sub_exp_b;
        }
        vlSelf->fp_subtract__DOT__carry_out_nxt = (1U 
                                                   & (vlSelf->fp_subtract__DOT____VdfgTmp_h6e49da82__0 
                                                      >> 0x18U));
        vlSelf->fp_subtract__DOT__res_man_nxt = (0xffffffU 
                                                 & vlSelf->fp_subtract__DOT____VdfgTmp_h6e49da82__0);
        vlSelf->fp_subtract__DOT__rnd_sel_nxt = 1U;
        vlSelf->fp_subtract__DOT__guard_nxt = (1U & 
                                               VL_SHIFTR_III(24,24,32, vlSelf->fp_subtract__DOT__ext_man_B, 
                                                             ((IData)(vlSelf->fp_subtract__DOT__exp_diff) 
                                                              - (IData)(1U))));
        vlSelf->fp_subtract__DOT__round_bit_nxt = (1U 
                                                   & VL_SHIFTR_III(24,24,32, vlSelf->fp_subtract__DOT__ext_man_B, 
                                                                   ((IData)(vlSelf->fp_subtract__DOT__exp_diff) 
                                                                    - (IData)(2U))));
        vlSelf->fp_subtract__DOT__sticky_nxt = (0U 
                                                != 
                                                (vlSelf->fp_subtract__DOT__ext_man_B 
                                                 & vlSelf->fp_subtract__DOT__stick_mask));
        vlSelf->fp_subtract__DOT__nxt_st = ((((IData)(vlSelf->fp_subtract__DOT__sub_inf_a) 
                                              & (IData)(vlSelf->fp_subtract__DOT__sub_inf_b)) 
                                             | ((IData)(vlSelf->fp_subtract__DOT__sub_nan_a) 
                                                | (IData)(vlSelf->fp_subtract__DOT__sub_nan_b)))
                                             ? 5U : 
                                            (((IData)(vlSelf->fp_subtract__DOT__sub_inf_a) 
                                              ^ (IData)(vlSelf->fp_subtract__DOT__sub_inf_b))
                                              ? 4U : 1U));
    }
    vlSelf->diff = vlSelf->fp_subtract__DOT__diff;
    vlSelf->error = vlSelf->fp_subtract__DOT__error;
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/afs/andrew.cmu.edu/usr16/sutongy/private/18224/S25_18224_Final_Project_SY/testbench/../src/FPU_sub.sv", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/afs/andrew.cmu.edu/usr16/sutongy/private/18224/S25_18224_Final_Project_SY/testbench/../src/FPU_sub.sv", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/afs/andrew.cmu.edu/usr16/sutongy/private/18224/S25_18224_Final_Project_SY/testbench/../src/FPU_sub.sv", 1, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->data_valid & 0xfeU))) {
        Verilated::overWidthError("data_valid");}
}
#endif  // VL_DEBUG
