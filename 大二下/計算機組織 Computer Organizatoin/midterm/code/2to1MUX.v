module mux2X1( in0,in1,out,sel);
input in0,in1;
input sel;
output out;
assign out=(sel)?in1:in0;
endmodule
