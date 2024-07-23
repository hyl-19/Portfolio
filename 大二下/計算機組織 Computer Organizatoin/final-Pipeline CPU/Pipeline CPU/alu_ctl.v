/*
	Title:	ALU Control Unit
	Author: Garfield (Computer System and Architecture Lab, ICE, CYCU)
	Input Port
		1. ALUOp:     alu O n  + ٬O- άO  L   O
		2. Funct:  p G O  L   O h γo  6 X P _
	Output Port
		1. ALUOperation:  ̫ ѽX         O
*/

module alu_ctl(clk, ALUOp, Funct, ALUOperation, SignaltoMULTU, sel, HILOOperation); // clk, signaltoMULT
    input clk ;
    input [1:0] ALUOp;
    input [5:0] Funct;
    output SignaltoMULTU;
    output [1:0] sel;
    output [2:0] ALUOperation;
    output HILOOperation ;
    reg    SignaltoMULTU = 1'b0;
    
    reg    [1:0] sel;
    reg    [2:0] ALUOperation;
    reg    [6:0] count ;
    reg    HILOOperation ;
    // symbolic constants for instruction function code
    parameter ADD = 6'd32;
    parameter SUB = 6'd34;
    parameter AND = 6'd36;
    parameter OR  = 6'd37;
    parameter SRL = 6'd2;
    parameter SLT = 6'd42;
    parameter MULTU = 6'd25;
    parameter MFHI = 6'd16; 
    parameter MFLO = 6'd18; 
    parameter MADDU = 6'd1;

    // symbolic constants for ALU Operations
    parameter ALU_add = 3'b010;
    parameter ALU_sub = 3'b110;
    parameter ALU_and = 3'b000;
    parameter ALU_or  = 3'b001;
    parameter ALU_slt = 3'b111;
    parameter ALU_srl = 3'b011; 
    
    always @( Funct )
    begin
		if ( Funct == MULTU || Funct == MADDU )
		  begin
            SignaltoMULTU <= 1'b1;
		    count = 0 ;
		  end
	  end

    always @(ALUOp or Funct)
    begin
	
	sel = 2'b0;
        case (ALUOp) 
            2'b00 : ALUOperation = ALU_add;
            2'b01 : ALUOperation = ALU_sub;
            2'b10 : case (Funct) 
                        ADD : ALUOperation = ALU_add;
                        SUB : ALUOperation = ALU_sub;
                        AND : ALUOperation = ALU_and;
                        OR  : ALUOperation = ALU_or;
                        SLT : ALUOperation = ALU_slt;
                        SRL : ALUOperation = ALU_srl;
                        MULTU : 
                        begin
                            SignaltoMULTU = 1'b1;
                            sel = 2'b00; 
                            #(330) HILOOperation = 1'b0 ;
                            #(10) HILOOperation = 1'bx ;
                        end
                        MFHI : sel = 2'b01;
                        MFLO : sel = 2'b10;
                        MADDU :
                        begin 
                            SignaltoMULTU = 1'b1 ;
                            sel = 2'b00 ;
                            #(330) HILOOperation = 1'b1 ;
                            #(10) HILOOperation = 1'bx ;
                        end

                        default
                            begin
                                ALUOperation = 3'bxxx;

                            end
                    endcase
            default
                begin
                    ALUOperation = 3'bxxx;
                   
                end
        endcase
    end

    always @( posedge clk )
	begin
				
		if ( SignaltoMULTU == 1'b1 )
	    begin
			count = count + 1 ;
			SignaltoMULTU = 1'b1; 

			
			if ( count == 32 )
			begin
				SignaltoMULTU = 1'b0; 
				count = -6'b1 ;
			end
		end
		
	end

endmodule

