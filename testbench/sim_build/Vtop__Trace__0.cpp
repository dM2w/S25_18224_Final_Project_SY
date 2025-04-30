// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelf->clk));
    bufp->chgBit(oldp+1,(vlSelf->rst));
    bufp->chgIData(oldp+2,(vlSelf->a),32);
    bufp->chgIData(oldp+3,(vlSelf->b),32);
    bufp->chgBit(oldp+4,(vlSelf->data_valid));
    bufp->chgIData(oldp+5,(vlSelf->diff),32);
    bufp->chgBit(oldp+6,(vlSelf->error));
    bufp->chgBit(oldp+7,(vlSelf->fp_subtract__DOT__clk));
    bufp->chgBit(oldp+8,(vlSelf->fp_subtract__DOT__rst));
    bufp->chgIData(oldp+9,(vlSelf->fp_subtract__DOT__a),32);
    bufp->chgIData(oldp+10,(vlSelf->fp_subtract__DOT__b),32);
    bufp->chgBit(oldp+11,(vlSelf->fp_subtract__DOT__data_valid));
    bufp->chgIData(oldp+12,(vlSelf->fp_subtract__DOT__diff),32);
    bufp->chgBit(oldp+13,(vlSelf->fp_subtract__DOT__error));
    bufp->chgBit(oldp+14,(vlSelf->fp_subtract__DOT__sub_sign_a));
    bufp->chgBit(oldp+15,(vlSelf->fp_subtract__DOT__sub_sign_b));
    bufp->chgCData(oldp+16,(vlSelf->fp_subtract__DOT__sub_exp_a),8);
    bufp->chgCData(oldp+17,(vlSelf->fp_subtract__DOT__sub_exp_b),8);
    bufp->chgIData(oldp+18,(vlSelf->fp_subtract__DOT__sub_man_a),23);
    bufp->chgIData(oldp+19,(vlSelf->fp_subtract__DOT__sub_man_b),23);
    bufp->chgBit(oldp+20,(vlSelf->fp_subtract__DOT__sub_a_bigger));
    bufp->chgCData(oldp+21,(vlSelf->fp_subtract__DOT__exp_diff),8);
    bufp->chgBit(oldp+22,(vlSelf->fp_subtract__DOT__sub_inf_a));
    bufp->chgBit(oldp+23,(vlSelf->fp_subtract__DOT__sub_inf_b));
    bufp->chgBit(oldp+24,(vlSelf->fp_subtract__DOT__sub_nan_a));
    bufp->chgBit(oldp+25,(vlSelf->fp_subtract__DOT__sub_nan_b));
    bufp->chgIData(oldp+26,(vlSelf->fp_subtract__DOT__ext_man_A),24);
    bufp->chgIData(oldp+27,(vlSelf->fp_subtract__DOT__ext_man_B),24);
    bufp->chgBit(oldp+28,(vlSelf->fp_subtract__DOT__sub_op_subtract));
    bufp->chgIData(oldp+29,(vlSelf->fp_subtract__DOT__stick_mask),24);
    bufp->chgCData(oldp+30,(vlSelf->fp_subtract__DOT__cur_st),3);
    bufp->chgCData(oldp+31,(vlSelf->fp_subtract__DOT__nxt_st),3);
    bufp->chgBit(oldp+32,(vlSelf->fp_subtract__DOT__res_sign));
    bufp->chgBit(oldp+33,(vlSelf->fp_subtract__DOT__res_sign_nxt));
    bufp->chgCData(oldp+34,(vlSelf->fp_subtract__DOT__res_exp),8);
    bufp->chgCData(oldp+35,(vlSelf->fp_subtract__DOT__res_exp_nxt),8);
    bufp->chgIData(oldp+36,(vlSelf->fp_subtract__DOT__res_man),24);
    bufp->chgIData(oldp+37,(vlSelf->fp_subtract__DOT__res_man_nxt),24);
    bufp->chgBit(oldp+38,(vlSelf->fp_subtract__DOT__carry_out));
    bufp->chgBit(oldp+39,(vlSelf->fp_subtract__DOT__carry_out_nxt));
    bufp->chgCData(oldp+40,(vlSelf->fp_subtract__DOT__norm_exp),8);
    bufp->chgCData(oldp+41,(vlSelf->fp_subtract__DOT__norm_exp_nxt),8);
    bufp->chgIData(oldp+42,(vlSelf->fp_subtract__DOT__norm_man),24);
    bufp->chgIData(oldp+43,(vlSelf->fp_subtract__DOT__norm_man_nxt),24);
    bufp->chgCData(oldp+44,(vlSelf->fp_subtract__DOT__rnd_sel),7);
    bufp->chgCData(oldp+45,(vlSelf->fp_subtract__DOT__rnd_sel_nxt),7);
    bufp->chgBit(oldp+46,(vlSelf->fp_subtract__DOT__guard));
    bufp->chgBit(oldp+47,(vlSelf->fp_subtract__DOT__guard_nxt));
    bufp->chgBit(oldp+48,(vlSelf->fp_subtract__DOT__round_bit));
    bufp->chgBit(oldp+49,(vlSelf->fp_subtract__DOT__round_bit_nxt));
    bufp->chgBit(oldp+50,(vlSelf->fp_subtract__DOT__sticky));
    bufp->chgBit(oldp+51,(vlSelf->fp_subtract__DOT__sticky_nxt));
    bufp->chgBit(oldp+52,(vlSelf->fp_subtract__DOT__invalid_flag));
    bufp->chgBit(oldp+53,(vlSelf->fp_subtract__DOT__invalid_flag_nxt));
    bufp->chgBit(oldp+54,(vlSelf->fp_subtract__DOT__overflow_flag));
    bufp->chgBit(oldp+55,(vlSelf->fp_subtract__DOT__overflow_flag_nxt));
    bufp->chgBit(oldp+56,(vlSelf->fp_subtract__DOT__start_sig));
    bufp->chgIData(oldp+57,(vlSelf->fp_subtract__DOT__unnamedblk2__DOT__k),32);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
