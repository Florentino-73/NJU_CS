#include "common.h"
#include "x86.h"
#include "device.h"

void kEntry(void) {

	// Interruption is disabled in bootloader
    
	// TODO: 做一系列初始化
	
	initSerial();// initialize serial port
	initIdt(); // initialize idt
	initIntr(); // iniialize 8259a
	initSeg(); // initialize gdt, tss
	initVga(); // initialize vga device
	initKeyTable();
	loadUMain(); // load user program, enter user space
	while(1);
	assert(0);
}
