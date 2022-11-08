#include"memory.h"
#include"cpu/cpu.h"
#include<stdio.h>

typedef struct
{
	bool  validbit;
	uint32_t tag;
	uint8_t data[64];
}CacheLine;

//#ifndef __CACHE_H__
//#define __CACHE_H__

CacheLine cache[1024];
void init_cache();
uint32_t cache_read(paddr_t paddr,size_t len,CacheLine *cache);
void cache_write(paddr_t paddr, size_t len,uint32_t data, CacheLine *cache);


#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"

#ifdef CACHE_ENABLED

// cache struct
typedef struct
{
	bool  validbit; // 标志位
	uint32_t tag; // 标记部分
	uint8_t data[64]; // 数据区域
}CacheLine;

// init the cache
void init_cache();

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data, uint8_t* hw_mem);

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len, uint8_t* hw_mem);

#endif

#endif