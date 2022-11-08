module generate_contrl_signal(
input [6:0]op,input [2:0]func3,input [6:0]func7,
output reg [2:0]ExtOP,output reg RegWr,output reg [2:0]Branch,
output reg MemtoReg,output reg MemWr,output reg [2:0]MemOP,
output reg ALUAsrc,output reg [1:0]ALUBsrc,output reg [3:0]ALUctr);
always @ (*) begin
	if(op[6:2]==5'b01101) begin//lui
		ExtOP=3'b001;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
		ALUBsrc=2'b01;
		ALUctr=4'b0011;
	end
	if(op[6:2]==5'b00101) begin//auipc
		ExtOP=3'b001;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=1;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b00100&&func3==3'b000) begin//addi
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b00100&&func3==3'b010) begin//slti
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0010;
	end
    if(op[6:2]==5'b00100&&func3==3'b011) begin//sltiu
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b1010;
	end
    if(op[6:2]==5'b00100&&func3==3'b100) begin//xori
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0100;
	end
    if(op[6:2]==5'b00100&&func3==3'b110) begin//ori
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0110;
	end
    if(op[6:2]==5'b00100&&func3==3'b111) begin//andi
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0111;
	end
    if(op[6:2]==5'b00100&&func3==3'b001&&func7[5]==0) begin//slli
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0001;
	end
    if(op[6:2]==5'b00100&&func3==3'b101&&func7[5]==0) begin//srli
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0101;
	end
    if(op[6:2]==5'b00100&&func3==3'b101&&func7[5]==1) begin//srai
		ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b1101;
	end
    if(op[6:2]==5'b01100&&func3==3'b000&&func7[5]==0) begin//add
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b01100&&func3==3'b000&&func7[5]==1) begin//sub
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b1000;
	end
    if(op[6:2]==5'b01100&&func3==3'b001&&func7[5]==0) begin//sll
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0001;
	end
    if(op[6:2]==5'b01100&&func3==3'b010&&func7[5]==0) begin//slt
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0010;
	end
    if(op[6:2]==5'b01100&&func3==3'b011&&func7[5]==0) begin//sltu
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b1010;
	end
    if(op[6:2]==5'b01100&&func3==3'b100&&func7[5]==0) begin//xor
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0100;
	end
    if(op[6:2]==5'b01100&&func3==3'b101&&func7[5]==0) begin//srl
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0101;
	end
    if(op[6:2]==5'b01100&&func3==3'b101&&func7[5]==1) begin//sra
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b1101;
	end
    if(op[6:2]==5'b01100&&func3==3'b110&&func7[5]==0) begin//or
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0110;
	end
    if(op[6:2]==5'b01100&&func3==3'b111&&func7[5]==0) begin//and
		RegWr=1;
		Branch=3'b000;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0111;
	end
    if(op[6:2]==5'b11011) begin//jal
        ExtOP=3'b100;
		RegWr=1;
		Branch=3'b001;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=1;
        ALUBsrc=2'b10;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b11001&&func3==3'b000) begin//jalr
        ExtOP=3'b000;
		RegWr=1;
		Branch=3'b010;
		MemtoReg=0;
		MemWr=0;
        ALUAsrc=1;
        ALUBsrc=2'b10;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b11000&&func3==3'b000) begin//beq
        ExtOP=3'b011;
		RegWr=0;
		Branch=3'b100;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0010;
	end
    if(op[6:2]==5'b11000&&func3==3'b001) begin//bne
        ExtOP=3'b011;
		RegWr=0;
		Branch=3'b101;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0010;
	end
    if(op[6:2]==5'b11000&&func3==3'b100) begin//blt
        ExtOP=3'b011;
		RegWr=0;
		Branch=3'b110;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0010;
	end
    if(op[6:2]==5'b11000&&func3==3'b101) begin//bge
        ExtOP=3'b011;
		RegWr=0;
		Branch=3'b111;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b0010;
	end
    if(op[6:2]==5'b11000&&func3==3'b110) begin//bltu
        ExtOP=3'b011;
		RegWr=0;
		Branch=3'b110;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b1010;
	end
    if(op[6:2]==5'b11000&&func3==3'b111) begin//bgeu
        ExtOP=3'b011;
		RegWr=0;
		Branch=3'b111;
		MemWr=0;
        ALUAsrc=0;
        ALUBsrc=2'b00;
        ALUctr=4'b1010;
	end
    if(op[6:2]==5'b00000&&func3==3'b000) begin//lb
        ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
        MemtoReg=1;
		MemWr=0;
        MemOP=3'b000;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b00000&&func3==3'b001) begin//lh
        ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
        MemtoReg=1;
		MemWr=0;
        MemOP=3'b001;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b00000&&func3==3'b010) begin//lw
        ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
        MemtoReg=1;
		MemWr=0;
        MemOP=3'b010;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b00000&&func3==3'b100) begin//lbu
        ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
        MemtoReg=1;
		MemWr=0;
        MemOP=3'b100;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b00000&&func3==3'b101) begin//lhu
        ExtOP=3'b000;
		RegWr=1;
		Branch=3'b000;
        MemtoReg=1;
		MemWr=0;
        MemOP=3'b101;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b01000&&func3==3'b000) begin//sb
        ExtOP=3'b010;
		RegWr=0;
		Branch=3'b000;
		MemWr=1;
        MemOP=3'b000;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b01000&&func3==3'b001) begin//sh
        ExtOP=3'b010;
		RegWr=0;
		Branch=3'b000;
		MemWr=1;
        MemOP=3'b001;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
    if(op[6:2]==5'b01000&&func3==3'b010) begin//sw
        ExtOP=3'b010;
		RegWr=0;
		Branch=3'b000;
		MemWr=1;
        MemOP=3'b010;
        ALUAsrc=0;
        ALUBsrc=2'b01;
        ALUctr=4'b0000;
	end
end
endmodule