module exp_7(
   input clk,
	input clrn,
	input ps2_clk,
	input ps2_data,
	
	output reg [7:0] cur_key,
	output reg [7:0] ascii_key,
	output reg [7:0] key_count,
	
	output reg [6:0] led0,
	output reg [6:0] led1,
	output reg [6:0] led2,
	output reg [6:0] led3,
	output reg [6:0] led4,
	output reg [6:0] led5,
	
	output reg shift_led,
	output reg ctrl_led,
	output reg caps_led
	);
	
	wire [7:0] keydata;
	wire ready;
	wire nextdata_n;
   wire overflow;
   reg next;
   reg out;
	
	reg ctrl_state = 0;
	reg shift_state = 0;
	reg caps_state = 0;
	wire bool;
	wire [7:0] ascii_KEY;
	
	ASCII ascii_tab(
		.address(cur_key),
		.clock(clk),
		.q(ascii_KEY)
	);
	
	ps2_keyboard mykey(clk, clrn, ps2_clk, ps2_data, keydata, ready, nextdata_n, overflow);
   is_char Aa(key_data,bool);	 
	
always@ (posedge clk) 
begin
	 ascii_key <= ascii_KEY;
	 
    if(clrn == 0) begin
        key_count <= 0; cur_key <= 0; next <= 1; out <= 0;
    end

    else begin
    if(nextdata_n == 0)
        next <= 1; 	 
		  
    else if(ready == 1) 
        begin
        next <= 0;
		  
		  // 按下新的按键
        if(out == 0 && keydata != 8'b11110000 && keydata != cur_key) 
            begin
				
				if(keydata == 2'h14)
					ctrl_state <= 1; 
				if(keydata == 2'h12)
					shift_state <= 1; 
				if(keydata == 2'h58)
					caps_state <= 1;		
					
            cur_key <= keydata;
				
				if(ctrl_state == 1)
					ctrl_led <= 1;
				if(shift_state == 1)
					shift_led <= 1;
				if(caps_state == 1)
					caps_led <= 1;
				
				// 判断大写
				if(bool == 1 && (caps_state == 1||shift_state == 1))
					ascii_key <= ascii_key - 32;
					
            key_count <= key_count + 1;
            end
				
		   // 按住上次的按键
        else if(keydata == cur_key) 
            cur_key <= keydata;
				
			// 松开上次的按键
        else 
				if(out == 1 && keydata == 2'h14)
					ctrl_state <= 0;
				if(out == 1 && keydata == 2'h12)
					shift_state <= 0;
				if(out == 1 && keydata == 2'h58)
					caps_state <= 0;
					
            cur_key <= 0; 
				
			// out 记录是否是断码
        if(keydata == 8'b11110000)
            out <= 1;
        else 
            out <= 0;
        end
    end
	 
	case(cur_key%16)
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
		10:led0=7'b0001000;
		11:led0=7'b0000011;
		12:led0=7'b1000110;
		13:led0=7'b0100001;
		14:led0=7'b0000110;
		15:led0=7'b0001110;
	endcase
	case(cur_key/16)
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
		10:led1=7'b0001000;
		11:led1=7'b0000011;
		12:led1=7'b1000110;
		13:led1=7'b0100001;
		14:led1=7'b0000110;
		15:led1=7'b0001110;
	endcase	
	case(ascii_key%16)
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
		10:led2=7'b0001000;
		11:led2=7'b0000011;
		12:led2=7'b1000110;
		13:led2=7'b0100001;
		14:led2=7'b0000110;
		15:led2=7'b0001110;
	endcase
	case(ascii_key/16)
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
		10:led3=7'b0001000;
		11:led3=7'b0000011;
		12:led3=7'b1000110;
		13:led3=7'b0100001;
		14:led3=7'b0000110;
		15:led3=7'b0001110;
	endcase
	case(key_count%10)
		0:led4=7'b1000000;
		1:led4=7'b1111001;
		2:led4=7'b0100100;
		3:led4=7'b0110000;
		4:led4=7'b0011001;
		5:led4=7'b0010010;
		6:led4=7'b0000010;
		7:led4=7'b1111000;
		8:led4=7'b0000000;
		9:led4=7'b0010000;
	endcase
	case((key_count/10)%10)
		0:led5=7'b1000000;
		1:led5=7'b1111001;
		2:led5=7'b0100100;
		3:led5=7'b0110000;
		4:led5=7'b0011001;
		5:led5=7'b0010010;
		6:led5=7'b0000010;
		7:led5=7'b1111000;
		8:led5=7'b0000000;
		9:led5=7'b0010000;
	endcase
end

assign nextdata_n = next;
endmodule

module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,ready,nextdata_n,overflow);
    input clk,clrn,ps2_clk,ps2_data;
	 input nextdata_n;
    output [7:0] data;
    output reg ready;
    output reg overflow;     
    reg [9:0] buffer;       
    reg [7:0] fifo[7:0];     
	 reg [2:0] w_ptr,r_ptr;   
    reg [3:0] count; 
    reg [2:0] ps2_clk_sync;
    
    always @(posedge clk) begin
        ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
    end

    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];
    
    always @(posedge clk) begin
        if (clrn == 0) begin 
            count <= 0; w_ptr <= 0; 
            r_ptr <= 0; overflow <= 0;ready<= 0;
        end 
		else if (sampling) begin
            if (count == 4'd10) begin
                if ((buffer[0] == 0) &&  
                    (ps2_data)       &&  
                    (^buffer[9:1])) begin      
                    fifo[w_ptr] <= buffer[8:1];  
                    w_ptr <= w_ptr+3'b1;
                    ready <= 1'b1;
                    overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
                end
                count <= 0;     
            end else begin
                buffer[count] <= ps2_data;  
                count <= count + 3'b1;
            end      
        end
        if ( ready ) begin 
				if(nextdata_n == 1'b0)
				begin
				   r_ptr <= r_ptr + 3'b1; 
					if(w_ptr==(r_ptr+1'b1)) 
					     ready <= 1'b0;
				end           
        end
    end
    assign data = fifo[r_ptr];
endmodule 


module is_char(indata,outdata);
input [7:0] indata;
output reg outdata;
always @(*)
begin
   outdata = 0;
	if(indata == 2'h15	||
		indata == 2'h1D	||
		indata == 2'h24	||
		indata == 2'h2D	||
		indata == 2'h2C	||
		indata == 2'h35	||
		indata == 2'h3C	||
		indata == 2'h43	||
		indata == 2'h44	||
		indata == 2'h4D	||
		indata == 2'h1C	||
		indata == 2'h1B	||
		indata == 2'h23	||
		indata == 2'h2B	||
		indata == 2'h34	||
		indata == 2'h33	||
		indata == 2'h3B	||
		indata == 2'h42	||
		indata == 2'h4B	||
		indata == 2'h1A	||
		indata == 2'h22	||
		indata == 2'h21	||
		indata == 2'h2A	||
		indata == 2'h32	||
		indata == 2'h31	||
		indata == 2'h3A	
		)
			outdata <= 1;
end
endmodule

