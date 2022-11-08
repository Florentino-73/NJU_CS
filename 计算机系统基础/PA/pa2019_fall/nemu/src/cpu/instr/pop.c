#include "cpu/instr.h"


static void instr_execute_1op()
{
	operand_read(&opr_src);
	opr_src.val=laddr_read(cpu.esp,4);
	cpu.esp=cpu.esp+4;
	operand_write(&opr_src);
}

make_instr_impl_1op(pop,r,v)
/*
static uint32_t pop(){
	OPERAND t;
	t.addr=cpu.esp;
	cpu.esp=cpu.esp+4;
	t.type=OPR_MEM;
	t.data_size=32;
	t.sreg=SREG_SS;
	operand_read(&t);
	return t.val;
}
*/
make_instr_func(popa)
{
	/*int len=1;
	cpu.edi=pop();
	cpu.esi=pop();
	pop();
	cpu.ebp=pop();
	cpu.ebx=pop();
	cpu.edx=pop();
	cpu.ecx=pop();
	cpu.eax=pop();
	return len;
	*/
	OPERAND reg[8];
	int len = 1;

	for(int i=0;i<8;i++){
		reg[i].data_size = data_size;
		reg[i].type = OPR_MEM;
		reg[i].sreg = SREG_SS;
	}
	for(int i=7;i>=0;i--){
		reg[i].addr = cpu.esp;
		cpu.esp += data_size/8;
		operand_read(&reg[i]);
	}
	for(int i=0;i<8;i++){
		reg[i].type = OPR_REG;
		reg[i].addr = i;
		if(i!=REG_ESP)
			operand_write(&reg[i]);
	}
	return len;
}
