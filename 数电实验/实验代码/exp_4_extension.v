module exp_4_extension(
	input clk, 
	input [1:0] choice, //选择端，为00时关机，为11时开机，为01时调整分钟，为10时调整时钟
	input [3:0] data_0, //个位
	input [3:0] data_1, //十位
	
	output [6:0] LED_0,
	output [6:0] LED_1,
	output [6:0] LED_2,
	output [6:0] LED_3,
	output [6:0] LED_4,
	output [6:0] LED_5
);

	
	integer count_clk=0;
	integer second=0;
	integer minute=0;
	integer hour=0;
	
	reg [6:0] led_0;
	reg [6:0] led_1;
	reg [6:0] led_2;
	reg [6:0] led_3;
	reg [6:0] led_4;
	reg [6:0] led_5;
	
	always @(posedge clk) 
	begin
	if(choice!=0) begin
		if(count_clk==49999999)
		begin
			count_clk = 0;
			
			if(choice==1) 
				minute=data_0+data_1*10;
			if(choice==2)
				hour=data_0+data_1*10;
			if(choice==3) begin
			
				if(second==59) begin
					second=0;
					minute=minute+1;
					if(minute==59) begin
						minute=0;
						hour=hour+1;
						if(hour==23)
							hour=0;
					end
				end	
				else 
					second=second+1;

			end
	
			led_0=7'b1111111;
			led_1=7'b1111111;
			led_2=7'b1111111;
			led_3=7'b1111111;
			led_4=7'b1111111;
			led_5=7'b1111111;
			
			case(second%10)
				0: led_0=7'b1000000;
				1: led_0=7'b1111001;
				2: led_0=7'b0100100;
				3: led_0=7'b0110000;
				4: led_0=7'b0011001;
				5: led_0=7'b0010010;
				6: led_0=7'b0000010;
				7: led_0=7'b1111000;
				8: led_0=7'b0000000;
				9: led_0=7'b0010000;
			endcase
				
			case(second/10)
				0: led_1=7'b1000000;
				1: led_1=7'b1111001;
				2: led_1=7'b0100100;
				3: led_1=7'b0110000;
				4: led_1=7'b0011001;
				5: led_1=7'b0010010;
				6: led_1=7'b0000010;
				7: led_1=7'b1111000;
				8: led_1=7'b0000000;
				9: led_1=7'b0010000;
			endcase
			
			case(minute%10)
				0: led_2=7'b1000000;
				1: led_2=7'b1111001;
				2: led_2=7'b0100100;
				3: led_2=7'b0110000;
				4: led_2=7'b0011001;
				5: led_2=7'b0010010;
				6: led_2=7'b0000010;
				7: led_2=7'b1111000;
				8: led_2=7'b0000000;
				9: led_2=7'b0010000;
			endcase
				
			case(minute/10)
				0: led_3=7'b1000000;
				1: led_3=7'b1111001;
				2: led_3=7'b0100100;
				3: led_3=7'b0110000;
				4: led_3=7'b0011001;
				5: led_3=7'b0010010;
				6: led_3=7'b0000010;
				7: led_3=7'b1111000;
				8: led_3=7'b0000000;
				9: led_3=7'b0010000;
			endcase
			
			case(hour%10)
				0: led_4=7'b1000000;
				1: led_4=7'b1111001;
				2: led_4=7'b0100100;
				3: led_4=7'b0110000;
				4: led_4=7'b0011001;
				5: led_4=7'b0010010;
				6: led_4=7'b0000010;
				7: led_4=7'b1111000;
				8: led_4=7'b0000000;
				9: led_4=7'b0010000;
			endcase
				
			case(hour/10)
				0: led_5=7'b1000000;
				1: led_5=7'b1111001;
				2: led_5=7'b0100100;
				3: led_5=7'b0110000;
				4: led_5=7'b0011001;
				5: led_5=7'b0010010;
				6: led_5=7'b0000010;
				7: led_5=7'b1111000;
				8: led_5=7'b0000000;
				9: led_5=7'b0010000;
			endcase
			
		end
		
		else
			count_clk <= count_clk+1;
	end
	end
	
	assign LED_0=led_0;
	assign LED_1=led_1;
	assign LED_2=led_2;
	assign LED_3=led_3;
	assign LED_4=led_4;
	assign LED_5=led_5;
	
endmodule
