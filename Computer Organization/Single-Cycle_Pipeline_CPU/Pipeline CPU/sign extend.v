/*
	Title: Sign Extend
	Author: Selene (Computer System and Architecture Lab, ICE, CYCU)
	
	Input Port
		1. immed_in: Ū�J����sign extend���
	Output Port
		1. ext_immed_out: ��X�w����sign extend���
*/
module sign_extend( clk, op, immed_in, ext_immed_out );
  input clk ;
	input[31:0] op ;
	input[15:0] immed_in;
	output [31:0] ext_immed_out;
	
	parameter BEQ = 6'd4; 
  parameter LW = 6'd35; 
  parameter SW = 6'd43;
	

		assign ext_immed_out = { 16'b0, immed_in } ;
	
	
endmodule
