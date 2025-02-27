library verilog;
use verilog.vl_types.all;
entity sign_extend is
    generic(
        BEQ             : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        LW              : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi0, Hi1, Hi1);
        SW              : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi1)
    );
    port(
        clk             : in     vl_logic;
        op              : in     vl_logic_vector(31 downto 0);
        immed_in        : in     vl_logic_vector(15 downto 0);
        ext_immed_out   : out    vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of BEQ : constant is 1;
    attribute mti_svvh_generic_type of LW : constant is 1;
    attribute mti_svvh_generic_type of SW : constant is 1;
end sign_extend;
