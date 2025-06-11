library verilog;
use verilog.vl_types.all;
entity IF_ID is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en_reg          : in     vl_logic;
        ins_in          : in     vl_logic_vector(31 downto 0);
        pc_in           : in     vl_logic_vector(31 downto 0);
        ins_out         : out    vl_logic_vector(31 downto 0);
        pc_out          : out    vl_logic_vector(31 downto 0)
    );
end IF_ID;
