TOPLEVEL_LANG = verilog
VERILOG_SOURCES = $(shell pwd)/src/FPU_mul.sv
TOPLEVEL = fp_mult
MODULE = mul_test
SIM = verilator
EXTRA_ARGS += --trace -Wno-WIDTHTRUNC -Wno-UNOPTFLAT -Wno-fatal
include $(shell cocotb-config --makefiles)/Makefile.sim
