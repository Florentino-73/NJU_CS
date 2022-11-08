module buffer(
input [7:0] keyboarddata,
input re,
input clock,
output reg [7:0] bufferout,
input rdclk
);

reg [7:0] head=0;
reg [7:0] tail=0; 
reg we=1;
reg [7:0] wrdata;
reg [7:0] buffer [7:0];
reg [7:0] lastinput;
always @ (posedge clock) begin
	buffer[tail][7:0]<=keyboarddata[7:0];
	if(keyboarddata!=lastinput && keyboarddata != 0) begin
		if(tail==3'b111)
			tail<=0;
		else
			tail<=tail+1;
	end
	lastinput=keyboarddata; 
end
always @ (posedge rdclk) begin
if(re) begin
 	if(head==tail) 
		bufferout<=8'b0;
	else begin
		bufferout<=buffer[head];
		if(head==3'b111)
			head<=0;
		else
			head<=head+1;
	end
end
end
endmodule