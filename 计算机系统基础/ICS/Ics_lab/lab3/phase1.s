
phase1.o:     file format elf32-i386


Disassembly of section .text:

00000000 <do_phase>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 08             	sub    $0x8,%esp
   6:	b8 24 01 00 00       	mov    $0x124,%eax
   b:	83 ec 0c             	sub    $0xc,%esp
   e:	50                   	push   %eax
   f:	e8 fc ff ff ff       	call   10 <do_phase+0x10>
  14:	83 c4 10             	add    $0x10,%esp
  17:	90                   	nop
  18:	c9                   	leave  
  19:	c3                   	ret    
