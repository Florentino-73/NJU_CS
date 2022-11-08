#include "cpu/instr.h"

make_instr_func(leave)
{

	int len=0;
	cpu.esp=cpu.ebp;
	cpu.ebp=laddr_read(cpu.esp,4);
	len++;
	cpu.esp=cpu.esp+4;
	return len;

	
}
