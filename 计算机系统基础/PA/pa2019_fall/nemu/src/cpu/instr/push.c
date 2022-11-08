#include"cpu/instr.h"

static void instr_execute_1op()
{
	operand_read(&opr_src);
	if(data_size==16)
		cpu.esp=cpu.esp-2;
	else
		cpu.esp=cpu.esp-4;
	OPERAND imm;
	imm.type=OPR_MEM;
	imm.sreg=SREG_SS;
	imm.addr=cpu.esp;
	imm.data_size=data_size;
	imm.val=sign_ext(opr_src.val,opr_src.data_size);
	operand_write(&imm);
}

make_instr_impl_1op(push,rm,v);
make_instr_impl_1op(push,r,v);
//make_instr_impl_1op(push,i,b);
make_instr_impl_1op(push,i,v);


/*

make_instr_func(push_i_b){
	OPERAND imm, des;
	cpu.esp -= 4;
	imm.data_size = 8;
	imm.type = OPR_IMM;
	imm.sreg = SREG_CS;
	imm.addr = eip + 1;
	des.data_size = 32;
	des.type = OPR_MEM;
	des.sreg = SREG_CS;
	des.addr = cpu.esp;
	operand_read(&imm);
	uint32_t offset = imm.val | 0xffffff00;
	
	if((imm.val >> 7) == 1)
		des.val = offset;
	else
		des.val = imm.val;
	operand_write(&des);
	return 2;
}*/
make_instr_func(push_i_b){

	OPERAND r,imm;
	r.data_size=data_size;
	r.sreg=SREG_SS;
	r.type=OPR_MEM;
	if(r.data_size==16)cpu.esp-=2;
	else cpu.esp-=4;
	r.addr=cpu.esp;

	imm.data_size=8;
	imm.type=OPR_IMM;
	imm.addr=eip+1;
	imm.sreg=SREG_SS;

	operand_read(&imm);
	imm.val=sign_ext(imm.val,32);
	r.val=imm.val;
	//printf("push imm.val=%x imm.addr=%x\n",imm.val,imm.addr);
	operand_write(&r);
	return 2;
}

make_instr_func(pusha)
{
	uint32_t t=cpu.esp;
	for(int i=0;i<8;i++)
	{
		OPERAND rel;
		rel.data_size=data_size;
		rel.type=OPR_MEM;
		rel.sreg=SREG_SS;
		cpu.esp-=4;
		rel.addr=cpu.esp;
		if(i==4)
		{
			rel.val=t;
		}
		else
		{
			rel.val=cpu.gpr[i].val;
		}
		operand_write(&rel);
	}
	return 1;
}
