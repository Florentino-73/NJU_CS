#include "cpu/instr.h"

/*
static void instr_execute_2op()
{


	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val=alu_xor(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);

}*/
//make_instr_impl_2op(xor,r,rm,v)


make_instr_func(xor_r2rm_v)

{


	OPERAND r,rm;
	r.data_size=data_size;
	rm.data_size=data_size;
	int len=modrm_r_rm(eip+1,&r,&rm);
	operand_read(&r);
	rm.sreg=SREG_DS;
	operand_read(&rm);
	rm.val=alu_xor(r.val,rm.val,data_size);
	operand_write(&rm);
	return  len+1;
}

