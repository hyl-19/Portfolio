//	Title: MIPS Single-Cycle Processor
//	Editor: Selene (Computer System and Architecture Lab, ICE, CYCU)


module mips_pipelined( clk, rst );
	input clk, rst;
	
	// instruction bus
	wire[31:0] instr ;
	
	// break out important fields from instruction
	wire alusrc, regdst, memtoreg, rf_writeback, mem_read, mem_write ;
	wire [1:0] alu_sel_mux, aluop ;
	wire [5:0] opcode, funct, funct_out;
    wire [4:0] rs, rt, rt_out, rd, rd_out, shamt, shamt_out;
    wire [15:0] immed;
    wire [31:0] extend_immed, b_offset, extend_out;
    wire [25:0] jumpoffset;
	wire [63:0] MulAns;
	
	// datapath signals
    wire [4:0] rfile_wn, rfile_wn_EXMEMout, rfile_wn_MEMWBout;

	wire [31:0] rfile_rd1, rfile_rd2, rfile_wd, alu_b, alu_out, b_tgt, pc_next,
                pc, pc_incr, dmem_rdata, jump_addr, branch_addr,
				rd1_out, rd2_out, rd2ToWD, alu_ans,
				aluToADDR, ADDR_out, HiOut, LoOut, 
                DM_RD_MEMWBout;

	// control signals
    wire RegWrite, Branch, PCSrc, RegDst, MemtoReg, MemRead, MemWrite, ALUSrc, Zero, Jump, Multu ;

    wire [1:0] ALUOp;
    wire [2:0] Operation;
	wire  	HiLoOP ;
	
	wire [1:0] WB_reg, MEM_reg ;
	wire [1:0] WB_reg_IDEXout, WB_reg_EXMEMout, WB_reg_MEMWBout;
	wire [1:0] MEM_reg_IDEXout, MEM_reg_EXMEMout;
	wire [3:0] EX_reg, EX_reg_IDEXout;

	assign WB_reg = { MemtoReg, RegWrite };   
	assign MEM_reg = { MemWrite, MemRead };  
	assign EX_reg = { ALUSrc, RegDst, ALUOp }; 
	
	wire[31:0] instr_out, pc_incr_out ; // for 1 block
    assign opcode = instr_out[31:26];
    assign rs = instr_out[25:21];
    assign rt = instr_out[20:16];
    assign rd = instr_out[15:11];
    assign shamt = instr_out[10:6];
    assign funct = instr_out[5:0];
    assign immed = instr_out[15:0];
    assign jumpoffset = instr_out[25:0];
	assign alusrc = EX_reg_IDEXout[3] ;
	assign regdst = EX_reg_IDEXout[2] ;
	assign aluop = EX_reg_IDEXout[1:0] ;
	assign mem_read = MEM_reg_EXMEMout[0] ;
	assign mem_write = MEM_reg_EXMEMout[1] ;
	assign memtoreg = WB_reg_MEMWBout[1] ;
	assign rf_writeback = WB_reg_MEMWBout[0] ;

    assign b_offset = extend_immed << 2;
	
	// jump offset shifter & concatenation
	assign jump_addr = { pc_incr[31:28], jumpoffset <<2 };

	// module instantiations
	//============1========================================
	

	reg32 PC( .clk(clk), .rst(rst), .en_reg(1'b1), .d_in(pc_next), .d_out(pc) );  

	add32 PCADD( .a(pc), .b(32'd4), .result(pc_incr) );

	memory InstrMem( .clk(clk), .MemRead(1'b1), .MemWrite(1'b0), .wd(32'd0), .addr(pc), .rd(instr) );

	mux2 #(32) PCMUX( .sel(PCSrc), .a(pc_incr), .b(b_tgt), .y(branch_addr) );	
	
	mux2 #(32) JMUX( .sel(Jump), .a(branch_addr), .b(jump_addr), .y(pc_next) );

	and BR_AND(PCSrc, Branch, Zero);

	IF_ID IFID_reg( .clk(clk), .rst(rst), .en_reg(1'b1),
					.ins_in(instr), .pc_in(pc_incr), 
					.ins_out(instr_out), .pc_out(pc_incr_out) );

	//============2========================================

	reg_file RegFile( .clk(clk), .RegWrite(rf_writeback),
					  .RN1(rs), .RN2(rt), .WN(rfile_wn_MEMWBout), .WD(rfile_wd),
					  .RD1(rfile_rd1), .RD2(rfile_rd2) );

	branch_equ equ( .opcode(opcode), .zero(Zero), .a(rfile_rd1), .b(rfile_rd2) );

	sign_extend sign_extendto32( .clk(clk), .op(instr_out), .immed_in(immed), .ext_immed_out(extend_immed) );

	add32 BRADD( .a(pc_incr_out), .b(b_offset), .result(b_tgt) );

	control_pipelined ctr_pipeline(.opcode(opcode), .RegDst(RegDst), .ALUSrc(ALUSrc), .MemtoReg(MemtoReg), 
                       	  		   .RegWrite(RegWrite), .MemRead(MemRead), .MemWrite(MemWrite),
								   .Branch(Branch), .Jump(Jump), .ALUOp(ALUOp) );

	ID_EX IDEX_reg( .clk(clk), .rst(rst), .en_reg(1'b1),
					.WB_in(WB_reg), .MEM_in(MEM_reg), .EX_in(EX_reg),
					.shamt_in(shamt), .funct_in(funct),
					.RD1_in(rfile_rd1), .RD2_in(rfile_rd2), .immed_in(extend_immed), .rt_in(rt), .rd_in(rd),
					
					.WB_out(WB_reg_IDEXout), .MEM_out(MEM_reg_IDEXout), .EX_out(EX_reg_IDEXout),
					.shamt_out(shamt_out), .funct_out(funct_out), 
					.RD1_out(rd1_out), .RD2_out(rd2_out), .immed_out(extend_out), .rt_out(rt_out), .rd_out(rd_out));

	//============3========================================

	mux2 #(32) ALUMUX( .sel(alusrc), .a(rd2_out), .b(extend_out), .y(alu_b) ); //alusrc

	ALU ALU( .ctl(Operation), .dataA(rd1_out), .dataB(alu_b), .shamt(shamt_out), .result(alu_ans) );

	multiplier multiplier( .clk(clk), .dataA(rd1_out), .dataB(rd2_out), .Signal(Multu), .dataOut(MulAns), .reset(rst) );
	
	HiLo HiLo( .clk(clk), .MulAns(MulAns), .HiOut(HiOut), .LoOut(LoOut), .reset(rst), .op(HiLoOP) );

	mux2 #(5) RFMUX( .sel(regdst), .a(rt_out), .b(rd_out), .y(rfile_wn) ); //regdst

	alu_ctl ALUCTL( .clk(clk), .ALUOp(aluop), .Funct(funct_out), .ALUOperation(Operation), .SignaltoMULTU(Multu), .sel(alu_sel_mux), .HILOOperation(HiLoOP) );

	mux3 #(32) out_mux( .sel(alu_sel_mux), .a(alu_ans), .b(HiOut), .c(LoOut), .y(alu_out) ); //ex

	EX_MEM EXMEM_reg( .clk(clk), .rst(rst), .en_reg(1'b1),
					  .WB_in(WB_reg_IDEXout), .MEM_in(MEM_reg_IDEXout), .alu_in(alu_out), .RD2_in(rd2_out), .WN_in(rfile_wn), 	
					  .WB_out(WB_reg_EXMEMout), .MEM_out(MEM_reg_EXMEMout), .alu_out(aluToADDR), .RD2_out(rd2ToWD), .WN_out(rfile_wn_EXMEMout));

	//============4========================================

	memory DatMem( .clk(clk), .MemRead(mem_read), .MemWrite(mem_write), .wd(rd2ToWD), .addr(aluToADDR), .rd(dmem_rdata) );


	MEM_WB MEMWB_reg( .clk(clk), .rst(rst), .en_reg(1'b1), 
					  .WB_in(WB_reg_EXMEMout), .RD_in(dmem_rdata), .ADDR_in(aluToADDR), .WN_in(rfile_wn_EXMEMout),
					  .WB_out(WB_reg_MEMWBout), .RD_out(DM_RD_MEMWBout), .ADDR_out(ADDR_out), .WN_out(rfile_wn_MEMWBout) );
	//============5========================================

	mux2 #(32) WRMUX( .sel(memtoreg), .a(ADDR_out), .b(DM_RD_MEMWBout), .y(rfile_wd) );
	//=====================================================
			   
endmodule
