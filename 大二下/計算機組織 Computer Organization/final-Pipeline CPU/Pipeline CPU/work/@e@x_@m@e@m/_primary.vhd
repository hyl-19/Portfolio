library verilog;
use verilog.vl_types.all;
entity EX_MEM is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en_reg          : in     vl_logic;
        WB_in           : in     vl_logic_vector(1 downto 0);
        MEM_in          : in     vl_logic_vector(1 downto 0);
        alu_in          : in     vl_logic_vector(31 downto 0);
        RD2_in          : in     vl_logic_vector(31 downto 0);
        WN_in           : in     vl_logic_vector(4 downto 0);
        WB_out          : out    vl_logic_vector(1 downto 0);
        MEM_out         : out    vl_logic_vector(1 downto 0);
        alu_out         : out    vl_logic_vector(31 downto 0);
        RD2_out         : out    vl_logic_vector(31 downto 0);
        WN_out          : out    vl_logic_vector(4 downto 0)
    );
end EX_MEM;
