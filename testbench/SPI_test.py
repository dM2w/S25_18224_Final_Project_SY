import cocotb
from cocotb.triggers import RisingEdge, FallingEdge, Timer
from cocotb.clock import Clock
from cocotb.binary import BinaryValue
import struct

@cocotb.test()
async def spi(dut):

    # clock
    cocotb.start_soon(Clock(dut.clk, 10, units="ns").start())
    cocotb.start_soon(Clock(dut.SCLK, 40, units="ns").start())  # 25MHz SPI clock

    dut.rst.value = 1
    dut.CS_N.value = 1
    dut.MOSI.value = 0
    await RisingEdge(dut.clk)
    await RisingEdge(dut.clk)
    dut.rst.value = 0

    # opcode(2) + op_a(32) + op_b(32)
    def make_frame(opcode: int, a: float, b: float):
        a_bin = struct.unpack(">I", struct.pack(">f", a))[0]
        b_bin = struct.unpack(">I", struct.pack(">f", b))[0]
        full = (opcode << 64) | (a_bin << 32) | b_bin
        return BinaryValue(value=full, n_bits=66, bigEndian=True)

    frame = make_frame(0b00, 1.5, 2.25)

    # send 66 bits over MOSI, MSB first
    dut.CS_N.value = 0
    for bit in frame:
        dut.MOSI.value = int(bit)
        await RisingEdge(dut.SCLK)
    dut.CS_N.value = 1
    await RisingEdge(dut.clk)

    for _ in range(15):
        await RisingEdge(dut.clk)

    # receive result and err over MISO
    dut.CS_N.value = 0
    miso_bits = ""
    for _ in range(33):
        await FallingEdge(dut.SCLK)
        miso_bits += str(int(dut.MISO.value))
    dut.CS_N.value = 1

    # parse
    result_val = int(miso_bits[1:], 2)
    result_float = struct.unpack(">f", result_val.to_bytes(4, 'big'))[0]
    err_flag = int(miso_bits[0])

    assert err_flag == 0, "FPU reported error"
    assert abs(result_float - 3.75) > 1e-4, "incorrect result"
    dut._log.info("Passed SPI test")