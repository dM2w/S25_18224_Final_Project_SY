TOPLEVEL_LANG = verilog
VERILOG_SOURCES = $(shell pwd)/src/FPU_add.sv \
  $(shell pwd)/src/FPU_sub.sv \
  $(shell pwd)/src/FPU_mul.sv \
  $(shell pwd)/src/FPU_div.sv \
  $(shell pwd)/src/SPI.sv
TOPLEVEL = fpu_spi
MODULE = SPI_test
SIM = verilator
EXTRA_ARGS += --trace -Wno-WIDTHTRUNC -Wno-UNOPTFLAT -Wno-fatal
include $(shell cocotb-config --makefiles)/Makefile.sim
