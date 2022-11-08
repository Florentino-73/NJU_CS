module exp_4(
	input clk, //50MHZ
	input start,
	input pause,
	input rst,
	output RCO,
	output [6:0] LED_0,
	output [6:0] LED_1
);
	
	integer count_clk=0;
	integer cnt=0;
	reg clk_1s=0;
	reg rco=0;
	reg [6:0] led_0;
	reg [6:0] led_1;
	
	always @(posedge clk) 
	begin
		
		if(count_clk==49999999)
		begin
			count_clk = 0;
			
			if(rst==1) cnt=0;
			
			else begin
			
				if(pause==0) begin
					
					if(cnt==99) begin
						cnt=0;
						rco=1;
					end
					
					else begin
						cnt=cnt+1;
						rco=0;
					end
						
				end
				
			end
				
			led_0=7'b1111111;
			led_1=7'b1111111;
			if(start) begin
			
				case(cnt%10)
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
				
				case(cnt/10)
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
				
			end
			
		end
		
		else
			count_clk <= count_clk+1;
	end
	
	
	assign RCO=rco;
	assign LED_1=led_1;
	assign LED_0=led_0;
	
endmodule
