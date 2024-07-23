module stimulus;
  
reg clk, reset, r;
wire [7:0] o;
reg [7:0] i;
reg[1:0] s;

Shift_Register SR(i, s, o, clk, reset, r) ;

initial clk = 1'b0;
always #5 clk = ~clk;


initial
begin


 reset = 1'b1;
 i = 8'b00000000;
 s = 2'b00;
 r = 1'b0;

 #5
 reset = 1'b0;
 
 #5
 i = 8'b10100101;
 s = 2'b11;
 
 #10
 i = 8'b01111011;
 s = 2'b00;
 
 #10
 s = 2'b01;
 
 #10
 s = 2'b10;
 r = 1'b1;
 
 #5
 s = 2'b11;
 
 #5
 s = 2'b01;
 r = 1'b0;
 
 #10
 s = 2'b11;
 
 #5
 s = 2'b10;
 
 #5
 s = 2'b00;
 
 #5
 reset = 1'b1;
 
 #5
 reset = 1'b0;
 s = 2'b01;
 r = 1'b1;
 
end



endmodule
