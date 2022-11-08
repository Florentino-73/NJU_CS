
phase3.o:     file format elf32-i386


Disassembly of section .text:

00000000 <do_phase>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 18             	sub    $0x18,%esp
   6:	c7 45 ea 67 6c 77 69 	movl   $0x69776c67,-0x16(%ebp)
   d:	c7 45 ee 7a 71 6e 72 	movl   $0x726e717a,-0x12(%ebp)
  14:	66 c7 45 f2 76 00    	movw   $0x76,-0xe(%ebp)
  1a:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  21:	eb 28                	jmp    4b <do_phase+0x4b>
  23:	8d 55 ea             	lea    -0x16(%ebp),%edx
  26:	8b 45 f4             	mov    -0xc(%ebp),%eax
  29:	01 d0                	add    %edx,%eax
  2b:	0f b6 00             	movzbl (%eax),%eax
  2e:	0f b6 c0             	movzbl %al,%eax
  31:	0f b6 80 00 00 00 00 	movzbl 0x0(%eax),%eax
  38:	0f be c0             	movsbl %al,%eax
  3b:	83 ec 0c             	sub    $0xc,%esp
  3e:	50                   	push   %eax
  3f:	e8 fc ff ff ff       	call   40 <do_phase+0x40>
  44:	83 c4 10             	add    $0x10,%esp
  47:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  4b:	8b 45 f4             	mov    -0xc(%ebp),%eax
  4e:	83 f8 08             	cmp    $0x8,%eax
  51:	76 d0                	jbe    23 <do_phase+0x23>
  53:	83 ec 0c             	sub    $0xc,%esp
  56:	6a 0a                	push   $0xa
  58:	e8 fc ff ff ff       	call   59 <do_phase+0x59>
  5d:	83 c4 10             	add    $0x10,%esp
  60:	90                   	nop
  61:	c9                   	leave  
  62:	c3                   	ret    
