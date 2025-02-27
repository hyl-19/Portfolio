/*
	Title: Memory
	Author: Selene (Computer System and Architecture Lab, ICE, CYCU)
	
	Input Port
		1. clk
		2. MemRead: ����O����O�_�iŪ��
		3. MemWrite: ����O����O�_�i�g�J
		4. wd: �g�J���O������
		5. addr: ���s�����O�����m
	Output Port
		1. rd: Ū�����O������
*/
module memory( clk, MemRead, MemWrite, wd, addr, rd );
	input clk, MemRead, MemWrite;
	input[31:0] addr, wd;
	output[31:0] rd;
	reg[31:0] rd;
	
	// Memory size: 1KB.
	reg [7:0] mem_array [0:1023];
	
	
	// �H�U���ܫ��w�O�����mŪ����� 
	always @( MemRead or mem_array[addr] or mem_array[addr+1] or 
			  mem_array[addr+2] or mem_array[addr+3] ) begin
		if ( MemRead == 1'b1 ) begin
			rd[7:0] = mem_array[addr];
			rd[15:8] = mem_array[addr+1];
			rd[23:16] = mem_array[addr+2];
			rd[31:24] = mem_array[addr+3];
			$display( "%d, reading data: Mem[%d] => %d", $time/10, addr, rd );
		end
		else rd = 32'hxxxxxxxx;
	end
	
	// �H�U�N��Ƽg�J���w�O�����m
	always @( posedge clk ) begin
		if ( MemWrite == 1'b1 ) begin
			$display( "%d, writing data: Mem[%d] <= %d", $time/10, addr, wd );
			mem_array[addr] <= wd[7:0];
			mem_array[addr+1] <= wd[15:8];
			mem_array[addr+2] <= wd[23:16];
			mem_array[addr+3] <= wd[31:24];
		end
	end
	
endmodule

