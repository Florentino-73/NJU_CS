module exp_5_1(

	input clk,
	input we_1, // 为0时写入
	input we_2, // 为0时写入
	input [3:0] addr,
	input [1:0] din, // 限于输入端开关个数，数据段只保留低两位
	output [7:0] out_2,
	output [6:0] LED_0,
	output [6:0] LED_1,
	output [6:0] LED_2,
	output [6:0] LED_3

);

ram1 ram2(
	.address(addr),
	.clock(clk),
	.data(din),
	.wren(~we_2),
	.q(out_2)
	);
	
	reg [7:0] ram1 [15:0];
	reg [7:0] out_1;
	reg [6:0] led0=0;
	reg [6:0] led1=0;
	reg [6:0] led2=0;
	reg [6:0] led3=0;
	
	
initial
	begin
		//ram[7] = 8'hf0; ram[6] = 8'h23; ram[5] = 8'h20; ram[4] = 8'h50;
		//ram[3] = 8'h03; ram[2] = 8'h21; ram[1] = 8'h82; ram[0] = 8'h0D;
		$readmemh("D:/My_design/exp_5_1/mem1.txt", ram1, 0, 15);
	end

always @(posedge clk) begin

	if (we_1==0)
		ram1[addr] <= din;
		
end
	
always @(ram1[addr]) begin
	
		out_1 = ram1[addr]; 
		case(out_1%10)
			0:led0=7'b1000000;
			1:led0=7'b1111001;
			2:led0=7'b0100100;
			3:led0=7'b0110000;
			4:led0=7'b0011001;
			5:led0=7'b0010010;
			6:led0=7'b0000010;
			7:led0=7'b1111000;
			8:led0=7'b0000000;
			9:led0=7'b0010000;
		endcase
		
		case((out_1/10)%10)
			0:led1=7'b1000000;
			1:led1=7'b1111001;
			2:led1=7'b0100100;
			3:led1=7'b0110000;
			4:led1=7'b0011001;
			5:led1=7'b0010010;
			6:led1=7'b0000010;
			7:led1=7'b1111000;
			8:led1=7'b0000000;
			9:led1=7'b0010000;
		endcase

end 

always @(*) begin

		case(out_2%10)
			0:led2=7'b1000000;
			1:led2=7'b1111001;
			2:led2=7'b0100100;
			3:led2=7'b0110000;
			4:led2=7'b0011001;
			5:led2=7'b0010010;
			6:led2=7'b0000010;
			7:led2=7'b1111000;
			8:led2=7'b0000000;
			9:led2=7'b0010000;
		endcase
		
		case((out_2/10)%10)
			0:led3=7'b1000000;
			1:led3=7'b1111001;
			2:led3=7'b0100100;
			3:led3=7'b0110000;
			4:led3=7'b0011001;
			5:led3=7'b0010010;
			6:led3=7'b0000010;
			7:led3=7'b1111000;
			8:led3=7'b0000000;
			9:led3=7'b0010000;
		endcase

end 

	assign LED_0=led0;
	assign LED_1=led1;
	assign LED_2=led2;
	assign LED_3=led3;

endmodule