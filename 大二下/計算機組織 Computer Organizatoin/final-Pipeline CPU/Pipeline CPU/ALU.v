`timescale 1ns/1ns
module ALU( dataA, dataB, ctl, result, shamt ) ;
  input  [2:0]  ctl ; 
  input  [4:0]  shamt;
  input  [31:0] dataA, dataB ;
  output [31:0] result ;

  wire [31:0] sll_out, temp ;
  wire [30:0] cin ;
  wire [1:0] sel ;
  wire set, cout, inv ;
  assign sel = ctl[1:0];
  assign inv = ctl[2];


b1_ALU alu0( .a(dataA[0]), .b(dataB[0]), .cin(inv), .cout(cin[0]), .signal(sel), .inv(inv), .less(set), .out(temp[0]) ) ;
b1_ALU alu1( .a(dataA[1]), .b(dataB[1]), .cin(cin[0]), .cout(cin[1]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[1]) ) ;
b1_ALU alu2( .a(dataA[2]), .b(dataB[2]), .cin(cin[1]), .cout(cin[2]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[2]) ) ;
b1_ALU alu3( .a(dataA[3]), .b(dataB[3]), .cin(cin[2]), .cout(cin[3]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[3]) ) ;
b1_ALU alu4( .a(dataA[4]), .b(dataB[4]), .cin(cin[3]), .cout(cin[4]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[4]) ) ;
b1_ALU alu5( .a(dataA[5]), .b(dataB[5]), .cin(cin[4]), .cout(cin[5]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[5]) ) ;
b1_ALU alu6( .a(dataA[6]), .b(dataB[6]), .cin(cin[5]), .cout(cin[6]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[6]) ) ;
b1_ALU alu7( .a(dataA[7]), .b(dataB[7]), .cin(cin[6]), .cout(cin[7]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[7]) ) ;
b1_ALU alu8( .a(dataA[8]), .b(dataB[8]), .cin(cin[7]), .cout(cin[8]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[8]) ) ;
b1_ALU alu9( .a(dataA[9]), .b(dataB[9]), .cin(cin[8]), .cout(cin[9]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[9]) ) ;
b1_ALU alu10( .a(dataA[10]), .b(dataB[10]), .cin(cin[9]), .cout(cin[10]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[10]) ) ;
b1_ALU alu11( .a(dataA[11]), .b(dataB[11]), .cin(cin[10]), .cout(cin[11]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[11]) ) ;
b1_ALU alu12( .a(dataA[12]), .b(dataB[12]), .cin(cin[11]), .cout(cin[12]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[12]) ) ;
b1_ALU alu13( .a(dataA[13]), .b(dataB[13]), .cin(cin[12]), .cout(cin[13]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[13]) ) ;
b1_ALU alu14( .a(dataA[14]), .b(dataB[14]), .cin(cin[13]), .cout(cin[14]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[14]) ) ;
b1_ALU alu15( .a(dataA[15]), .b(dataB[15]), .cin(cin[14]), .cout(cin[15]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[15]) ) ;
b1_ALU alu16( .a(dataA[16]), .b(dataB[16]), .cin(cin[15]), .cout(cin[16]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[16]) ) ;
b1_ALU alu17( .a(dataA[17]), .b(dataB[17]), .cin(cin[16]), .cout(cin[17]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[17]) ) ;
b1_ALU alu18( .a(dataA[18]), .b(dataB[18]), .cin(cin[17]), .cout(cin[18]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[18]) ) ;
b1_ALU alu19( .a(dataA[19]), .b(dataB[19]), .cin(cin[18]), .cout(cin[19]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[19]) ) ;
b1_ALU alu20( .a(dataA[20]), .b(dataB[20]), .cin(cin[19]), .cout(cin[20]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[20]) ) ;
b1_ALU alu21( .a(dataA[21]), .b(dataB[21]), .cin(cin[20]), .cout(cin[21]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[21]) ) ;
b1_ALU alu22( .a(dataA[22]), .b(dataB[22]), .cin(cin[21]), .cout(cin[22]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[22]) ) ;
b1_ALU alu23( .a(dataA[23]), .b(dataB[23]), .cin(cin[22]), .cout(cin[23]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[23]) ) ;
b1_ALU alu24( .a(dataA[24]), .b(dataB[24]), .cin(cin[23]), .cout(cin[24]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[24]) ) ;
b1_ALU alu25( .a(dataA[25]), .b(dataB[25]), .cin(cin[24]), .cout(cin[25]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[25]) ) ;
b1_ALU alu26( .a(dataA[26]), .b(dataB[26]), .cin(cin[25]), .cout(cin[26]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[26]) ) ;
b1_ALU alu27( .a(dataA[27]), .b(dataB[27]), .cin(cin[26]), .cout(cin[27]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[27]) ) ;
b1_ALU alu28( .a(dataA[28]), .b(dataB[28]), .cin(cin[27]), .cout(cin[28]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[28]) ) ;
b1_ALU alu29( .a(dataA[29]), .b(dataB[29]), .cin(cin[28]), .cout(cin[29]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[29]) ) ;
b1_ALU alu30( .a(dataA[30]), .b(dataB[30]), .cin(cin[29]), .cout(cin[30]), .signal(sel), .inv(inv), .less(1'b0), .out(temp[30]) ) ;
msb_alu alu31( .a(dataA[31]), .b(dataB[31]), .cin(cin[30]), .cout(cout), .signal(sel), .inv(inv), .less(1'b0), .out(temp[31]), .set(set) ) ;

Shifter u_shifter( .dataA(dataB), .dataB(shamt), .dataOut(sll_out) );
assign result = (ctl == 3'b011)? sll_out : temp ;

endmodule