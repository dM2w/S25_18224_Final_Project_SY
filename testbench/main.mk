TOPLEVEL_LANG = verilog
VERILOG_SOURCES = \
  $(shell pwd)/src/FPU_add.sv \
  $(shell pwd)/src/FPU_mul.sv \
  $(shell pwd)/src/FPU_div.sv \
  $(shell pwd)/src/SPI_TESTMODE.sv
TOPLEVEL = fpu_spi_test
MODULE = main_test
SIM = verilator
EXTRA_ARGS += --trace -DTEST_MODE=1 -Wno-WIDTHTRUNC -Wno-UNOPTFLAT -Wno-fatal
include $(shell cocotb-config --makefiles)/Makefile.sim
