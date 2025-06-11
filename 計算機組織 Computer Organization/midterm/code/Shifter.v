`timescale 1ns/1ns
module Shifter( dataA, dataB, Signal, dataOut, reset );
input reset ;
input [31:0] dataA ;
input [31:0] dataB ;
input [5:0] Signal ;
output [31:0] dataOut ;
wire [31:0] ST1,ST2,ST3,ST4,ST5;


parameter SRL = 6'b000010;
// 1-bit  1
mux2X1 m32(dataA[31], 1'b0, ST1[31], dataB[0]);
mux2X1 m31(dataA[30], dataA[31], ST1[30], dataB[0]);
mux2X1 m30(dataA[29], dataA[30], ST1[29], dataB[0]);
mux2X1 m29(dataA[28], dataA[29], ST1[28], dataB[0]);
mux2X1 m28(dataA[27], dataA[28], ST1[27], dataB[0]);
mux2X1 m27(dataA[26], dataA[27], ST1[26], dataB[0]);
mux2X1 m26(dataA[25], dataA[26], ST1[25], dataB[0]);
mux2X1 m25(dataA[24], dataA[25], ST1[24], dataB[0]);
mux2X1 m24(dataA[23], dataA[24], ST1[23], dataB[0]);
mux2X1 m23(dataA[22], dataA[23], ST1[22], dataB[0]);
mux2X1 m22(dataA[21], dataA[22], ST1[21], dataB[0]);
mux2X1 m21(dataA[20], dataA[21], ST1[20], dataB[0]);
mux2X1 m20(dataA[19], dataA[20], ST1[19], dataB[0]);
mux2X1 m19(dataA[18], dataA[19], ST1[18], dataB[0]);
mux2X1 m18(dataA[17], dataA[18], ST1[17], dataB[0]);
mux2X1 m17(dataA[16], dataA[17], ST1[16], dataB[0]);
mux2X1 m16(dataA[15], dataA[16], ST1[15], dataB[0]);
mux2X1 m15(dataA[14], dataA[15], ST1[14], dataB[0]);
mux2X1 m14(dataA[13], dataA[14], ST1[13], dataB[0]);
mux2X1 m13(dataA[12], dataA[13], ST1[12], dataB[0]);
mux2X1 m12(dataA[11], dataA[12], ST1[11], dataB[0]);
mux2X1 m11(dataA[10], dataA[11], ST1[10], dataB[0]);
mux2X1 m10(dataA[9], dataA[10], ST1[9], dataB[0]);
mux2X1 m9(dataA[8], dataA[9], ST1[8], dataB[0]);
mux2X1 m8(dataA[7], dataA[8], ST1[7], dataB[0]);
mux2X1 m7(dataA[6], dataA[7], ST1[6], dataB[0]);
mux2X1 m6(dataA[5], dataA[6], ST1[5], dataB[0]);
mux2X1 m5(dataA[4], dataA[5], ST1[4], dataB[0]);
mux2X1 m4(dataA[3], dataA[4], ST1[3], dataB[0]);
mux2X1 m3(dataA[2], dataA[3], ST1[2], dataB[0]);
mux2X1 m2(dataA[1], dataA[2], ST1[1], dataB[0]);
mux2X1 m1(dataA[0], dataA[1], ST1[0], dataB[0]);







// 2-bit   2
mux2X1 im32(ST1[31], 1'b0, ST2[31], dataB[1]);
mux2X1 im31(ST1[30], 1'b0, ST2[30], dataB[1]);
mux2X1 im30(ST1[29], ST1[31], ST2[29], dataB[1]);
mux2X1 im29(ST1[28], ST1[30], ST2[28], dataB[1]);
mux2X1 im28(ST1[27], ST1[29], ST2[27], dataB[1]);
mux2X1 im27(ST1[26], ST1[28], ST2[26], dataB[1]);
mux2X1 im26(ST1[25], ST1[27], ST2[25], dataB[1]);
mux2X1 im25(ST1[24], ST1[26], ST2[24], dataB[1]);
mux2X1 im24(ST1[23], ST1[25], ST2[23], dataB[1]);
mux2X1 im23(ST1[22], ST1[24], ST2[22], dataB[1]);
mux2X1 im22(ST1[21], ST1[23], ST2[21], dataB[1]);
mux2X1 im21(ST1[20], ST1[22], ST2[20], dataB[1]);
mux2X1 im20(ST1[19], ST1[21], ST2[19], dataB[1]);
mux2X1 im19(ST1[18], ST1[20], ST2[18], dataB[1]);
mux2X1 im18(ST1[17], ST1[19], ST2[17], dataB[1]);
mux2X1 im17(ST1[16], ST1[18], ST2[16], dataB[1]);
mux2X1 im16(ST1[15], ST1[17], ST2[15], dataB[1]);
mux2X1 im15(ST1[14], ST1[16], ST2[14], dataB[1]);
mux2X1 im14(ST1[13], ST1[15], ST2[13], dataB[1]);
mux2X1 im13(ST1[12], ST1[14], ST2[12], dataB[1]);
mux2X1 im12(ST1[11], ST1[13], ST2[11], dataB[1]);
mux2X1 im11(ST1[10], ST1[12], ST2[10], dataB[1]);
mux2X1 im10(ST1[9], ST1[11], ST2[9], dataB[1]);
mux2X1 im9(ST1[8], ST1[10], ST2[8], dataB[1]);
mux2X1 im8(ST1[7], ST1[9], ST2[7], dataB[1]);
mux2X1 im7(ST1[6], ST1[8], ST2[6], dataB[1]);
mux2X1 im6(ST1[5], ST1[7], ST2[5], dataB[1]);
mux2X1 im5(ST1[4], ST1[6], ST2[4], dataB[1]);
mux2X1 im4(ST1[3], ST1[5], ST2[3], dataB[1]);
mux2X1 im3(ST1[2], ST1[4], ST2[2], dataB[1]);
mux2X1 im2(ST1[1], ST1[3], ST2[1], dataB[1]);
mux2X1 im1(ST1[0], ST1[2], ST2[0], dataB[1]);  

//4-bit   3
mux2X1 img32(ST2[31], 1'b0, ST3[31], dataB[2]);
mux2X1 img31(ST2[30], 1'b0, ST3[30], dataB[2]);
mux2X1 img30(ST2[29], 1'b0, ST3[29], dataB[2]);
mux2X1 img29(ST2[28], 1'b0, ST3[28], dataB[2]);
mux2X1 img28(ST2[27], ST2[31], ST3[27], dataB[2]);
mux2X1 img27(ST2[26], ST2[30], ST3[26], dataB[2]);
mux2X1 img26(ST2[25], ST2[29], ST3[25], dataB[2]);
mux2X1 img25(ST2[24], ST2[28], ST3[24], dataB[2]);
mux2X1 img24(ST2[23], ST2[27], ST3[23], dataB[2]);
mux2X1 img23(ST2[22], ST2[26], ST3[22], dataB[2]);
mux2X1 img22(ST2[21], ST2[25], ST3[21], dataB[2]);
mux2X1 img21(ST2[20], ST2[24], ST3[20], dataB[2]);
mux2X1 img20(ST2[19], ST2[23], ST3[19], dataB[2]);
mux2X1 img19(ST2[18], ST2[22], ST3[18], dataB[2]);
mux2X1 img18(ST2[17], ST2[21], ST3[17], dataB[2]);
mux2X1 img17(ST2[16], ST2[20], ST3[16], dataB[2]);
mux2X1 img16(ST2[15], ST2[19], ST3[15], dataB[2]);
mux2X1 img15(ST2[14], ST2[18], ST3[14], dataB[2]);
mux2X1 img14(ST2[13], ST2[17], ST3[13], dataB[2]);
mux2X1 img13(ST2[12], ST2[16], ST3[12], dataB[2]);
mux2X1 img12(ST2[11], ST2[15], ST3[11], dataB[2]);
mux2X1 img11(ST2[10], ST2[14], ST3[10], dataB[2]);
mux2X1 img10(ST2[9], ST2[13], ST3[9], dataB[2]);
mux2X1 img9(ST2[8], ST2[12], ST3[8], dataB[2]);
mux2X1 img8(ST2[7], ST2[11], ST3[7], dataB[2]);
mux2X1 img7(ST2[6], ST2[10], ST3[6], dataB[2]);
mux2X1 img6(ST2[5], ST2[9], ST3[5], dataB[2]);
mux2X1 img5(ST2[4], ST2[8], ST3[4], dataB[2]);
mux2X1 img4(ST2[3], ST2[7], ST3[3], dataB[2]);
mux2X1 img3(ST2[2], ST2[6], ST3[2], dataB[2]);
mux2X1 img2(ST2[1], ST2[5], ST3[1], dataB[2]);
mux2X1 img1(ST2[0], ST2[4], ST3[0], dataB[2]);  

//8-bit    4

mux2X1 imgy32(ST3[31], 1'b0, ST4[31], dataB[3]);
mux2X1 imgy31(ST3[30], 1'b0, ST4[30], dataB[3]);
mux2X1 imgy30(ST3[29], 1'b0, ST4[29], dataB[3]);
mux2X1 imgy29(ST3[28], 1'b0, ST4[28], dataB[3]);
mux2X1 imgy28(ST3[27], 1'b0, ST4[27], dataB[3]);
mux2X1 imgy27(ST3[26], 1'b0, ST4[26], dataB[3]);
mux2X1 imgy26(ST3[25], 1'b0, ST4[25], dataB[3]);
mux2X1 imgy25(ST3[24], 1'b0, ST4[24], dataB[3]);
mux2X1 imgy24(ST3[23], ST3[31], ST4[23], dataB[3]);
mux2X1 imgy23(ST3[22], ST3[30], ST4[22], dataB[3]);
mux2X1 imgy22(ST3[21], ST3[29], ST4[21], dataB[3]);
mux2X1 imgy21(ST3[20], ST3[28], ST4[20], dataB[3]);
mux2X1 imgy20(ST3[19], ST3[27], ST4[19], dataB[3]);
mux2X1 imgy19(ST3[18], ST3[26], ST4[18], dataB[3]);
mux2X1 imgy18(ST3[17], ST3[25], ST4[17], dataB[3]);
mux2X1 imgy17(ST3[16], ST3[24], ST4[16], dataB[3]);
mux2X1 imgy16(ST3[15], ST3[23], ST4[15], dataB[3]);
mux2X1 imgy15(ST3[14], ST3[22], ST4[14], dataB[3]);
mux2X1 imgy14(ST3[13], ST3[21], ST4[13], dataB[3]);
mux2X1 imgy13(ST3[12], ST3[20], ST4[12], dataB[3]);
mux2X1 imgy12(ST3[11], ST3[19], ST4[11], dataB[3]);
mux2X1 imgy11(ST3[10], ST3[18], ST4[10], dataB[3]);
mux2X1 imgy10(ST3[9], ST3[17], ST4[9], dataB[3]);
mux2X1 imgy9(ST3[8], ST3[16], ST4[8], dataB[3]);
mux2X1 imgy8(ST3[7], ST3[15], ST4[7], dataB[3]);
mux2X1 imgy7(ST3[6], ST3[14], ST4[6], dataB[3]);
mux2X1 imgy6(ST3[5], ST3[13], ST4[5], dataB[3]);
mux2X1 imgy5(ST3[4], ST3[12], ST4[4], dataB[3]);
mux2X1 imgy4(ST3[3], ST3[11], ST4[3], dataB[3]);
mux2X1 imgy3(ST3[2], ST3[10], ST4[2], dataB[3]);
mux2X1 imgy2(ST3[1], ST3[9], ST4[1], dataB[3]);
mux2X1 imgy1(ST3[0], ST3[8], ST4[0], dataB[3]);
// 16-bit    5
mux2X1 imgUy32(ST4[31], 1'b0, ST5[31], dataB[4]);
mux2X1 imgUy31(ST4[30], 1'b0, ST5[30], dataB[4]);
mux2X1 imgUy30(ST4[29], 1'b0, ST5[29], dataB[4]);
mux2X1 imgUy29(ST4[28], 1'b0, ST5[28], dataB[4]);
mux2X1 imgUy28(ST4[27], 1'b0, ST5[27], dataB[4]);
mux2X1 imgUy27(ST4[26], 1'b0, ST5[26], dataB[4]);
mux2X1 imgUy26(ST4[25], 1'b0, ST5[25], dataB[4]);
mux2X1 imgUy25(ST4[24], 1'b0, ST5[24], dataB[4]);
mux2X1 imgUy24(ST4[23], 1'b0, ST5[23], dataB[4]);
mux2X1 imgUy23(ST4[22], 1'b0, ST5[22], dataB[4]);
mux2X1 imgUy22(ST4[21], 1'b0, ST5[21], dataB[4]);
mux2X1 imgUy21(ST4[20], 1'b0, ST5[20], dataB[4]);
mux2X1 imgUy20(ST4[19], 1'b0, ST5[19], dataB[4]);
mux2X1 imgUy19(ST4[18], 1'b0, ST5[18], dataB[4]);
mux2X1 imgUy18(ST4[17], 1'b0, ST5[17], dataB[4]);
mux2X1 imgUy17(ST4[16], 1'b0, ST5[16], dataB[4]);
mux2X1 imgUy16(ST4[15], ST4[31], ST5[15], dataB[4]);
mux2X1 imgUy15(ST4[14], ST4[30], ST5[14], dataB[4]);
mux2X1 imgUy14(ST4[13], ST4[29], ST5[13], dataB[4]);
mux2X1 imgUy13(ST4[12], ST4[28], ST5[12], dataB[4]);
mux2X1 imgUy12(ST4[11], ST4[27], ST5[11], dataB[4]);
mux2X1 imgUy11(ST4[10], ST4[26], ST5[10], dataB[4]);
mux2X1 imgUy10(ST4[9], ST4[25], ST5[9], dataB[4]);
mux2X1 imgUy9(ST4[8], ST4[24], ST5[8], dataB[4]);
mux2X1 imgUy8(ST4[7], ST4[23], ST5[7], dataB[4]);
mux2X1 imgUy7(ST4[6], ST4[22], ST5[6], dataB[4]);
mux2X1 imgUy6(ST4[5], ST4[21], ST5[5], dataB[4]);
mux2X1 imgUy5(ST4[4], ST4[20], ST5[4], dataB[4]);
mux2X1 imgUy4(ST4[3], ST4[19], ST5[3], dataB[4]);
mux2X1 imgUy3(ST4[2], ST4[18], ST5[2], dataB[4]);
mux2X1 imgUy2(ST4[1], ST4[17], ST5[1], dataB[4]);
mux2X1 imgUy1(ST4[0], ST4[16], ST5[0], dataB[4]);

assign dataOut =(reset==1)?32'b0 :(Signal==6'b000010)? ST5: 32'b0 ;


endmodule