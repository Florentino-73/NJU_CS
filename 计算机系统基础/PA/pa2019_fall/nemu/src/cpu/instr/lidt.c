#include "cpu/instr.h"
make_instr_func(lidt)
{
	OPERAND t;
	t.data_size=data_size;
	int len=1;
	len=len+modrm_rm(eip+1,&t);
	cpu.idtr.limit=laddr_read(t.addr,2);
	if(data_size==32){
		cpu.idtr.base=laddr_read(t.addr+2,4);
	}
	else{
		cpu.idtr.base=laddr_read(t.addr+2,3);
	}
	return len;
}
