TOPLEVEL_LANG = verilog
VERILOG_SOURCES = $(shell pwd)/src/FPU_sub.sv
TOPLEVEL = fpu_spi
MODULE = sub_test
SIM = verilator
EXTRA_ARGS += --trace -Wno-WIDTHTRUNC -Wno-UNOPTFLAT -Wno-fatal
include $(shell cocotb-config --makefiles)/Makefile.sim
