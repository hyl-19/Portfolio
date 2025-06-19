library verilog;
use verilog.vl_types.all;
entity MEM_WB is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en_reg          : in     vl_logic;
        WB_in           : in     vl_logic_vector(1 downto 0);
        RD_in           : in     vl_logic_vector(31 downto 0);
        ADDR_in         : in     vl_logic_vector(31 downto 0);
        WN_in           : in     vl_logic_vector(4 downto 0);
        WB_out          : out    vl_logic_vector(1 downto 0);
        RD_out          : out    vl_logic_vector(31 downto 0);
        ADDR_out        : out    vl_logic_vector(31 downto 0);
        WN_out          : out    vl_logic_vector(4 downto 0)
    );
end MEM_WB;
