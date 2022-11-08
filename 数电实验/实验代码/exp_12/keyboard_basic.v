module keyboard_basic(
	input 		          		clk,
	//////////// Seg7 //////////
	//output		     [6:0]		HEX2,
	//output		     [6:0]		HEX3,
	output [7:0] data,
	//////////// PS2 //////////
	inout 		          		ps2_clk,
	inout 		          		ps2_data
);
wire [7:0] bigdata;
reg shift;
reg cap;
wire [7:0]keydata;//从keyboard接收到的数据
reg [7:0]cur_key;//要显示在数码管上的数据
wire ready,overflow;
reg nextdata_n,duanma;
reg [299:0]haxi;
reg [7:0]key_count;
initial begin
	duanma=0;
	key_count=0;
	cur_key=0;
	nextdata_n=1;
	haxi=300'b0;
end
integer reading=0;
ps2_keyboard mykey(clk, 1'b1, ps2_clk, ps2_data, keydata, ready, nextdata_n, overflow);
//---DO NOT CHANGE END-----
always @ (posedge clk) begin
    if(reading==0&&ready==1) begin  //父模块已经准备好下一次读取，子模块已经准备好下一次读取
        nextdata_n<=0;//通知子模块，父模块已经准备好
		reading<=1;
	end
    if(reading==1) begin
		  reading<=0;
		  nextdata_n<=1;
        if(keydata==8'b11110000) //读到F0h，记录下来，等待下一次读取
            duanma<=1;
        else begin
            if(duanma==0)begin//如果上一次读取不是F0h
                if(haxi[keydata]==0) begin
                    haxi[keydata]<=1;
                    cur_key<=keydata;
						  
					if(keydata==8'b01011010)//enter
						key_count<=((key_count+69)/70)*70;
						else if(keydata==8'b00010010)
							shift<=1;
						else
                    key_count<=key_count+1;
                end
            end
            else begin
				if(keydata==8'b00010010)
							shift<=0;
				if(keydata==8'b01011000)begin
							if(cap==0)
								cap<=1;
							if(cap==1)
								cap<=0;
						end
					haxi[keydata]<=0;
               duanma<=0;
					cur_key<=0;
            end
        end
    end
end
wire [7:0]asc2;
wire [7:0]big_asc2;
assign data=asc2;
assign big_data=big_asc2;
regpile my_reg(cur_key[7:0],asc2[7:0]);
big_regpile big_reg(cur_key[7:0],big_asc2[7:0]);
//bcd7seg bcd2(cur_key[3:0],HEX2);
//bcd7seg bcd3(cur_key[7:4],HEX3);
endmodule
module big_regpile(
	input [7:0]address,
	output [7:0]dout
	);
	reg [7:0] regs[255:0];//256个八位寄存器	
	initial begin
		$readmemh("capcode.txt", regs, 0, 255);
	end
	assign dout=regs[address];
endmodule
module regpile(
	input [7:0]address,
	output [7:0]dout
	);
	reg [7:0] regs[255:0];//256个八位寄存器	
	initial begin
		$readmemh("scancode.txt", regs, 0, 255);
	end
	assign dout=regs[address];
endmodule

//standard ps2 interface, you can keep this
module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,ready,nextdata_n,overflow);
    input clk,clrn,ps2_clk,ps2_data;
    input nextdata_n;
    output [7:0] data;
    output reg ready;
    output reg overflow; // fifo overflow
    // internal signal, for test
    reg [9:0] buffer; // ps2_data bits
    reg [7:0] fifo[7:0]; // data fifo
    reg [2:0] w_ptr,r_ptr; // fifo write and read pointers
    reg [3:0] count; // count ps2_data bits
    // detect falling edge of ps2_clk
    reg [2:0] ps2_clk_sync; 
    always @(posedge clk) begin
        ps2_clk_sync <= {ps2_clk_sync[1:0],ps2_clk};
    end 
    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1]; 
    always @(posedge clk) begin
        if (clrn == 0) begin // reset
            count <= 0; w_ptr <= 0; r_ptr <= 0; overflow <= 0; ready<= 0;
        end
        else begin
            if ( ready ) begin // read to output next data
                if(nextdata_n == 1'b0) //read next data
                begin
                    r_ptr <= r_ptr + 3'b1;
                    if(w_ptr==(r_ptr+1'b1)) //empty
                    ready <= 1'b0;
                end
            end
            if (sampling) begin
                if (count == 4'd10) begin//如果攒够了11个
                    if ((buffer[0] == 0) && // start bit
                    (ps2_data) && // stop bit
                    (^buffer[9:1])) begin // odd parity
                        fifo[w_ptr] <= buffer[8:1]; // kbd scan code
                        w_ptr <= w_ptr+3'b1;
                        ready <= 1'b1;
                        overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
                    end
                count <= 0; // for next
                end 
                else begin//如果buffer没有攒够10个，继续攒
                    buffer[count] <= ps2_data; // store ps2_data
                    count <= count + 3'b1;
                end
            end
        end
    end
    assign data = fifo[r_ptr]; //always set output data 
endmodule