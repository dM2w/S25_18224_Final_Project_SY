TOPLEVEL_LANG = verilog
VERILOG_SOURCES = $(shell pwd)/../src/FPU_add.sv
TOPLEVEL = fp_adder
MODULE = add_test
SIM = verilator
EXTRA_ARGS += --trace -Wno-WIDTHTRUNC -Wno-UNOPTFLAT -Wno-fatal
include $(shell cocotb-config --makefiles)/Makefile.sim
