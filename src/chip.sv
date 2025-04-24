`default_nettype none

module my_chip (
    input logic [11:0] io_in, // Inputs to your chip
    output logic [11:0] io_out, // Outputs from your chip
    input logic clock,
    input logic reset // Important: Reset is ACTIVE-HIGH
);
    
    // Basic counter design as an example
    // TODO: remove the counter design and use this module to insert your own design
    // DO NOT change the I/O header of this design

    fpu_spi #(
        .FPU_LATENCY(12)
    ) fpu (
        .clk   (clock),
        .rst   (reset),
        .SCLK  (io_in[0]),
        .CS_N  (io_in[1]),
        .MOSI  (io_in[2]),
        .MISO  (io_out[0])
    );

endmodule
