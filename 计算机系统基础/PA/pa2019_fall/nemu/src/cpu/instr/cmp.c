#include"cpu/instr.h"
static void instr_execute_2op()
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	alu_sub(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
}

make_instr_impl_2op(cmp,r,rm,v)
make_instr_impl_2op(cmp,i,rm,v)
make_instr_impl_2op(cmp,rm,r,v)
make_instr_impl_2op(cmp,i,a,b)
make_instr_impl_2op(cmp,i,rm,b)
make_instr_impl_2op(cmp,rm,r,b)
make_instr_impl_2op(cmp,i,rm,bv);
make_instr_impl_2op(cmp,i,a,v);
