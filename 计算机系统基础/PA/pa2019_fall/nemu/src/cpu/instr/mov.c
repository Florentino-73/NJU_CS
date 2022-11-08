#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_2op(mov, r, rm, b)
make_instr_impl_2op(mov, r, rm, v)
make_instr_impl_2op(mov, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)

make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
        operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
        return len;
}
make_instr_func(mov_rm2s_w)
{
	OPERAND rm;
	int len=0;
	rm.data_size=data_size;
	rm.type=OPR_MEM;
	MODRM mm;
	mm.val=instr_fetch(eip+1,1);
	uint8_t code=mm.reg_opcode;
	len+=modrm_rm(eip+1,&rm);
	operand_read(&rm);
	cpu.segReg[code].val=rm.val;
	load_sreg(code);
	return len+1;
}
make_instr_func(mov_c2r_l)
{
	OPERAND cr,r;
	int len=1;
	cr.data_size=data_size;
	r.data_size=data_size;

	cr.type=OPR_CREG;
	
	len+=modrm_r_rm(eip+1,&r,&cr);

	operand_read(&cr);
	r.val=cr.val;
	operand_write(&r);

	return len;
}
make_instr_func(mov_r2c_l)
{
	OPERAND cr,r;
	int len=1;
	cr.data_size=data_size;
	r.data_size=data_size;
	cr.type=OPR_CREG;
	len+=modrm_r_rm(eip+1,&cr,&r);
	operand_read(&r);
	cr.val=r.val;
	cr.type=OPR_CREG;
	operand_write(&cr);
	return len;
}
