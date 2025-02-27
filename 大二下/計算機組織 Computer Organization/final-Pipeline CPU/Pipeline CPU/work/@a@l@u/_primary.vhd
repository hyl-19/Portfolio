library verilog;
use verilog.vl_types.all;
entity ALU is
    port(
        dataA           : in     vl_logic_vector(31 downto 0);
        dataB           : in     vl_logic_vector(31 downto 0);
        ctl             : in     vl_logic_vector(2 downto 0);
        result          : out    vl_logic_vector(31 downto 0);
        shamt           : in     vl_logic_vector(4 downto 0)
    );
end ALU;
