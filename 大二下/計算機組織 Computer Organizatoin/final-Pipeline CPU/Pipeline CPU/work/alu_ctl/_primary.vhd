library verilog;
use verilog.vl_types.all;
entity alu_ctl is
    generic(
        ADD             : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        SUB             : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi0, Hi1, Hi0);
        \AND\           : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi1, Hi0, Hi0);
        \OR\            : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi1, Hi0, Hi1);
        \SRL\           : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        SLT             : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi0);
        MULTU           : vl_logic_vector(0 to 5) := (Hi0, Hi1, Hi1, Hi0, Hi0, Hi1);
        MFHI            : vl_logic_vector(0 to 5) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        MFLO            : vl_logic_vector(0 to 5) := (Hi0, Hi1, Hi0, Hi0, Hi1, Hi0);
        MADDU           : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        ALU_add         : vl_logic_vector(0 to 2) := (Hi0, Hi1, Hi0);
        ALU_sub         : vl_logic_vector(0 to 2) := (Hi1, Hi1, Hi0);
        ALU_and         : vl_logic_vector(0 to 2) := (Hi0, Hi0, Hi0);
        ALU_or          : vl_logic_vector(0 to 2) := (Hi0, Hi0, Hi1);
        ALU_slt         : vl_logic_vector(0 to 2) := (Hi1, Hi1, Hi1);
        ALU_srl         : vl_logic_vector(0 to 2) := (Hi0, Hi1, Hi1)
    );
    port(
        clk             : in     vl_logic;
        ALUOp           : in     vl_logic_vector(1 downto 0);
        Funct           : in     vl_logic_vector(5 downto 0);
        ALUOperation    : out    vl_logic_vector(2 downto 0);
        SignaltoMULTU   : out    vl_logic;
        sel             : out    vl_logic_vector(1 downto 0);
        HILOOperation   : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ADD : constant is 1;
    attribute mti_svvh_generic_type of SUB : constant is 1;
    attribute mti_svvh_generic_type of \AND\ : constant is 1;
    attribute mti_svvh_generic_type of \OR\ : constant is 1;
    attribute mti_svvh_generic_type of \SRL\ : constant is 1;
    attribute mti_svvh_generic_type of SLT : constant is 1;
    attribute mti_svvh_generic_type of MULTU : constant is 1;
    attribute mti_svvh_generic_type of MFHI : constant is 1;
    attribute mti_svvh_generic_type of MFLO : constant is 1;
    attribute mti_svvh_generic_type of MADDU : constant is 1;
    attribute mti_svvh_generic_type of ALU_add : constant is 1;
    attribute mti_svvh_generic_type of ALU_sub : constant is 1;
    attribute mti_svvh_generic_type of ALU_and : constant is 1;
    attribute mti_svvh_generic_type of ALU_or : constant is 1;
    attribute mti_svvh_generic_type of ALU_slt : constant is 1;
    attribute mti_svvh_generic_type of ALU_srl : constant is 1;
end alu_ctl;
