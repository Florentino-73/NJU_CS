module color (
input we,
input wrclk,
input [3:0] wrdata,
output [3:0] q
);
reg [3:0] color;
always @ (posedge wrclk) begin
	if(we) 
		color<=wrdata;
end
assign q=color;
endmodule