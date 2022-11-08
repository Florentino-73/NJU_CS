module cpu(
	input 	clock,
	input 	reset,
	output [31:0] imemaddr,
	input  [31:0] imemdataout,
	output 	imemclk,
	output [31:0] dmemaddr,
	input  [31:0] dmemdataout,
	output [31:0] dmemdatain,
	output 	dmemrdclk,
	output	dmemwrclk,
	output [2:0] dmemop,
	output	dmemwe
	);
	reg [31:0]PC=0;
	wire [31:0]NextPC;//PC是当前指令的实际地址，next_PC是PC+4,但是传给指令存储器的永远是next_PC
	assign imemclk=~clock;//取指令的时钟，在CPU时钟的下降沿（取指令时钟的上升沿），取指令，
	assign imemaddr=NextPC;
	assign dbgdata=PC;
	
	assign dmemrdclk=clock;
	assign dmemwrclk=~clock;
	wire [31:0]instr;
	wire [6:0]op;
	wire [4:0]rs1;
	wire [4:0]rs2;
	wire [4:0]rd;
	wire [2:0]func3;
	wire [6:0]func7;
	wire [31:0]imm;
	
	wire [2:0] ExtOP;
	wire RegWr;
	wire [2:0] Branch;
	wire MemtoReg;
	wire ALUAsrc;
	wire [1:0]ALUBsrc;
	wire [3:0] ALUctr;
	
 	wire [31:0] busA;
	wire [31:0] busB;
	reg [31:0] busW;

	wire [31:0] alu_dataa;
	wire [31:0] alu_datab;
	wire [31:0]aluresult;
	wire less,zero;
	assign dmemaddr=aluresult;
	assign dmemdatain=busB;
	
	
	
	//跳转控制&PC生成
	always @ (negedge clock) begin
		if(reset) //reset可能有问题
			PC<=0;
		else 
			PC<=NextPC;
	end
	
	PC_gen me_PC(.reset(reset),.Branch(Branch),.zero(zero),.less(less),.NextPC(NextPC),
	.imm(imm),.PC(PC),.busA(busA));
	
	//ALU
	alu_input my_aluinput(.alu_dataa(alu_dataa),.alu_datab(alu_datab),.PC(PC),.busA(busA),.busB(busB),.imm(imm),
	.ALUAsrc(ALUAsrc),.ALUBsrc(ALUBsrc));
	alu my_alu(.dataa(alu_dataa),.datab(alu_datab),.ALUctr(ALUctr),
	.less(less),.zero(zero),.aluresult(aluresult));
	
	//指令译码及立即数生成
	assign instr=imemdataout;
	assign op=instr[6:0];
	assign rs1=instr[19:15];
	assign rs2=instr[24:20];
	assign rd=instr[11:7];
	assign func3=instr[14:12];
	assign func7=instr[31:25];
	imm_gen my_imm(.instr(instr),.ExtOp(ExtOP),.imm(imm));
	
	//控制信号生成
	generate_contrl_signal my_signal (.op(op),.func3(func3),.func7(func7),
	.ExtOP(ExtOP),.RegWr(RegWr),.Branch(Branch),
	.MemtoReg(MemtoReg),.MemWr(dmemwe),.MemOP(dmemop),
	.ALUAsrc(ALUAsrc),.ALUBsrc(ALUBsrc),.ALUctr(ALUctr));
	
	always @ (*) begin
		if(MemtoReg==0)
			busW=aluresult;
		else
			busW=dmemdataout;
	end
	regfile myregfile(.wrclk(~clock),.regwr(RegWr),
	.ra(rs1),.rb(rs2),.outa(busA),.outb(busB),
	.rw(rd),.wrdata(busW)
	//,.HEX4(HEX4)
	//,.HEX5(HEX5)
	);
endmodule

module alu_input(output reg [31:0] alu_dataa,output reg [31:0] alu_datab,input [31:0] PC,
input [31:0] imm,input [31:0] busA,input [31:0] busB,input ALUAsrc,input [1:0]ALUBsrc);
	always @ (*) begin
		case (ALUAsrc)
			1'b0:alu_dataa=busA;
			1'b1:alu_dataa=PC;
		endcase
		case (ALUBsrc)
			2'b00:alu_datab=busB;
			2'b01:alu_datab=imm;
			2'b10:alu_datab=4;
			default:alu_datab=0;
		endcase
	end
endmodule

module PC_gen (input reset,input [2:0] Branch,input zero,input less,
input [31:0] imm,input [31:0] PC,input [31:0] busA, output reg [31:0] NextPC);
	always @ (*) begin
		if(reset)
			NextPC= 0;
		else begin
		if(Branch==3'b000) 
			NextPC=PC+4;
		if(Branch==3'b001)
			NextPC=PC+imm;
		if(Branch==3'b010) 
			NextPC=busA+imm;
		if(Branch==3'b100&&zero==0) 
			NextPC=PC+4;
		if(Branch==3'b100&&zero==1) 
			NextPC=PC+imm;
		if(Branch==3'b101&&zero==0) 
			NextPC=PC+imm;
		if(Branch==3'b101&&zero==1) 
			NextPC=PC+4;
		if(Branch==3'b110&&less==0) 
			NextPC=PC+4;
		if(Branch==3'b110&&less==1) 
			NextPC=PC+imm;
		if(Branch==3'b111&&less==0)
			NextPC=PC+imm;
		if(Branch==3'b111&&less==1)
			NextPC=PC+4;
		end
	end
endmodule 

module imm_gen (input [31:0] instr,input [2:0] ExtOp, output reg [31:0] imm);
	wire [31:0]immI;
	wire [31:0]immU;
	wire [31:0]immS;
	wire [31:0]immB;
	wire [31:0]immJ;
	assign immI = {{20{instr[31]}}, instr[31:20]};
	assign immU = {instr[31:12], 12'b0};
	assign immS = {{20{instr[31]}}, instr[31:25], instr[11:7]};
	assign immB = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};
	assign immJ = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
	always @ (*) begin
		case(ExtOp)
			3'b000:imm=immI;
			3'b001:imm=immU;
			3'b010:imm=immS;
			3'b011:imm=immB;
			3'b100:imm=immJ;
		endcase
	end
endmodule

 module regfile(
//output		     [6:0]		HEX4,
//output		     [6:0]		HEX5,
 input  [4:0]  ra,
	input  [4:0]  rb,
	input  [4:0]  rw,
	input  [31:0] wrdata,
	input  regwr,
	input  wrclk,
	output [31:0] outa,
	output [31:0] outb
	);
	
	
	reg [31:0] regs [31:0];	
	///bcd7seg bcd4(regs[14][3:0],HEX4);
///bcd7seg bcd5(regs[15][3:0],HEX5);
	integer i;
	initial begin
		for(i=0;i<=31;i=i+1)
			regs[i]=32'b0;
	end
	always @ (posedge wrclk) begin
		if(regwr==1&&rw!=0) begin
			regs[rw]=wrdata;
		end
	end
	assign outa=regs[ra];
	assign outb=regs[rb];
endmodule