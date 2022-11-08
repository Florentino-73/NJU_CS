//4位带符号补码ALU
module exp_3( 
	input [3:0] A, 
	input [3:0] B,
	input [2:0] ALUstr,
	output [3:0] F,
	output [6:0] LED,
	output CF,
	output ZERO,
	output OF
);

	reg cf;
	reg of;
	reg zero;
	reg [3:0] f;
	reg [6:0] led;
	
	always @(*) begin
		case(ALUstr)
			0: // 加法
			begin
				{cf,f}=A+B;
				zero=(f==0)?1:0;
				of=(A[3]==B[3]) && (F[3]!=A[3]);
			end
			1: //减法
			begin
				{cf,f}=A-B;
				zero=(f==0)?1:0;
				of=(A[3]!=B[3]) && (F[3]!=A[3]);
			end
			2: //取反
			begin
				f=~A;
				zero=(f==0)?1:0;of=0;cf=0;
			end
			3: //与
			begin
				f=A&B;
				zero=(f==0)?1:0;of=0;cf=0;
			end
			4: //或
			begin
				f=A|B;
				zero=(f==0)?1:0;of=0;cf=0;
			end
			5: //异或
			begin
				f=A^B;
				zero=(f==0)?1:0;of=0;cf=0;
			end
			6: //比较大小
			begin
				if(A[3]==B[3]) 
					f=(A>B)?1:0;
				else if(A[3]==1) f=0;
				else f=1;
				zero=(f==0)?1:0;of=0;cf=0;
			end
			7: //判断相等
			begin
				f=((A-B)==0)?1:0;
				zero=(f==0)?1:0;of=0;cf=0;
			end
			default: begin
				f=0;zero=0;of=0;cf=0;
			end
		endcase
		case(f)
			0: led=7'b1000000;
			1: led=7'b1111001;
			2: led=7'b0100100;
			3: led=7'b0110000;
			4: led=7'b0011001;
			5: led=7'b0010010;
			6: led=7'b0000010;
			7: led=7'b1111000;
			8: led=7'b0000000;
			9: led=7'b0010000;
			10: led=7'b0001000;
			11: led=7'b0000011;
			12: led=7'b1000110;
			13: led=7'b0100001;
			14: led=7'b0000110;
			15: led=7'b0001110;
		endcase
	end
	
	assign ZERO=zero;
	assign CF=cf;
	assign OF=of;
	assign F=f;
	assign LED=led;
	
endmodule