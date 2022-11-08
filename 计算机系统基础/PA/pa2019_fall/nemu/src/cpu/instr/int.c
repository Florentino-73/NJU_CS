#include "cpu/instr.h"
#include "cpu/intr.h"
make_instr_func(int_){
	/*OPERAND imm;
	imm.data_size=data_size=8;
	imm.type=OPR_IMM;
	imm.addr=eip+1;
	operand_read(&imm);
	raise_sw_intr(imm.val);
	return 0;*/
    
	OPERAND imm;
	imm.data_size = 8;
	imm.addr = eip + 1;
	imm.sreg = SREG_CS;
	imm.type = OPR_IMM;
	operand_read(&imm);
	raise_sw_intr(imm.val);
	return 0;
}
