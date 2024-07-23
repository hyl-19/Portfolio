library verilog;
use verilog.vl_types.all;
entity vending_machine is
    generic(
        state_0         : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        state_1         : vl_logic_vector(0 to 1) := (Hi0, Hi1);
        state_2         : vl_logic_vector(0 to 1) := (Hi1, Hi0);
        state_3         : vl_logic_vector(0 to 1) := (Hi1, Hi1)
    );
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        howManyTicket   : in     vl_logic_vector(31 downto 0);
        origin          : in     vl_logic_vector(2 downto 0);
        destination     : in     vl_logic_vector(2 downto 0);
        money           : in     vl_logic_vector(31 downto 0);
        costOfTicket    : out    vl_logic_vector(31 downto 0);
        moneyToPay      : out    vl_logic_vector(31 downto 0);
        totalMoney      : out    vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of state_0 : constant is 1;
    attribute mti_svvh_generic_type of state_1 : constant is 1;
    attribute mti_svvh_generic_type of state_2 : constant is 1;
    attribute mti_svvh_generic_type of state_3 : constant is 1;
end vending_machine;
