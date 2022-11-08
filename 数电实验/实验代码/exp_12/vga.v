module vga(
	input VGA_CLK,
	input CLOCK_50,
   input we,
	input [3:0] color,
   input vga_mem_clk,
	input [7:0] writedata,
	input [11:0] writeaddress,
   output		          		VGA_BLANK_N,
	output		          		VGA_VS,
	output		          		VGA_HS,
	output		     [7:0]		VGA_B,
	output		     [7:0]		VGA_G,
   output		     [7:0]		VGA_R,
	input [31:0] vga_offset
);
wire [7:0]asc2;
wire [11:0]font;
wire [9:0]haddr;
wire [9:0]vaddr;
reg [11:0]vgadata;
reg [11:0]asc2_address;
reg [11:0]block_addr;

vga_ctrl my_vga(
.pclk(VGA_CLK),//25MHz时钟
.reset(1'b0),//reset
.vga_data(vgadata),//vgadata[11:0]
.h_addr(haddr),
.v_addr(vaddr),
.hsync(VGA_HS),//列同步信号
.vsync(VGA_VS),//行同步信号
.valid(VGA_BLANK_N),//消隐信号
.vga_r(VGA_R),
.vga_g(VGA_G),
.vga_b(VGA_B)
);

reg [2:0] command_prompt=0;
always @(CLOCK_50)begin
    block_addr <= (((vaddr >> 4)+vga_offset)%30) * 70 + ((haddr) / 9);
	 
//	 if(((vaddr >> 4)+vga_offset)%30)==0) begin
//			vgadata <= 12'b000000000000;
//	 end
	 
	 asc2_address <= (asc2 << 4) + (vaddr % 16);
	 if(font[haddr % 9] == 1'b1&&haddr<=629) begin
		if(color==3'b000)
			vgadata<=12'b000000000000;
		if(color==3'b001)
			vgadata<=12'b000000001111;
		if(color==3'b010)
			vgadata<=12'b111100000000;
		if(color==3'b011)
			vgadata<=12'b11110000111
		if(color==3'b100);
			vgadata<=12'b000011110000;
		if(color==3'b101)
			vgadata<=12'b000011111111;
		if(color==3'b110)
			vgadata<=12'b000011111111;
		if(color==3'b111)
			vgadata<=12'b111111111111;
	 end
	 else 
		// vgadata<=12'b111111111111;
		vgadata<=12'b000000000000;
end
wire [11:0] backgrounddata;

vga_ram ram1(
.rdaddress(block_addr),
.wraddress(writeaddress),
.rdclock(CLOCK_50),
.wrclock(vga_mem_clk),
.data(writedata),
.wren(we),
.q(asc2)
);
vga_rom rom1(
.address(asc2_address),
.clock(CLOCK_50),
.q(font)
);
/*
backgroun rom2(
.address({haddr, vaddr[8:0]}),
.clock(CLOCK_50),
.q(backgrounddata)
);*/
endmodule
