#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void push_eflags(){
	cpu.esp-=4;
	//uint32_t t=cpu.eflags.val;
	vaddr_write(cpu.esp,2,4,cpu.eflags.val);
}
void push_cs(){
	cpu.esp-=4;
	vaddr_write(cpu.esp,2,4,(cpu.cs.val&0x0000ffff));
}
void push_eip(){
	cpu.esp-=4;
	vaddr_write(cpu.esp,2,4,cpu.eip);
}
void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
//	printf("Please implement raise_intr()");
//	assert(0);

	push_eflags();
	push_cs();
	push_eip();
	GateDesc gate;
	gate.val[0]=laddr_read((cpu.idtr.base+intr_no*8),4);
	gate.val[1]=laddr_read(((cpu.idtr.base+intr_no*8)+4),4);
	cpu.eip=gate.offset_15_0|(gate.offset_31_16<<16);
	cpu.cs.val=gate.selector;
	if(gate.type==6){
		cpu.eflags.IF=0;
	}
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
