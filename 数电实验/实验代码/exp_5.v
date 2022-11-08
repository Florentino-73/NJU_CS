module exp_5(
	input  [3:0]  adr,    // 读口/写口地址
	input  [7:0]  data,   // 写入的数据,write data
	input  en,            // 写使能,write enable
	input  rw,            // 判断当前模式为读/写, 0为读取,1为写入
	input  clk,           //时钟
	output [6:0] LED_0,
	output [6:0] LED_1,
	output [6:0] LED_2
	);
	
/*
	initial begin
	reg [7:0] memory_array [15:0]; // 声明一个16*8的寄存器组
	$readmemh("E:/FPGA design/mem1.txt", memory_array, 0, 15);
	end
*/

	reg [7:0] register [15:0]; // 声明一个16*8的寄存器组
	reg [7:0] out;
	reg [6:0] led0;
	reg [6:0] led1;
	reg [6:0] led2;
	integer i=1;
	
	always@(posedge clk) begin
	
	// initial once
		if(i)begin
			for(i=0;i<16;i=i+1)
				register[i]=i;
		end
		
		i=0;
		
		if(rw==0) begin
			out=register[adr]; // 显示读口地址对应的寄存器内容
		end
		
		else begin
			out=data; // 显示将要写入的数据
			if(en)
				register[adr]=data;
		end

		case(out%10)
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
		
		case((out/10)%10)
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
		
		case(out/100)
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
	end
	
	assign LED_0=led0;
	assign LED_1=led1;
	assign LED_2=led2;

endmodule
