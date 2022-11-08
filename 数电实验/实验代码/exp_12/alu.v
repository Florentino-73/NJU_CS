module alu(
	input [31:0] dataa,
	input [31:0] datab,
	input [3:0]  ALUctr,
	output reg less,
	output reg zero,
	output reg [31:0] aluresult);
always @ (*) begin
	if(ALUctr==4'b0) 
		aluresult=dataa+datab;
	if(ALUctr==4'b1000)
		aluresult=dataa-datab;
	if(ALUctr[2:0]==3'b001)
		aluresult=dataa<<datab[4:0];
	if(ALUctr==4'b0010)begin//带符号
		less=(( $signed(dataa) )<( $signed(datab) ));
		aluresult={{31'b0},less};
	end
	if(ALUctr==4'b1010)begin//不带符号
		less=(dataa<datab);
		aluresult={{31'b0},less};
	end
	if(ALUctr[2:0]==3'b011)
		aluresult=datab;
	if(ALUctr[2:0]==3'b100)
		aluresult=datab^dataa;
	if(ALUctr==4'b0101)
		aluresult=dataa>>datab[4:0];
	if(ALUctr==4'b1101)
		aluresult=( $signed(dataa) )>>>datab[4:0];
	if(ALUctr[2:0]==3'b110)
		aluresult=dataa|datab;
	if(ALUctr[2:0]==3'b111)
		aluresult=dataa&datab;
	if(ALUctr==4'b1010||ALUctr==4'b0010)
		zero=(dataa==datab);
	else
		zero=(aluresult==0)?1:0;
end
endmodule