module IF_ID ( clk, rst, en_reg,
               ins_in, pc_in,
               ins_out, pc_out) ;

    input clk, rst, en_reg;
    input[31:0]	ins_in, pc_in;
    output[31:0] ins_out, pc_out;

    reg [31:0] ins_out, pc_out;
   
    always @( posedge clk ) begin
        if ( rst ) begin
		pc_out  <= 32'b0;
		ins_out <= 32'b0;
	end
        else if ( en_reg ) begin
		pc_out  <= pc_in;
		ins_out <= ins_in;
	end
    end
endmodule
	


