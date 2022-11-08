#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	//return 0;
	//assert (sreg>=0&&sreg<6);
	return cpu.segReg[sreg].base+offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	// assert(cpu.segReg[sreg].ti==0);
	SegDesc new_seg;
	memcpy(&new_seg,hw_mem+cpu.gdtr.base+cpu.segReg[sreg].index*8,sizeof(new_seg));

	uint32_t BASE = (new_seg.base_31_24 << 24) + (new_seg.base_23_16 << 16) + new_seg.base_15_0;
	uint32_t LIMIT = (new_seg.limit_19_16 << 16) + new_seg.limit_15_0;

	assert(BASE == 0);
	assert(LIMIT == 0xffffffff);
	assert(new_seg.granularity == 1);

	cpu.segReg[sreg].base = BASE;
	cpu.segReg[sreg].limit = LIMIT;
	cpu.segReg[sreg].type = new_seg.type;
	cpu.segReg[sreg].privilege_level = new_seg.privilege_level;
	cpu.segReg[sreg].soft_use = new_seg.soft_use;
}
