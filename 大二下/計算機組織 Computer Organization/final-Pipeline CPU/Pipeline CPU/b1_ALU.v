`timescale 1ns/1ns

module b1_ALU(a, b, cin, cout, signal, inv, less, out) ;

input a, b, cin, inv, less ;
input[1:0] signal ;
output out, cout ;

wire t1, e0, e1, e2, e3 ;


and(e0, a, b) ;
or(e1, a, b) ;
xor(t1, b, inv) ;
FA fa( .a(a), .b(t1), .c(cin), .cout(cout), .sum(e2) ) ;


assign e3 = less ;

assign out = ( signal == 2'b00 ) ? e0 :
		   ( signal == 2'b01 ) ? e1 :
		   ( signal == 2'b10 ) ? e2 :
		   ( signal == 2'b11 ) ? e3 :1'b0 ;
									 

endmodule
