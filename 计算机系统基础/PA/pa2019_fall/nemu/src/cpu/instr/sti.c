#include "cpu/instr.h"
make_instr_func(sti){
	cpu.eflags.IF=1;
	return 1;
}
