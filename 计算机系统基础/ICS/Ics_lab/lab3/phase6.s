
phase6.o:     file format elf32-i386


Disassembly of section .text:

00000000 <VilkAwbaqQ>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 20             	sub    $0x20,%esp
   6:	e8 fc ff ff ff       	call   7 <VilkAwbaqQ+0x7>
   b:	05 01 00 00 00       	add    $0x1,%eax
  10:	c7 45 e4 75 4d 76 73 	movl   $0x73764d75,-0x1c(%ebp)
  17:	c7 45 e8 66 56 67 78 	movl   $0x78675666,-0x18(%ebp)
  1e:	c7 45 ec 4e 71 52 4d 	movl   $0x4d52714e,-0x14(%ebp)
  25:	c7 45 f0 57 58 57 74 	movl   $0x74575857,-0x10(%ebp)
  2c:	c7 45 f4 42 74 44 59 	movl   $0x59447442,-0xc(%ebp)
  33:	c7 45 f8 70 4a 75 00 	movl   $0x754a70,-0x8(%ebp)
  3a:	c7 45 fc 18 00 00 00 	movl   $0x18,-0x4(%ebp)
  41:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
  45:	78 15                	js     5c <VilkAwbaqQ+0x5c>
  47:	8b 45 08             	mov    0x8(%ebp),%eax
  4a:	3b 45 fc             	cmp    -0x4(%ebp),%eax
  4d:	7d 0d                	jge    5c <VilkAwbaqQ+0x5c>
  4f:	8d 55 e4             	lea    -0x1c(%ebp),%edx
  52:	8b 45 08             	mov    0x8(%ebp),%eax
  55:	01 d0                	add    %edx,%eax
  57:	0f b6 00             	movzbl (%eax),%eax
  5a:	eb 05                	jmp    61 <VilkAwbaqQ+0x61>
  5c:	b8 00 00 00 00       	mov    $0x0,%eax
  61:	c9                   	leave  
  62:	c3                   	ret    

00000063 <transform_code>:
  63:	55                   	push   %ebp
  64:	89 e5                	mov    %esp,%ebp
  66:	e8 fc ff ff ff       	call   67 <transform_code+0x4>
  6b:	05 01 00 00 00       	add    $0x1,%eax
  70:	8b 90 00 00 00 00    	mov    0x0(%eax),%edx
  76:	8b 4d 0c             	mov    0xc(%ebp),%ecx
  79:	8b 14 8a             	mov    (%edx,%ecx,4),%edx
  7c:	83 e2 07             	and    $0x7,%edx
  7f:	83 fa 07             	cmp    $0x7,%edx
  82:	0f 87 85 00 00 00    	ja     10d <.L6>
  88:	c1 e2 02             	shl    $0x2,%edx
  8b:	8b 94 02 50 00 00 00 	mov    0x50(%edx,%eax,1),%edx
  92:	01 c2                	add    %eax,%edx
  94:	ff e2                	jmp    *%edx

00000096 <.L14>:
  96:	f7 55 08             	notl   0x8(%ebp)
  99:	eb 76                	jmp    111 <.L6+0x4>

0000009b <.L13>:
  9b:	8b 80 00 00 00 00    	mov    0x0(%eax),%eax
  a1:	8b 55 0c             	mov    0xc(%ebp),%edx
  a4:	8b 04 90             	mov    (%eax,%edx,4),%eax
  a7:	83 e0 03             	and    $0x3,%eax
  aa:	89 c1                	mov    %eax,%ecx
  ac:	d3 7d 08             	sarl   %cl,0x8(%ebp)
  af:	eb 60                	jmp    111 <.L6+0x4>

000000b1 <.L12>:
  b1:	8b 80 00 00 00 00    	mov    0x0(%eax),%eax
  b7:	8b 55 0c             	mov    0xc(%ebp),%edx
  ba:	8b 04 90             	mov    (%eax,%edx,4),%eax
  bd:	f7 d0                	not    %eax
  bf:	21 45 08             	and    %eax,0x8(%ebp)
  c2:	eb 4d                	jmp    111 <.L6+0x4>

