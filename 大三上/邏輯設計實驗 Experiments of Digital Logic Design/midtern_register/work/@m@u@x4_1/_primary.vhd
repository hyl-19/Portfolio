library verilog;
use verilog.vl_types.all;
entity MUX4_1 is
    port(
        s0              : in     vl_logic;
        s1              : in     vl_logic;
        i0              : in     vl_logic;
        i1              : in     vl_logic;
        i2              : in     vl_logic;
        i3              : in     vl_logic;
        \out\           : out    vl_logic
    );
end MUX4_1;
