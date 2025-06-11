library verilog;
use verilog.vl_types.all;
entity multiplier is
    generic(
        MULT            : vl_logic := Hi1;
        \OUT\           : vl_logic := Hi0
    );
    port(
        clk             : in     vl_logic;
        dataA           : in     vl_logic_vector(31 downto 0);
        dataB           : in     vl_logic_vector(31 downto 0);
        \Signal\        : in     vl_logic;
        dataOut         : out    vl_logic_vector(63 downto 0);
        reset           : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of MULT : constant is 1;
    attribute mti_svvh_generic_type of \OUT\ : constant is 1;
end multiplier;
