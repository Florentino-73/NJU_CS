#include "memory/cache.h"
void init_cache()
{
	for(int i=0;i<1024;i++)
	{
		cache[i].validbit=false;
	}
}

uint32_t cache_read(paddr_t paddr,size_t len,CacheLine *cache)
{
	uint32_t group=((paddr>>6)&0x7f)*8;
	uint32_t tag=(paddr>>13);
	uint32_t ret=0;
	uint32_t flag=paddr&0x3f;
	for(int i=0;i<8;i++)
	{
		if(cache[group+i].tag==tag&&cache[group+i].validbit==true)
		{
		//	uint32_t flag=paddr&0x3f;
			if(flag+len>64)
			{
				memcpy(&ret,hw_mem+paddr,len);

			}
			else
			{
				memcpy(&ret,(void*)(cache[group+i].data+flag),len);
			}
			return ret;
		}
	}
	memcpy(&ret,hw_mem+paddr,len);
	for(int i=0;i<8;i++)
	{
		if(cache[group+i].validbit==false)
		{
			memcpy((void*)cache[group+i].data,(hw_mem+((paddr/64)*64)),64);
			cache[group+i].validbit=true;
			cache[group+i].tag=tag;
			return ret;
		}
	}
//	int number=rand()%8;
	memcpy(cache[group].data,hw_mem+((paddr/64)*64),64);
	cache[group].tag=tag;
	cache[group].validbit=true;
	return ret;

}

void cache_write(paddr_t paddr ,size_t len,uint32_t data,CacheLine *cache)
{
	int index=(paddr/64)%128;
	uint32_t high=paddr>>13;
	for(int i=0;i<8;i++)
	{
		if(cache[8*index+i].validbit==true&&cache[8*index+i].tag==high)
		{
			cache[8*index+i].validbit=false;
			break;
		}
	}
		memcpy(hw_mem+paddr,&data,len);
	//	printf("good");
}







// #include "memory/mmu/cache.h"
// // #include "nemu/src/memory/memory.c"

// CacheLine cache[1024]; // ȫ�ֱ���

// // init the cache
// void init_cache()
// {
// 	// implement me in PA 3-1
// 	for (int i = 0; i < 1024; i++)
// 	{
// 		cache[i].validbit = false;
// 	}
// }

// // write data to cache
// void cache_write(paddr_t paddr, size_t len, uint32_t data, uint8_t* hw_mem)
// {
// 	// implement me in PA 3-1
// 	int index = (paddr / 64) % 128;
// 	uint32_t high = paddr >> 13;
// 	for (int i = 0; i < 8; i++)
// 	{
// 		if (cache[8 * index + i].validbit == true && cache[8 * index + i].tag == high)
// 		{
// 			cache[8 * index + i].validbit = false;
// 			break;
// 		}
// 	}
// 	memcpy(hw_mem + paddr, &data, len);
// }

// // read data from cache
// uint32_t cache_read(paddr_t paddr, size_t len, uint8_t* hw_mem)
// {
// 	// implement me in PA 3-1
// 	uint32_t group = ((paddr >> 6) & 0x7f) * 8; //���
// 	uint32_t tag = (paddr >> 13); //���
// 	uint32_t ret = 0;
// 	uint32_t flag = paddr & 0x3f;

// 	for (int i = 0; i < 8; i++)
// 	{
// 		if (cache[group + i].tag == tag && cache[group + i].validbit == true)
// 		{
// 			if (flag + len > 64)
// 			{
// 				memcpy(&ret, hw_mem + paddr, len);
// 			}
// 			else
// 			{
// 				memcpy(&ret, (void*)(cache[group + i].data + flag), len);
// 			}
// 			return ret;
// 		}
// 	}

// 	memcpy(&ret, hw_mem + paddr, len);

// 	for (int i = 0; i < 8; i++)
// 	{
// 		if (cache[group + i].validbit == false)
// 		{
// 			memcpy((void*)cache[group + i].data, (hw_mem + ((paddr / 64) * 64)), 64);
// 			cache[group + i].validbit = true;
// 			cache[group + i].tag = tag;
// 			return ret;
// 		}
// 	}

// 	memcpy(cache[group].data, hw_mem + ((paddr / 64) * 64), 64);
// 	cache[group].tag = tag;
// 	cache[group].validbit = true;
// 	return ret;
// }