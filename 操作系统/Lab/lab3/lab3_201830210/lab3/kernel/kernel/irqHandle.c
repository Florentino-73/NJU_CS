#include "device.h"
#include "x86.h"

extern int displayRow;
extern int displayCol;
extern ProcessTable pcb[MAX_PCB_NUM];
extern int current;
extern TSS tss;
void GProtectFaultHandle(struct StackFrame *sf);

void syscallHandle(struct StackFrame *sf);
void syscallWrite(struct StackFrame *sf);
void syscallPrint(struct StackFrame *sf);
void syscallSleep(struct StackFrame *sf);
void syscallFork(struct StackFrame *sf);
void syscallExit(struct StackFrame *sf);
void timerHandle(struct StackFrame *sf);

void putCharHelper(char * str){
    // int i = 0;
    // for(;;){
    //     if(str[i] != '\0'){
    //         putChar(str[i]);
    //         i++;
    //     } else {
    //         break;
    //     }
    // }
}

void irqHandle(struct StackFrame *sf) {  // pointer sf = esp
    /* Reassign segment register */
    asm volatile("movw %%ax, %%ds" ::"a"(KSEL(SEG_KDATA)));
    /* Save esp to stackTop */
    // putCharHelper("Start irq!\n");
    uint32_t tmpStackTop = pcb[current].stackTop;
    pcb[current].prevStackTop = pcb[current].stackTop;
    pcb[current].stackTop = (uint32_t)sf;

    switch (sf->irq) {
        case -1:
            // putCharHelper("Err !\n");
            break;
        case 0xd:
            // putCharHelper("Strange !\n");
            GProtectFaultHandle(sf);
            break;
        case 0x20:
            // putCharHelper("Timer !\n");
            timerHandle(sf);
            break;
        case 0x80:
            putCharHelper("Syscall !\n");
            syscallHandle(sf);
            break;
        default:
            // putCharHelper("Err !\n");
            assert(0);
    }

    /* Recover stackTop */ 
    pcb[current].stackTop = tmpStackTop; // What is this bullshit -> Kernel to User
}

void changeStack(){
    // set esp to pcb[current]'s stack:
    uint32_t tempStackTop = pcb[current].stackTop;
    pcb[current].stackTop = pcb[current].prevStackTop;
    tss.esp0 = (uint32_t)&(pcb[current].stackTop);
    asm volatile("movl %0, %%esp" : :"m"(tempStackTop));
	asm volatile("popl %gs");
	asm volatile("popl %fs");
	asm volatile("popl %es");
	asm volatile("popl %ds");
	asm volatile("popal");
	asm volatile("addl $8, %esp");
	asm volatile("iret");
}

void GProtectFaultHandle(struct StackFrame *sf) {
    assert(0);
    return;
}

#define panic(...)

void syscallHandle(struct StackFrame *sf) {
    switch (sf->eax)
    {
        case SYS_WRITE:
            /* code */
            syscallWrite(sf);
            break;
        case SYS_FORK:
            syscallFork(sf);
            break;
        case SYS_SLEEP:
            syscallSleep(sf);
            break;
        default:
            break;
    }
}

int computeMod(int i){
    return ((current + i) % MAX_PCB_NUM);
}

void schedule(){
    int found_idle = 0;

    for(int i = 1; i < MAX_PCB_NUM; ++i){
        if (computeMod(i)!=0 && pcb[computeMod(i)].state == STATE_RUNNABLE){
            current = computeMod(i); // this needs to be locked to protect from concurrency
            found_idle = 1;
            break;
        }
    }

    if (!found_idle) {
        // switch to idle
        current = 0;
    }

    if (current == 0) {
        putCharHelper("Current = 0\n");
    } else if(current == 1){
        putCharHelper("Change to user\n");
    } else {
        putCharHelper("Err");
    }

    changeStack();
}

void updateSleepTime(){
    for(int i = 1; i < MAX_PCB_NUM; ++i){
        if(pcb[i].state == STATE_BLOCKED) {
            pcb[i].sleepTime--;
            if(pcb[i].sleepTime == 0){
                pcb[i].state = STATE_RUNNABLE;
            }
        }
    }
}

