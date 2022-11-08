module mem(
	input  [31:0] addr,
	output reg [31:0] dataout,
	input  [31:0] datain,
	input  rdclk,
	input  wrclk,
	input [2:0] memop,
	input we
);

wire [31:0] tempout;


wire[14:0]address=addr[16:2];
wire [31:0]in_data=datain<<(8*addr[1:0]);
reg[3:0]byteena_a;
wire [31:0]out_data=tempout>>(8*addr[1:0]);

dmem_ram ram_1(.byteena_a(byteena_a),.data(in_data),
.rdaddress(address),.rdclock(rdclk),
.wraddress(address),.wrclock(wrclk),
.wren(we),.q(tempout));

always@(*)begin
	case(memop[1:0])
	2'b10:begin//字节
		case(addr[1:0])
		2'b00:byteena_a=4'b1111;
		default:byteena_a=4'b0000;
		endcase
	end
	2'b01:begin//半字节
		case(addr[1:0])
		2'b00:byteena_a=4'b0011;		
		2'b10:byteena_a=4'b1100;		
		default:byteena_a=4'b0000;
		endcase
	end
	2'b00:begin//四分之一字节
		case(addr[1:0])
		2'b00:byteena_a=4'b0001;
		2'b01:byteena_a=4'b0010;
		2'b10:byteena_a=4'b0100;
		2'b11:byteena_a=4'b1000;
		default:byteena_a=4'b0000;
		endcase
	end
	default:byteena_a=4'b0000;
	endcase
end

always@(*)begin
	case(memop)
	3'b000:dataout={{24{out_data[7]}},
	out_data[7:0]};			
	3'b001:dataout={{16{out_data[15]}},
	out_data[15:0]};		
	3'b100:dataout={24'b0,
	out_data[7:0]};			
	3'b101:dataout={16'b0,
	out_data[15:0]};			
	default:dataout=out_data;	
	endcase
end

endmodule 