000000c4 <.L11>:
  c4:	8b 80 00 00 00 00    	mov    0x0(%eax),%eax
  ca:	8b 55 0c             	mov    0xc(%ebp),%edx
  cd:	8b 04 90             	mov    (%eax,%edx,4),%eax
  d0:	c1 e0 08             	shl    $0x8,%eax
  d3:	09 45 08             	or     %eax,0x8(%ebp)
  d6:	eb 39                	jmp    111 <.L6+0x4>

000000d8 <.L10>:
  d8:	8b 80 00 00 00 00    	mov    0x0(%eax),%eax
  de:	8b 55 0c             	mov    0xc(%ebp),%edx
  e1:	8b 04 90             	mov    (%eax,%edx,4),%eax
  e4:	31 45 08             	xor    %eax,0x8(%ebp)
  e7:	eb 28                	jmp    111 <.L6+0x4>

000000e9 <.L9>:
  e9:	8b 80 00 00 00 00    	mov    0x0(%eax),%eax
  ef:	8b 55 0c             	mov    0xc(%ebp),%edx
  f2:	8b 04 90             	mov    (%eax,%edx,4),%eax
  f5:	f7 d0                	not    %eax
  f7:	09 45 08             	or     %eax,0x8(%ebp)
  fa:	eb 15                	jmp    111 <.L6+0x4>

000000fc <.L7>:
  fc:	8b 80 00 00 00 00    	mov    0x0(%eax),%eax
 102:	8b 55 0c             	mov    0xc(%ebp),%edx
 105:	8b 04 90             	mov    (%eax,%edx,4),%eax
 108:	01 45 08             	add    %eax,0x8(%ebp)
 10b:	eb 04                	jmp    111 <.L6+0x4>

0000010d <.L6>:
 10d:	f7 5d 08             	negl   0x8(%ebp)
 110:	90                   	nop
 111:	8b 45 08             	mov    0x8(%ebp),%eax
 114:	5d                   	pop    %ebp
 115:	c3                   	ret    

00000116 <generate_code>:
 116:	55                   	push   %ebp
 117:	89 e5                	mov    %esp,%ebp
 119:	53                   	push   %ebx
 11a:	83 ec 14             	sub    $0x14,%esp
 11d:	e8 fc ff ff ff       	call   11e <generate_code+0x8>
 122:	81 c3 02 00 00 00    	add    $0x2,%ebx
 128:	8b 83 00 00 00 00    	mov    0x0(%ebx),%eax
 12e:	8b 55 08             	mov    0x8(%ebp),%edx
 131:	89 10                	mov    %edx,(%eax)
 133:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 13a:	eb 25                	jmp    161 <generate_code+0x4b>
 13c:	8b 83 00 00 00 00    	mov    0x0(%ebx),%eax
 142:	8b 00                	mov    (%eax),%eax
 144:	83 ec 08             	sub    $0x8,%esp
 147:	ff 75 f4             	pushl  -0xc(%ebp)
 14a:	50                   	push   %eax
 14b:	e8 fc ff ff ff       	call   14c <generate_code+0x36>
 150:	83 c4 10             	add    $0x10,%esp
 153:	89 c2                	mov    %eax,%edx
 155:	8b 83 00 00 00 00    	mov    0x0(%ebx),%eax
 15b:	89 10                	mov    %edx,(%eax)
 15d:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 161:	8b 45 f4             	mov    -0xc(%ebp),%eax
 164:	83 f8 0b             	cmp    $0xb,%eax
 167:	76 d3                	jbe    13c <generate_code+0x26>
 169:	90                   	nop
 16a:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 16d:	c9                   	leave  
 16e:	c3                   	ret    

