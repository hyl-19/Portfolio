library verilog;
use verilog.vl_types.all;
entity msb_alu is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        cin             : in     vl_logic;
        cout            : out    vl_logic;
        \signal\        : in     vl_logic_vector(1 downto 0);
        inv             : in     vl_logic;
        less            : in     vl_logic;
        \out\           : out    vl_logic;
        set             : out    vl_logic
    );
end msb_alu;
