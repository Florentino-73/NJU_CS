#ifndef __X86_H__
#define __X86_H__

#include "x86/cpu.h"
#include "x86/memory.h"
#include "x86/io.h"
#include "x86/irq.h"


#define MAXSYSCALL 4

#define SYS_WRITE 0
#define SYS_FORK 1
#define SYS_EXEC 2
#define SYS_SLEEP 3
#define SYS_EXIT 4
// #define SYS_
// #define SYS_
// #define SYS_
// #define SYS_
// #define SYS_





void initSeg(void);
void initProc(void);

#endif
