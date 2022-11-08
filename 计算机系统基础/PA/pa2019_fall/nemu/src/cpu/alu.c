#include "cpu/cpu.h"

void set_CF_add(uint32_t result,uint32_t src,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.CF=result<src;

}

void set_PF(uint32_t result)
{
	uint32_t x=0;
	for(int i=0;i<8;i++)
	{
		uint32_t t=1<<i;
		if((result&t)!=0)
			x++;
	}
	if(x%2==0)
	{
		cpu.eflags.PF=1;
	}
	else
	{
		cpu.eflags.PF=0;
	}
}

void set_ZF(uint32_t result,size_t data_size)
{
	result=result&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);
}

void set_SF(uint32_t result,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);
}

void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(src)==sign(dest))
	{
		if(sign(src)!=sign(result))
		{
			cpu.eflags.OF=1;
		}
		else
		{
			cpu.eflags.OF=0;
		}
	}
	else
	{
		cpu.eflags.OF=0;
	}
}




uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
        uint32_t res=0;
	res=dest+src;
	set_CF_add(res,src,data_size);
	set_PF(res);
	//set_AF();
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_add(res,src,dest,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
#endif
}
void set_CF_adc(uint32_t result,uint32_t src,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	uint32_t re=src+cpu.eflags.CF;
	if(re<src)
		cpu.eflags.CF=1;
	else
	{
		if(result<re)
			cpu.eflags.CF=1;
		else
		{
			cpu.eflags.CF=0;
		}
	}

}
uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t res=0;
	res=dest+src+cpu.eflags.CF;
	set_CF_adc(res,src,data_size);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_add(res,src,dest,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));

#endif
}
void set_CF_sub(uint32_t result,uint32_t dest,size_t data_size)
{

	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(result>dest)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;
}
void set_OF_sub(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{

	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result = sign_ext(result & 0xFFFF, 16); 
			src = sign_ext(src & 0xFFFF, 16); 
			dest = sign_ext(dest & 0xFFFF, 16); 
			break;
		default: break;
	}
	if(src!=0x80000000)
	{
		src=(~src)+1;
		if(sign(src)==sign(dest))
		{
			if(sign(src)!=sign(result))
				cpu.eflags.OF=1;
			else
				cpu.eflags.OF=0;
		}
		else
		{
			cpu.eflags.OF=0;
		}
	}
	else
	{
		if(dest>>31==1)
			cpu.eflags.OF=0;
		else
			cpu.eflags.OF=1;

	}
}
uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else

