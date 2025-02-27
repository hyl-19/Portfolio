
module HiLo( clk, MulAns, HiOut, LoOut, reset, op );
input clk ;
input reset ;
input [63:0] MulAns ;
input op ;
output [31:0] HiOut ;
output [31:0] LoOut ;
reg [63:0] HiLo ;

always@( posedge clk or reset )

  if ( op == 1 )
  begin
    HiLo = HiLo + MulAns ;
  end
  else if ( op == 0 )
  begin 
    HiLo = MulAns ;
  end
  
assign HiOut = HiLo[63:32] ;
assign LoOut = HiLo[31:0] ;
endmodule