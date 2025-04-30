import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge

FPU_LATENCY = 12

async def run_primitive_op(dut, opcode, a_val, b_val, expected, expected_err):
    # drive operands and opcode
    dut.tb_opcode.value = opcode
    dut.tb_a.value = a_val
    dut.tb_b.value = b_val

    dut.tb_valid.value = 1
    await RisingEdge(dut.clk)
    dut.tb_valid.value = 0

    # wait for result (FPU latency + 2 cycles)
    for _ in range(FPU_LATENCY + 2):
        await RisingEdge(dut.clk)

    # result
    if opcode == 0b00 or opcode == 0b01:
        got = int(dut.U_ADD.sum.value)
        err = int(dut.U_ADD.error.value)
        label = "ADD" if opcode == 0b00 else "SUB"

    elif opcode == 0b10:
        got = int(dut.U_MUL.mult.value)
        err = int(dut.U_MUL.error.value)
        label = "MUL"

    elif opcode == 0b11:
        got = int(dut.U_DIV.div.value)
        err = int(dut.U_DIV.error.value)
        label = "DIV"
    else:
        raise ValueError("Invalid opcode") # should not be here no opcode

    dut._log.info(f"got=0x{got:08x}, expected=0x{expected:08x}, err={err}, expected_err={expected_err}")
    assert got == expected, f"{label} value mismatch"
    assert err == expected_err, f"{label} error mismatch"


@cocotb.test()
async def primitive_units_test(dut):
    # clock
    cocotb.start_soon(Clock(dut.clk, 10, units="ns").start())

    # reset and validsignal
    dut.rst.value = 1
    dut.tb_valid.value = 0
    await RisingEdge(dut.clk)
    await RisingEdge(dut.clk)
    dut.rst.value = 0
    await RisingEdge(dut.clk)

    # SPI lines in test mode
    dut.SCLK.value = 0
    dut.CS_N.value = 1
    dut.MOSI.value = 0

    # add
    await run_primitive_op(dut, 0b00, 0x3f800000, 0x3f800000, 0x40000000, 0)
    await run_primitive_op(dut, 0b00,0x4479ff5c, 0x3c23d70a, 0x447a0000, 0) # 999.98999 + 0.01 = 999.999939
    await run_primitive_op(dut, 0b00,0x431617a8, 0xc3480000, 0xc247a160, 0) # 150.0924 - 200 = -49.9076
    # sub
    await run_primitive_op(dut, 0b01, 0x40400000, 0x40000000, 0x3f800000, 0)  
    await run_primitive_op(dut, 0b01,0xbf800000, 0x3f800000, 0xc0a00000, 0)# -1.0 - 1.0 = -2.0s
    # mul
    await run_primitive_op(dut, 0b10, 0x40000000, 0x40000000, 0x40800000, 0) #2.0 * 2.0 = 4.0
    await run_primitive_op(dut, 0b10,0x3f666666, 0x3f4ccccd, 0x3f70a3d7, 0)# 0.9 * 0.8 =0.72

    dut._log.info("Passed ALL in TEST_MODE!!!!")