//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t srcb=(~src)+1;
	uint32_t res=0;
	res=dest+srcb;
	set_CF_sub(res,dest,data_size);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_sub(res,src,dest,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
	#endif
}
void set_CF_sbb(uint32_t result,uint32_t dest,size_t data_size)
{
	result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size); 
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
	uint32_t des=dest;
	dest=dest-cpu.eflags.CF;
	if(dest>des)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=result>dest;
}
void set_OF_sbb(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	switch(data_size)
	{
		case 8:
			result = sign_ext(result & 0xFF, 8); 
			src = sign_ext(src & 0xFF, 8); 
			dest = sign_ext(dest & 0xFF, 8); 
			break;
		case 16:
			result = sign_ext(result & 0xFFFF, 16); 
			src = sign_ext(src & 0xFFFF, 16); 
			dest = sign_ext(dest & 0xFFFF, 16); 
			break; 
		default: break;// do nothingi
	}
	src=(~src)+1;
	dest=dest+((~cpu.eflags.CF)+1);
	if(sign(src)==sign(dest))
	{
		if(sign(src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;

	}
	else
		cpu.eflags.OF=0;
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t result_t=alu_add(src,cpu.eflags.CF,data_size);
	uint32_t temp_CF=cpu.eflags.CF;
	uint32_t temp_OF=cpu.eflags.OF;
	uint32_t result=alu_sub(result_t,dest,data_size);
	cpu.eflags.CF=(temp_CF||cpu.eflags.CF);
	cpu.eflags.OF=(temp_OF!=cpu.eflags.OF);
	return result&(0xFFFFFFFF>>(32-data_size));
#endif
}


void set_CF_mul(uint32_t src,uint32_t dest,size_t data_size,uint64_t result)
{
	uint64_t flag=0;
	uint32_t i=0;
	while(i<data_size)
	{
		flag=(flag<<1)+1;
		i++;
	}
	if(flag<result)
	{
			cpu.eflags.CF=1;
	}
	else
		cpu.eflags.CF=0;
}

void set_OF_mul(uint32_t src,uint32_t dest,size_t data_size,uint64_t result)
{
		uint64_t flag=0;
		uint32_t i=0;
		while(i<data_size)
		{
	        flag=(flag<<1)+1;
			i++;
		}
		if(result>flag)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint64_t res;
	uint64_t src1=src;
	uint64_t dest1=dest;
	res=src1*dest1;
	set_CF_mul(src,dest,data_size,res);
	set_OF_mul(src,dest,data_size,res);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
return alu_mul(src,dest,data_size);
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	if(src==0)
	{
//		printf("Floating Point Exception");
		return 0;
	}
	else
		return dest/src;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	if(src==0)
	{
		return 0;
	}
	else
	{
		uint32_t res=dest/src;
		return res;
	}
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t res=0;
	res=(uint32_t)(dest-(dest/src)*src);
	return res;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	int32_t res=0;
	res=(int32_t)(dest-(dest/src)*src);
	return res;

#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t res=0;
	res=src&dest;
	uint32_t flag=0;
	cpu.eflags.CF=flag;

	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	cpu.eflags.OF=flag;
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t res=src^dest;
	
	cpu.eflags.CF=0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	cpu.eflags.OF=0;
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t res=src|dest;
	cpu.eflags.CF=0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	cpu.eflags.OF=0;
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}


void set_CF_shl(uint32_t src,uint32_t dest,size_t data_size)
{
	dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);

	if(src>data_size)
		cpu.eflags.CF=0;
	else
	{
		cpu.eflags.CF=dest>>(data_size-src)&0x1;
	}
}
uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t res=0;
	switch(data_size)
	{
		case 8:
			res=(dest<<src)&0xff;
			res=res|(dest&0xffffff00);
		case 16:
			res=(dest<<src)&0xffff;
			res=res|(dest&0xffff0000);
		default:
			res=dest<<src;
	}
	set_CF_shl(src,dest,data_size);
	set_SF(res,data_size);
	set_ZF(res,data_size);
	set_PF(res);
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}
void set_CF_shr(uint32_t src,uint32_t dest,size_t data_size)
{
	src=sign_ext(src&(0xffffffff>>(32-data_size)),data_size);
	dest=sign_ext(dest&(0xffffffff>>(32-data_size)),data_size);
	if(src>data_size)
		cpu.eflags.CF=0;
	else
	{
		cpu.eflags.CF=(dest>>(src-1))&0x1;
	}

}
uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	uint32_t res=0;
	uint32_t temp=0;
	for(uint32_t i=0;i<data_size;++i)
	temp=(temp<<1)+1;
	res=(dest&temp)>>src;
	res=(res&temp)|(~temp&dest);
	set_CF_shr(src,dest,data_size);
	set_PF(res&temp);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
uint32_t res=0;
	uint32_t res1=(dest>>(data_size-1))&0x1;
	if(data_size==8)
	{
		if(res1==0)
		{
			res=alu_shr(src,dest,data_size);
		}
		else
			res=alu_shr(src,dest,data_size)|((0xff<<(8-src))&0xff);
	}
	else if(data_size==16)
	{
		if(res1==0)
		{
			res=alu_shr(src,dest,data_size);
		}
		else
		{
			res=alu_shr(src,dest,data_size)|((0xffff<<(16-src))&0xffff);
		}
	}
	else
	{
		if(res1==0)
		{
			res=alu_shr(src,dest,data_size);
		}
		else
		{
			res=alu_shr(src,dest,data_size)|(0xffffffff<<(32-src));
		}
	}
	set_PF(res);
	set_SF(res,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
//	return 0;
	return alu_shl(src,dest,data_size);
#endif
}