0000016f <encode_1>:
 16f:	55                   	push   %ebp
 170:	89 e5                	mov    %esp,%ebp
 172:	53                   	push   %ebx
 173:	83 ec 14             	sub    $0x14,%esp
 176:	e8 fc ff ff ff       	call   177 <encode_1+0x8>
 17b:	81 c3 02 00 00 00    	add    $0x2,%ebx
 181:	83 ec 0c             	sub    $0xc,%esp
 184:	ff 75 08             	pushl  0x8(%ebp)
 187:	e8 fc ff ff ff       	call   188 <encode_1+0x19>
 18c:	83 c4 10             	add    $0x10,%esp
 18f:	89 45 f0             	mov    %eax,-0x10(%ebp)
 192:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 199:	eb 60                	jmp    1fb <encode_1+0x8c>
 19b:	8b 55 f4             	mov    -0xc(%ebp),%edx
 19e:	8b 45 08             	mov    0x8(%ebp),%eax
 1a1:	01 d0                	add    %edx,%eax
 1a3:	0f b6 00             	movzbl (%eax),%eax
 1a6:	0f be c0             	movsbl %al,%eax
 1a9:	8b 93 00 00 00 00    	mov    0x0(%ebx),%edx
 1af:	0f b6 14 02          	movzbl (%edx,%eax,1),%edx
 1b3:	8b 83 00 00 00 00    	mov    0x0(%ebx),%eax
 1b9:	8b 00                	mov    (%eax),%eax
 1bb:	89 d1                	mov    %edx,%ecx
 1bd:	31 c1                	xor    %eax,%ecx
 1bf:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1c2:	8b 45 08             	mov    0x8(%ebp),%eax
 1c5:	01 d0                	add    %edx,%eax
 1c7:	83 e1 7f             	and    $0x7f,%ecx
 1ca:	89 ca                	mov    %ecx,%edx
 1cc:	88 10                	mov    %dl,(%eax)
 1ce:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1d1:	8b 45 08             	mov    0x8(%ebp),%eax
 1d4:	01 d0                	add    %edx,%eax
 1d6:	0f b6 00             	movzbl (%eax),%eax
 1d9:	3c 1f                	cmp    $0x1f,%al
 1db:	7e 0f                	jle    1ec <encode_1+0x7d>
 1dd:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1e0:	8b 45 08             	mov    0x8(%ebp),%eax
 1e3:	01 d0                	add    %edx,%eax
 1e5:	0f b6 00             	movzbl (%eax),%eax
 1e8:	3c 7f                	cmp    $0x7f,%al
 1ea:	75 0b                	jne    1f7 <encode_1+0x88>
 1ec:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1ef:	8b 45 08             	mov    0x8(%ebp),%eax
 1f2:	01 d0                	add    %edx,%eax
 1f4:	c6 00 3f             	movb   $0x3f,(%eax)
 1f7:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 1fb:	8b 45 f4             	mov    -0xc(%ebp),%eax
 1fe:	3b 45 f0             	cmp    -0x10(%ebp),%eax
 201:	7c 98                	jl     19b <encode_1+0x2c>
 203:	8b 45 f0             	mov    -0x10(%ebp),%eax
 206:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 209:	c9                   	leave  
 20a:	c3                   	ret    

