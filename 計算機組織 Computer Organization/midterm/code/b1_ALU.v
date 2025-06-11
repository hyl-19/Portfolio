`timescale 1ns/1ns

module b1_ALU(a, b, cin, cout, signal, inv, less, out ) ;

input a, b, cin, inv, less ;
input [5:0] signal ;
output out, cout ;

wire t1, e0, e1, e2 ;

parameter AND = 6'b100100 ;
parameter OR  = 6'b100101 ;
parameter ADD = 6'b100000 ;
parameter SUB = 6'b100010 ;
parameter SLT = 6'b101010 ;

xor(t1, b, inv) ;
FA fa( .a(a), .b(t1), .c(cin), .cout(cout), .sum(e2) ) ;
and(e0, a, b) ;
or(e1, a, b) ;
			 
assign out = ( signal[3]) ? less : ( signal[2] ? (( signal[0] ) ? e1 : e0 ) : e2 );

endmodule
