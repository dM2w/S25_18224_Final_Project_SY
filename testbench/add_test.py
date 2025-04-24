import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer
import logging

#apply a single test vector
async def run_test_vector(dut, test_id, a_val, b_val, expected_sum, expected_err, rounding_mode):
    dut._log.info(f"[Test {test_id}] Applying a = 0x{a_val:08x}, b = 0x{b_val:08x}, rnd_mode = {rounding_mode}")

    # drive inputs
    dut.a.value          = a_val
    dut.b.value          = b_val
    dut.rnd_mode.value   = rounding_mode
    dut.data_valid.value = 1 

    # let one rising edge capture operands
    await RisingEdge(dut.clk)
    dut.data_valid.value = 0   # deassert

    # now wait up to N cycles for result to settle
    for _ in range(30):
        await RisingEdge(dut.clk)

    # sample outputs
    result_sum = int(dut.sum.value)
    result_err = int(dut.error.value)

    dut._log.info(f"[Test {test_id}] Got sum = 0x{result_sum:08x}, error = {result_err} "
                  f"(Expected sum = 0x{expected_sum:08x}, error = {expected_err})")

    assert result_sum == expected_sum, \
        f"[Test {test_id}] Sum mismatch: exp=0x{expected_sum:08x}, got=0x{result_sum:08x}"
    assert result_err == expected_err, \
        f"[Test {test_id}] Err flag mismatch: exp={expected_err}, got={result_err}"



@cocotb.test()
async def fp_adder_test(dut):
  
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    # synchronous reset
    dut.rst.value        = 1
    dut.data_valid.value = 0
    await Timer(20, units="ns")
    dut.rst.value = 0
    await RisingEdge(dut.clk)


    # test vectors for each case.
    # (a, b, expected_sum, expected_error)
    # all tests first here use the default rounding mode (0) except for the TTE rounding tests
    test_vectors_default = [
        (0xc5fce001, 0x34d98e63, 0xc5fce000, 0),    # -8092.000425 - 0.00000040523 = -8092.0004254052
        (0xc3730083, 0xc119999a, 0xc37c9a1d, 0),    # -243.001999 - 9.6 = -252.601990
        (0x3fc00000, 0x4500001a, 0x4500181a, 0),  # 1.5 + 2048.006348 = 2049.506348
        (0x484c3381, 0x25acf030, 0x484c3380, 0),    # 209102.0123408 + 3.00000011676e-16 = 209102.0123408

        (0x3f000000, 0xbee00000, 0x3d800000, 0),    # 0.5 - 0.4375 = 0.0625
        (0x4479ff5c, 0x3c23d70a, 0x447a0000, 0),    # 999.98999 + 0.01 = 999.999939
        (0x431617a8, 0xc3480000, 0xc247a160, 0),    # 150.0924 - 200 = -49.9076
        (0x4238147b, 0xc21f36ae, 0x40c6ee68, 0),    # 46.02 - 39.8034 = 6.2166
        (0x3db8d4fe, 0x3f68f9b1, 0x3f800a28, 0),    # 0.09025 + 0.91006 = 1.00031
        (0x42c40666, 0x41403333, 0x42dc0ccc, 0),    # 98.0125 + 12.0125 = 110.025

        (0x484c3381, 0x00000000, 0x484c3380, 0),    # 209102.0123408 + 0.0 = 209102.0123408
        (0x4479ff5c, 0x80000000, 0x4479ff5c, 0),    # 999.98999 - 0.0 = 999.98999
    ]
    
    # test vectors for TTE Rounding (rounding_mode = 1)
    test_vectors_tte = [
        (0xc3730083, 0xc119999a, 0xc37c9a1d, 0),  # -243.001999 - 9.6 with TTE: expected result changes by LSB
        (0x4479ff5c, 0x3c23d70a, 0x447a0000, 0)   # 999.98999 + 0.01 with TTE rounding
    ]

    test_id = 1
    # default test vectors with rounding_mode = 0.
    for vec in test_vectors_default:
        a_val, b_val, expected_sum, expected_err = vec
        await run_test_vector(dut, test_id, a_val, b_val, expected_sum, expected_err, rounding_mode=0)
        test_id += 1

    # rounding test vectors with rounding_mode = 1.
    dut._log.info("Switching to TTE rounding mode (rounding_mode = 1)")
    for vec in test_vectors_tte:
        a_val, b_val, expected_sum, expected_err = vec
        await run_test_vector(dut, test_id, a_val, b_val, expected_sum, expected_err, rounding_mode=1)
        test_id += 1

    dut._log.info("All test cases passed!")