0000020b <encode_2>:
 20b:	55                   	push   %ebp
 20c:	89 e5                	mov    %esp,%ebp
 20e:	53                   	push   %ebx
 20f:	83 ec 14             	sub    $0x14,%esp
 212:	e8 fc ff ff ff       	call   213 <encode_2+0x8>
 217:	81 c3 02 00 00 00    	add    $0x2,%ebx
 21d:	83 ec 0c             	sub    $0xc,%esp
 220:	ff 75 08             	pushl  0x8(%ebp)
 223:	e8 fc ff ff ff       	call   224 <encode_2+0x19>
 228:	83 c4 10             	add    $0x10,%esp
 22b:	89 45 f0             	mov    %eax,-0x10(%ebp)
 22e:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 235:	eb 5f                	jmp    296 <encode_2+0x8b>
 237:	8b 55 f4             	mov    -0xc(%ebp),%edx
 23a:	8b 45 08             	mov    0x8(%ebp),%eax
 23d:	01 d0                	add    %edx,%eax
 23f:	0f b6 00             	movzbl (%eax),%eax
 242:	0f be c0             	movsbl %al,%eax
 245:	8b 93 00 00 00 00    	mov    0x0(%ebx),%edx
 24b:	0f b6 14 02          	movzbl (%edx,%eax,1),%edx
 24f:	8b 83 00 00 00 00    	mov    0x0(%ebx),%eax
 255:	8b 00                	mov    (%eax),%eax
 257:	8d 0c 02             	lea    (%edx,%eax,1),%ecx
 25a:	8b 55 f4             	mov    -0xc(%ebp),%edx
 25d:	8b 45 08             	mov    0x8(%ebp),%eax
 260:	01 d0                	add    %edx,%eax
 262:	83 e1 7f             	and    $0x7f,%ecx
 265:	89 ca                	mov    %ecx,%edx
 267:	88 10                	mov    %dl,(%eax)
 269:	8b 55 f4             	mov    -0xc(%ebp),%edx
 26c:	8b 45 08             	mov    0x8(%ebp),%eax
 26f:	01 d0                	add    %edx,%eax
 271:	0f b6 00             	movzbl (%eax),%eax
 274:	3c 1f                	cmp    $0x1f,%al
 276:	7e 0f                	jle    287 <encode_2+0x7c>
 278:	8b 55 f4             	mov    -0xc(%ebp),%edx
 27b:	8b 45 08             	mov    0x8(%ebp),%eax
 27e:	01 d0                	add    %edx,%eax
 280:	0f b6 00             	movzbl (%eax),%eax
 283:	3c 7f                	cmp    $0x7f,%al
 285:	75 0b                	jne    292 <encode_2+0x87>
 287:	8b 55 f4             	mov    -0xc(%ebp),%edx
 28a:	8b 45 08             	mov    0x8(%ebp),%eax
 28d:	01 d0                	add    %edx,%eax
 28f:	c6 00 2a             	movb   $0x2a,(%eax)
 292:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 296:	8b 45 f4             	mov    -0xc(%ebp),%eax
 299:	3b 45 f0             	cmp    -0x10(%ebp),%eax
 29c:	7c 99                	jl     237 <encode_2+0x2c>
 29e:	8b 45 f0             	mov    -0x10(%ebp),%eax
 2a1:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 2a4:	c9                   	leave  
 2a5:	c3                   	ret    

000002a6 <do_phase>:
 2a6:	55                   	push   %ebp
 2a7:	89 e5                	mov    %esp,%ebp
 2a9:	53                   	push   %ebx
 2aa:	83 ec 04             	sub    $0x4,%esp
 2ad:	e8 fc ff ff ff       	call   2ae <do_phase+0x8>
 2b2:	81 c3 02 00 00 00    	add    $0x2,%ebx
 2b8:	83 ec 0c             	sub    $0xc,%esp
 2bb:	68 b9 00 00 00       	push   $0xb9
 2c0:	e8 fc ff ff ff       	call   2c1 <do_phase+0x1b>
 2c5:	83 c4 10             	add    $0x10,%esp
 2c8:	8b 83 00 00 00 00    	mov    0x0(%ebx),%eax
 2ce:	8b 00                	mov    (%eax),%eax
 2d0:	83 ec 0c             	sub    $0xc,%esp
 2d3:	8b 93 00 00 00 00    	mov    0x0(%ebx),%edx
 2d9:	52                   	push   %edx
 2da:	ff d0                	call   *%eax
 2dc:	83 c4 10             	add    $0x10,%esp
 2df:	83 ec 0c             	sub    $0xc,%esp
 2e2:	8b 83 00 00 00 00    	mov    0x0(%ebx),%eax
 2e8:	50                   	push   %eax
 2e9:	e8 fc ff ff ff       	call   2ea <do_phase+0x44>
 2ee:	83 c4 10             	add    $0x10,%esp
 2f1:	90                   	nop
 2f2:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 2f5:	c9                   	leave  
 2f6:	c3                   	ret    

Disassembly of section .text.__x86.get_pc_thunk.ax:

00000000 <__x86.get_pc_thunk.ax>:
   0:	90                   	nop
   1:	90                   	nop
   2:	90                   	nop
   3:	90                   	nop

Disassembly of section .text.__x86.get_pc_thunk.bx:

00000000 <__x86.get_pc_thunk.bx>:
   0:	90                   	nop
   1:	90                   	nop
   2:	90                   	nop
   3:	90                   	nop
