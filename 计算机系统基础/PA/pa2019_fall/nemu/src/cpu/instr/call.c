#include"cpu/instr.h"
make_instr_func(call_near)
{

	cpu.esp-=4;
	OPERAND rel,imm;

	rel.type=OPR_MEM;
	rel.addr=cpu.esp;
	rel.data_size=data_size;
	rel.sreg=SREG_SS;
	rel.val=cpu.eip+5;
	operand_write(&rel);

	imm.type=OPR_IMM;
	imm.addr=eip+1;
	imm.data_size=data_size;
	operand_read(&imm);

	int offset=sign_ext(imm.val,imm.data_size);
	cpu.eip+=offset+5;

	return 0;
}

make_instr_func(call_near_indirect)
{
	OPERAND rm,r;
	int len=1;
	r.type=OPR_MEM;
	r.data_size=data_size;

	rm.data_size=data_size;
	len=len+modrm_rm(eip+1,&rm);
	operand_read(&rm);

	r.val=eip+len;
	cpu.esp-=4;
	r.addr=cpu.esp;
	operand_write(&r);
	return  rm.val-eip;
}

