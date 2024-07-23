`timescale 1ns/1ns
module Multiplier( clk, dataA, dataB, Signal, dataOut, reset );
input clk ;
input reset ;
input [31:0] dataA ;
input [31:0] dataB ;
input [5:0] Signal ;
output [63:0] dataOut ;
reg [63:0] multiplicand ;
reg [31:0] multiplier ;
reg [63:0] outreg ;

//   Signal ( 6-bits)?
//   MULT : 25

reg [63:0] temp ;
parameter MULT = 6'b011001;
parameter OUT = 6'b111111;

always@( posedge clk or reset )
begin
    if ( reset )
    begin
		  outreg = 64'b0 ;
      	  temp = 64'b0 ;
		  multiplicand = { 32'b0, dataA } ;
		  multiplier = dataB ;
    end
        
    else
    begin
	case ( Signal )
 	MULT:
	begin
		
		if ( multiplier[0] == 1'b1 ) 
		begin
			temp = temp + multiplicand ;
		end
			multiplier = ( multiplier >> 1 ) ;
		  multiplicand = ( multiplicand << 1 ) ;

	end
	OUT:
	begin
		outreg = temp ;
	end
	endcase
    end
end

assign dataOut = outreg ;

endmodule