void timerHandle(struct StackFrame *sf) {  
    updateSleepTime();

    pcb[current].timeCount++;

    if(pcb[current].timeCount >= MAX_TIME_COUNT){
        
        pcb[current].timeCount = 0;
        
        if (pcb[current].state == STATE_RUNNING){
            pcb[current].state = STATE_RUNNABLE;
        } 
        
        schedule();
    }

}

void syscallWrite(struct StackFrame *sf) {
    switch (sf->ecx) {  // file descriptor
        case 0:
            syscallPrint(sf);
            break;  // for STD_OUT
        default:
            break;
    }
}

// Attention:
// This is optional homework, because now our kernel can not deal with
// consistency problem in syscallPrint. If you want to handle it, complete this
// function. But if you're not interested in it, don't change anything about it
void syscallPrint(struct StackFrame *sf) {
    
    int sel = sf->ds;
    char *str = (char *)sf->edx;

    int size = sf->ebx;
    int i = 0;
    int pos = 0;
    char character = 0;
    uint16_t data = 0;
    asm volatile("movw %0, %%es" ::"m"(sel));
    for (i = 0; i < size; i++) {
        asm volatile("movb %%es:(%1), %0" : "=r"(character) : "r"(str + i));
        if (character == '\n') {
            displayRow++;
            displayCol = 0;
            if (displayRow == 25) {
                displayRow = 24;
                displayCol = 0;
                scrollScreen();
            }
        } else {
            data = character | (0x0c << 8);
            pos = (80 * displayRow + displayCol) * 2;
            asm volatile("movw %0, (%1)" ::"r"(data), "r"(pos + 0xb8000));
            displayCol++;
            if (displayCol == 80) {
                displayRow++;
                displayCol = 0;
                if (displayRow == 25) {
                    displayRow = 24;
                    displayCol = 0;
                    scrollScreen();
                }
            }
        }
        // asm volatile("int $0x20"); //XXX Testing irqTimer during syscall
        // asm volatile("int $0x20":::"memory"); //XXX Testing irqTimer during
        // syscall
    }

    updateCursor(displayRow, displayCol);
    // TODO take care of return value
    return;
}

void syscallFork(struct StackFrame *sf) {
    int availPos = -1;
    for(int i = 1; i < MAX_PCB_NUM; ++i){
        if(pcb[i].state == STATE_DEAD){
            availPos = i;
        }
    }
    if(availPos == -1) {
        // FORK FAILED
        pcb[current].regs.eax = -1;
    } else {
        // FORK SUCCESSFUL
        enableInterrupt();
		for (int j = 0; j < 0x100000; j++) {
			*(uint8_t *)(j + (availPos+1)*0x100000) = *(uint8_t *)(j + (current+1)*0x100000);
		}
		disableInterrupt();
        for (int j = 0; j < sizeof(ProcessTable); ++j)
			*((uint8_t *)(&pcb[availPos]) + j) = *((uint8_t *)(&pcb[current]) + j);
		
        pcb[availPos].stackTop = (uint32_t)&(pcb[availPos].regs);
		pcb[availPos].prevStackTop = (uint32_t)&(pcb[availPos].stackTop);
		pcb[availPos].state = STATE_RUNNABLE;
		pcb[availPos].timeCount = 0;
		pcb[availPos].sleepTime = 0;
		pcb[availPos].pid = availPos;

		pcb[availPos].regs.ss = USEL(2+2*availPos);
		pcb[availPos].regs.cs = USEL(1+2*availPos);
		pcb[availPos].regs.ds = USEL(2+2*availPos);
		pcb[availPos].regs.es = USEL(2+2*availPos);
		pcb[availPos].regs.fs = USEL(2+2*availPos);
		pcb[availPos].regs.gs = USEL(2+2*availPos);
		
        pcb[availPos].regs.eax = 0;
		pcb[current].regs.eax = availPos;

    }
}

void syscallSleep(struct StackFrame *sf) {
    pcb[current].sleepTime = sf->ecx;
    pcb[current].state = STATE_BLOCKED;
    schedule();
}

void syscallExit(struct StackFrame *sf) {
    pcb[current].state = STATE_DEAD;
    schedule();
    // panic("Should not reach here\n");
}