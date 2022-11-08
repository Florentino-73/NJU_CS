#include "cpu/instr.h"
static void instr_execute_2op()
{

	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val=alu_adc(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);



}
make_instr_impl_2op(adc,r,rm,b);
make_instr_impl_2op(adc,r,rm,v);
