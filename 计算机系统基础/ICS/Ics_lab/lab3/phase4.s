
phase4.o:     file format elf32-i386


Disassembly of section .text:

00000000 <HpBLANeZil>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	90                   	nop
   4:	90                   	nop
   5:	90                   	nop
   6:	90                   	nop
   7:	90                   	nop
   8:	90                   	nop
   9:	90                   	nop
   a:	90                   	nop
   b:	90                   	nop
   c:	90                   	nop
   d:	90                   	nop
   e:	90                   	nop
   f:	90                   	nop
  10:	90                   	nop
  11:	90                   	nop
  12:	90                   	nop
  13:	90                   	nop
  14:	90                   	nop
  15:	90                   	nop
  16:	90                   	nop
  17:	90                   	nop
  18:	90                   	nop
  19:	90                   	nop
  1a:	90                   	nop
  1b:	90                   	nop
  1c:	90                   	nop
  1d:	90                   	nop
  1e:	90                   	nop
  1f:	90                   	nop
  20:	90                   	nop
  21:	90                   	nop
  22:	90                   	nop
  23:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  28:	5d                   	pop    %ebp
  29:	c3                   	ret    

0000002a <do_phase>:
  2a:	55                   	push   %ebp
  2b:	89 e5                	mov    %esp,%ebp
  2d:	83 ec 28             	sub    $0x28,%esp
  30:	c7 45 e6 43 45 59 41 	movl   $0x41594543,-0x1a(%ebp)
  37:	c7 45 ea 55 54 5a 4f 	movl   $0x4f5a5455,-0x16(%ebp)
  3e:	66 c7 45 ee 50 00    	movw   $0x50,-0x12(%ebp)
  44:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  4b:	e9 e0 00 00 00       	jmp    130 <do_phase+0x106>
  50:	8d 55 e6             	lea    -0x1a(%ebp),%edx
  53:	8b 45 f0             	mov    -0x10(%ebp),%eax
  56:	01 d0                	add    %edx,%eax
  58:	0f b6 00             	movzbl (%eax),%eax
  5b:	88 45 f7             	mov    %al,-0x9(%ebp)
  5e:	0f be 45 f7          	movsbl -0x9(%ebp),%eax
  62:	83 e8 41             	sub    $0x41,%eax
  65:	83 f8 19             	cmp    $0x19,%eax
  68:	0f 87 b0 00 00 00    	ja     11e <do_phase+0xf4>
  6e:	8b 04 85 04 00 00 00 	mov    0x4(,%eax,4),%eax
  75:	ff e0                	jmp    *%eax
  77:	c6 45 f7 38          	movb   $0x38,-0x9(%ebp)
  7b:	e9 9e 00 00 00       	jmp    11e <do_phase+0xf4>
  80:	c6 45 f7 63          	movb   $0x63,-0x9(%ebp)
  84:	e9 95 00 00 00       	jmp    11e <do_phase+0xf4>
  89:	c6 45 f7 31          	movb   $0x31,-0x9(%ebp)
  8d:	e9 8c 00 00 00       	jmp    11e <do_phase+0xf4>
  92:	c6 45 f7 30          	movb   $0x30,-0x9(%ebp)
  96:	e9 83 00 00 00       	jmp    11e <do_phase+0xf4>
  9b:	c6 45 f7 33          	movb   $0x33,-0x9(%ebp)
  9f:	eb 7d                	jmp    11e <do_phase+0xf4>
  a1:	c6 45 f7 4f          	movb   $0x4f,-0x9(%ebp)
  a5:	eb 77                	jmp    11e <do_phase+0xf4>
  a7:	c6 45 f7 56          	movb   $0x56,-0x9(%ebp)
  ab:	eb 71                	jmp    11e <do_phase+0xf4>
  ad:	c6 45 f7 57          	movb   $0x57,-0x9(%ebp)
  b1:	eb 6b                	jmp    11e <do_phase+0xf4>
  b3:	c6 45 f7 5d          	movb   $0x5d,-0x9(%ebp)
  b7:	eb 65                	jmp    11e <do_phase+0xf4>
  b9:	c6 45 f7 54          	movb   $0x54,-0x9(%ebp)
  bd:	eb 5f                	jmp    11e <do_phase+0xf4>
  bf:	c6 45 f7 68          	movb   $0x68,-0x9(%ebp)
  c3:	eb 59                	jmp    11e <do_phase+0xf4>
  c5:	c6 45 f7 39          	movb   $0x39,-0x9(%ebp)
  c9:	eb 53                	jmp    11e <do_phase+0xf4>
  cb:	c6 45 f7 36          	movb   $0x36,-0x9(%ebp)
  cf:	eb 4d                	jmp    11e <do_phase+0xf4>
  d1:	c6 45 f7 57          	movb   $0x57,-0x9(%ebp)
  d5:	eb 47                	jmp    11e <do_phase+0xf4>
  d7:	c6 45 f7 7b          	movb   $0x7b,-0x9(%ebp)
  db:	eb 41                	jmp    11e <do_phase+0xf4>
  dd:	c6 45 f7 5b          	movb   $0x5b,-0x9(%ebp)
  e1:	eb 3b                	jmp    11e <do_phase+0xf4>
  e3:	c6 45 f7 34          	movb   $0x34,-0x9(%ebp)
  e7:	eb 35                	jmp    11e <do_phase+0xf4>
  e9:	c6 45 f7 32          	movb   $0x32,-0x9(%ebp)
  ed:	eb 2f                	jmp    11e <do_phase+0xf4>
  ef:	c6 45 f7 56          	movb   $0x56,-0x9(%ebp)
  f3:	eb 29                	jmp    11e <do_phase+0xf4>
  f5:	c6 45 f7 5b          	movb   $0x5b,-0x9(%ebp)
  f9:	eb 23                	jmp    11e <do_phase+0xf4>
  fb:	c6 45 f7 43          	movb   $0x43,-0x9(%ebp)
  ff:	eb 1d                	jmp    11e <do_phase+0xf4>
 101:	c6 45 f7 6e          	movb   $0x6e,-0x9(%ebp)
 105:	eb 17                	jmp    11e <do_phase+0xf4>
 107:	c6 45 f7 35          	movb   $0x35,-0x9(%ebp)
 10b:	eb 11                	jmp    11e <do_phase+0xf4>
 10d:	c6 45 f7 3d          	movb   $0x3d,-0x9(%ebp)
 111:	eb 0b                	jmp    11e <do_phase+0xf4>
 113:	c6 45 f7 63          	movb   $0x63,-0x9(%ebp)
 117:	eb 05                	jmp    11e <do_phase+0xf4>
 119:	c6 45 f7 37          	movb   $0x37,-0x9(%ebp)
 11d:	90                   	nop
 11e:	8d 55 dc             	lea    -0x24(%ebp),%edx
 121:	8b 45 f0             	mov    -0x10(%ebp),%eax
 124:	01 c2                	add    %eax,%edx
 126:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
 12a:	88 02                	mov    %al,(%edx)
 12c:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 130:	8b 45 f0             	mov    -0x10(%ebp),%eax
 133:	83 f8 08             	cmp    $0x8,%eax
 136:	0f 86 14 ff ff ff    	jbe    50 <do_phase+0x26>
 13c:	8d 55 dc             	lea    -0x24(%ebp),%edx
 13f:	8b 45 f0             	mov    -0x10(%ebp),%eax
 142:	01 d0                	add    %edx,%eax
 144:	c6 00 00             	movb   $0x0,(%eax)
 147:	83 ec 0c             	sub    $0xc,%esp
 14a:	8d 45 dc             	lea    -0x24(%ebp),%eax
 14d:	50                   	push   %eax
 14e:	e8 fc ff ff ff       	call   14f <do_phase+0x125>
 153:	83 c4 10             	add    $0x10,%esp
 156:	90                   	nop
 157:	c9                   	leave  
 158:	c3                   	ret    
