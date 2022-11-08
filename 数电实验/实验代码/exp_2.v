module exp_2(
	input  [7:0] X,
	input  en,
	output reg valid,
	output [2:0] Y,
	output [6:0] F
	);

   integer i;
	reg [2:0] y;
	reg [6:0] f;
	always @(*) begin
		y=0;valid=0;
		if(en==0) begin
			f=7'b1111111;
			valid=0;
		end

		else begin
			for(i=0;i<=7;i=i+1)
			if(X[i]==1) begin
				y=i;
				valid=1;
			end
			case(y)
			3'b000: begin
				if(valid==0)
					f=7'b1111111;
				else
					f=7'b1000000;
			end
			3'b001: f=7'b1111001;
			3'b010: f=7'b0100100;
			3'b011: f=7'b0110000;
			3'b100: f=7'b0011001;
			3'b101: f=7'b0010010;
			3'b110: f=7'b0000010;
			3'b111: f=7'b1111000;
		endcase
		end
	end
	assign Y=y;
	assign F=f;
endmodule
