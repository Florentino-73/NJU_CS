#include "cpu/instr.h"
static void instr_execute_2op()
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val=alu_or(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);

}
make_instr_impl_2op(or,r,rm,v)
make_instr_impl_2op(or,rm,r,b)
make_instr_impl_2op(or,i,rm,bv)
