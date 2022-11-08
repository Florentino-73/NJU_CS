#include "cpu/instr.h"
static void instr_execute_2op()
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val=alu_and(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);

}
//make_instr_impl_2op(and,i,rm,bv)
make_instr_impl_2op(and,rm,r,b)
make_instr_impl_2op(and,r,rm,v)
make_instr_impl_2op(and,i,rm,v)
make_instr_impl_2op(and,i,rm,b)
make_instr_impl_2op(and,i,a,v)



make_instr_func(and_i2rm_bv)
{

	OPERAND imm,rel;
	imm.type=OPR_IMM;
	imm.data_size=8;
	rel.data_size=data_size;
	int len=1;
	len=len+modrm_opcode_rm(eip+len,&opcode,&rel);
	operand_read(&rel);
	imm.addr=eip+len;
	operand_read(&imm);
	//switch(data_size)
//	{
	
//	}
	if(data_size==32)
	{
		imm.val=(int32_t)(imm.val<<24)>>24;
	}
	else
	{
		imm.val=(int16_t)(imm.val<<8)>>8;
	}

	rel.val=alu_and(imm.val,rel.val,data_size);
	operand_write(&rel);
	return len+1;

}
