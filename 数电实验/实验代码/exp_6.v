module exp_6(
	input  [7:0]  seed,
	input  clk,
	input  load,
	output [6:0] LED_0,
	output [6:0] LED_1,
	output [6:0] LED_2
	);

	reg x;
	reg [7:0] out;
	reg [6:0] led0;
	reg [6:0] led1;
	reg [6:0] led2;
	integer i=0;

	always @(posedge clk) begin
	
		if(load)
			out = seed;

		else begin
			x=out[0] ^ out[2] ^ out[3] ^ out[4];
			for(i=1;i<=7;i=i+1)
				out[i-1]=out[i];
			out[7]=x;
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