library verilog;
use verilog.vl_types.all;
entity ID_EX is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en_reg          : in     vl_logic;
        WB_in           : in     vl_logic_vector(1 downto 0);
        MEM_in          : in     vl_logic_vector(1 downto 0);
        EX_in           : in     vl_logic_vector(3 downto 0);
        shamt_in        : in     vl_logic_vector(4 downto 0);
        funct_in        : in     vl_logic_vector(5 downto 0);
        RD1_in          : in     vl_logic_vector(31 downto 0);
        RD2_in          : in     vl_logic_vector(31 downto 0);
        immed_in        : in     vl_logic_vector(31 downto 0);
        rt_in           : in     vl_logic_vector(4 downto 0);
        rd_in           : in     vl_logic_vector(4 downto 0);
        WB_out          : out    vl_logic_vector(1 downto 0);
        MEM_out         : out    vl_logic_vector(1 downto 0);
        EX_out          : out    vl_logic_vector(3 downto 0);
        shamt_out       : out    vl_logic_vector(4 downto 0);
        funct_out       : out    vl_logic_vector(5 downto 0);
        RD1_out         : out    vl_logic_vector(31 downto 0);
        RD2_out         : out    vl_logic_vector(31 downto 0);
        immed_out       : out    vl_logic_vector(31 downto 0);
        rt_out          : out    vl_logic_vector(4 downto 0);
        rd_out          : out    vl_logic_vector(4 downto 0)
    );
end ID_EX;
