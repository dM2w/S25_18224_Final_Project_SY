import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

async def run_test_vector(dut, test_id, a_val, b_val, expected_diff, expected_err):
    dut._log.info(
        f"[Test {test_id}] Driving a = 0x{a_val:08x}, b = 0x{b_val:08x}"
    )
    dut.a.value = a_val
    dut.b.value = b_val
    dut.data_valid.value = 1 

    # let one rising edge capture operands
    await RisingEdge(dut.clk)
    dut.data_valid.value = 0   # deassert

    # wait enough clock cycles for the subtract module to complete its state machine
    for _ in range(30):
        await RisingEdge(dut.clk)

    # capture outputs
    result_diff = int(dut.diff.value)
    result_err = int(dut.error.value)

    dut._log.info(
        f"[Test {test_id}] Got diff = 0x{result_diff:08x} and error = {result_err} "
        f"(Expected: diff = 0x{expected_diff:08x}, error = {expected_err})"
    )

    assert result_diff == expected_diff, \
        f"Test {test_id} failed: expected diff 0x{expected_diff:08x}, got 0x{result_diff:08x}"
    assert result_err == expected_err, \
        f"Test {test_id} failed: expected error {expected_err}, got {result_err}"

@cocotb.test()
async def fp_subtract_test(dut):
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    # deassert
    dut.rst.value = 1
    await Timer(20, units="ns")
    dut.rst.value = 0
    dut.data_valid.value = 0
    await RisingEdge(dut.clk)

    # test vectors
    # (a, b, expected_diff, expected_err)
    test_vectors = [
        # --- Case A: Regular arithmetic ---
        # 1.0 - 0.5 = 0.5
        (0x3f800000, 0x3f000000, 0x3f000000, 0),
        # 2.0 - 1.0 = 1.0
        (0x40000000, 0x3f800000, 0x3f800000, 0),
        # 1.5 - 1.25 = 0.25
        (0x3fc00000, 0x3fa00000, 0x3e800000, 0),
        # -1.0 - 1.0 = -2.0
        (0xbf800000, 0x3f800000, 0xc0000000, 0),

        # --- Case B: Infinities ---
        # inf - 1.0 = inf
        (0x7f800000, 0x3f800000, 0x7f800000, 0),
        # 1.0 - inf = -inf
        (0x3f800000, 0x7f800000, 0xff800000, 0),
        # inf - inf -> invalid, produce quiet NaN
        (0x7f800000, 0x7f800000, 0x7fffffff, 1),

        # --- Case C: Zero cases ---
        # 1.0 - 0.0 = 1.0
        (0x3f800000, 0x00000000, 0x3f800000, 0),
        # 0.0 - (-0.0) = 0.0
        (0x00000000, 0x80000000, 0x00800000, 0),
    ]

    test_id = 1
    for vec in test_vectors:
        a_val, b_val, expected_diff, expected_err = vec
        await run_test_vector(dut, test_id, a_val, b_val, expected_diff, expected_err)
        test_id += 1

    dut._log.info("All fp_subtract tests passed!")
