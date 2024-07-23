library verilog;
use verilog.vl_types.all;
entity Shift_Register is
    port(
        i               : in     vl_logic_vector(7 downto 0);
        s               : in     vl_logic_vector(1 downto 0);
        o               : out    vl_logic_vector(7 downto 0);
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        r               : in     vl_logic
    );
end Shift_Register;
