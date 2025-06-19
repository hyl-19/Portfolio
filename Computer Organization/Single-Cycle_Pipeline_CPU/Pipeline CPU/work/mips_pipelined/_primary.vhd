library verilog;
use verilog.vl_types.all;
entity mips_pipelined is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic
    );
end mips_pipelined;
