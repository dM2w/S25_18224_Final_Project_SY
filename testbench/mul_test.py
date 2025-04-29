import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

async def run_test_vector(dut, test_id, a_val, b_val, expected, rnd_mode):
    dut._log.info(f"[Test {test_id}] Applying a = 0x{a_val:08x}, b = 0x{b_val:08x}, "
                  f"rnd_mode = {rnd_mode}")
    
    dut.a.value = a_val
    dut.b.value = b_val
    dut.m_rnd.value = rnd_mode
    dut.data_valid.value = 1 

    # let one rising edge capture operands
    await RisingEdge(dut.clk)
    dut.data_valid.value = 0

    # wait enough clock cycles
    for _ in range(30):
        await RisingEdge(dut.clk)

    # read the output
    result = int(dut.mult.value)
    err_flag = int(dut.error.value)
    dut._log.info(f"[Test {test_id}] Got mult = 0x{result:08x}, error = {err_flag} "
                  f"(Expected mult = 0x{expected:08x})")
    assert result == expected, (
        f"[Test {test_id}] FAILED: Expected mult = 0x{expected:08x}, got 0x{result:08x}")

async def run_exception_only(dut, test_id, a_val, b_val, expected_err):

    dut._log.info(f"[Test {test_id}] [Exception] Applying a = 0x{a_val:08x}, b = 0x{b_val:08x}")
    dut.a.value = a_val
    dut.b.value = b_val
    # drive the rounding mode
    dut.m_rnd.value = 0

    for _ in range(30):
        await RisingEdge(dut.clk)

    # check the error flag
    err_flag = int(dut.error.value)
    dut._log.info(f"[Test {test_id}] [Exception] Got error flag = {err_flag} (Expected error flag = {expected_err})")
    assert err_flag == expected_err, (
        f"[Test {test_id}] Exception FAILED: Expected error flag = {expected_err}, got {err_flag}")

@cocotb.test()
async def fp_mult_test(dut):
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())
    
    dut.rst.value = 1
    await Timer(20, units="ns")
    dut.rst.value = 0
    dut.data_valid.value = 0
    await RisingEdge(dut.clk)
    
    # the default rounding mode (0)
    dut.m_rnd.value = 0
    test_id = 1

    # --- Case A: Legal operands ---
    #  (operand_a, operand_b, expected_result)
    legal_vectors = [
        (0x3f800000, 0x40000000, 0x40000000),   # 1.0 * 2.0= 2.0
        (0x40400000, 0x3f000000, 0x3f800000),   # 3.0 * 0.5= 1.5
        (0xbf800000, 0x40000000, 0xc0000000),   # -1.0 * 2.0= -2.0
        (0x41200000, 0x3f800000, 0x41400000), # 10.0 * 1.0 =10.0
        (0x3f800000, 0xbf800000, 0xbf800000),
        (0x3f666666, 0x3f4ccccd, 0x3f70a3d7)    # 0.9 * 0.8   ≈ 0.72
    ]
    for a_val, b_val, expected in legal_vectors:
        await run_test_vector(dut, test_id, a_val, b_val, expected, 0)
        test_id += 1

    # --- Case B: Zero operands ---
    zero_vectors = [
        (0x3f800000, 0x00000000, 0x00000000),  # 1.0 *  0.0 =  0.0
        (0x40000000, 0x80000000, 0x80000000),  # 2.0 * -0.0 = -0.0
        (0xbf800000, 0x00000000, 0x00000000)   # -1.0 * 0.0 =  0.0
    ]
    for a_val, b_val, expected in zero_vectors:
        await run_test_vector(dut, test_id, a_val, b_val, expected, 0)
        test_id += 1

    # --- Case C: Valid infinite operands ---
    inf_vectors = [
        (0x7f800000, 0x3f800000, 0x7f800000),  # inf *  1.0 =  inf
        (0xff800000, 0x3f800000, 0xff800000),  # -inf * 1.0 = -inf
        (0x7f800000, 0xbf800000, 0xff800000),  # inf * -1.0 = -inf
        (0xff800000, 0xbf800000, 0x7f800000)   # -inf * -1.0 = inf
    ]
    for a_val, b_val, expected in inf_vectors:
        await run_test_vector(dut, test_id, a_val, b_val, expected, 0)
        test_id += 1


    dut._log.info("All multiplier test cases passed")
