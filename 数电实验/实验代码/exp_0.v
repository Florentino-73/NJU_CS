module exp_0(
	input A,
	input B,
	output F
	);
	
	assign F=~A&B|A&~B;
endmodule