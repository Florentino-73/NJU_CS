#include "cpu/instr.h"

make_instr_func(ret_near)
{
	OPERAND mem;
	mem.data_size=data_size;
	mem.type=OPR_MEM;
	mem.addr=cpu.esp;

	operand_read(&mem);
	cpu.eip=mem.val;
	cpu.esp+=4;
	return 0;
}
make_instr_func(ret_near_imm16)
{
	OPERAND imm,r;
	int len=1;
	imm.data_size=16;
	imm.type=OPR_IMM;

	r.data_size=32;
	r.type=OPR_IMM;
	r.addr=cpu.esp;
	operand_read(&r);

	cpu.esp+=4;
	imm.addr=eip+len;
	len=len+1;
	operand_read(&imm);

	cpu.esp+=sign_ext(imm.val,32);
	len=r.val-eip;
	return len;

}

make_instr_func(iret)
{
	cpu.eip=vaddr_read(cpu.esp,2,4);
	cpu.esp=cpu.esp+4;
	cpu.cs.val=(uint16_t)vaddr_read(cpu.esp,2,4);
	cpu.esp+=4;
	cpu.eflags.val=vaddr_read(cpu.esp,2,4);
	cpu.esp+=4;
	return 0;
}
