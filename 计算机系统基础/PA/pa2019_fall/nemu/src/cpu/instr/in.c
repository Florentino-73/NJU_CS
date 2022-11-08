#include "cpu/instr.h"
#include "device/port_io.h"
make_instr_func(in_b)
{
cpu.gpr[0]._8[0]=(uint8_t)pio_read(cpu.gpr[2]._16,1);
return 1;
}
make_instr_func(in_v){
	cpu.gpr[0].val=pio_read(cpu.gpr[2]._16,4);
	return 1;
}
