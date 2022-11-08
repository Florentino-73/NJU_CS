
phase5.o:     file format elf32-i386


Disassembly of section .text:

00000000 <VilkAwbaqQ>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 10             	sub    $0x10,%esp
   6:	c7 45 f1 4c 6c 77 51 	movl   $0x51776c4c,-0xf(%ebp)
   d:	c7 45 f5 79 59 4c 43 	movl   $0x434c5979,-0xb(%ebp)
  14:	66 c7 45 f9 56 4d    	movw   $0x4d56,-0x7(%ebp)
  1a:	c6 45 fb 00          	movb   $0x0,-0x5(%ebp)
  1e:	c7 45 fc 0b 00 00 00 	movl   $0xb,-0x4(%ebp)
  25:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
  29:	78 15                	js     40 <VilkAwbaqQ+0x40>
  2b:	8b 45 08             	mov    0x8(%ebp),%eax
  2e:	3b 45 fc             	cmp    -0x4(%ebp),%eax
  31:	7d 0d                	jge    40 <VilkAwbaqQ+0x40>
  33:	8d 55 f1             	lea    -0xf(%ebp),%edx
  36:	8b 45 08             	mov    0x8(%ebp),%eax
  39:	01 d0                	add    %edx,%eax
  3b:	0f b6 00             	movzbl (%eax),%eax
  3e:	eb 05                	jmp    45 <VilkAwbaqQ+0x45>
  40:	b8 00 00 00 00       	mov    $0x0,%eax
  45:	c9                   	leave  
  46:	c3                   	ret    

00000047 <transform_code>:
  47:	55                   	push   %ebp
  48:	89 e5                	mov    %esp,%ebp
  4a:	8b 45 0c             	mov    0xc(%ebp),%eax
  4d:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
  54:	83 e0 07             	and    $0x7,%eax
  57:	83 f8 07             	cmp    $0x7,%eax
  5a:	77 74                	ja     d0 <transform_code+0x89>
  5c:	8b 04 85 50 00 00 00 	mov    0x50(,%eax,4),%eax
  63:	ff e0                	jmp    *%eax
  65:	f7 55 08             	notl   0x8(%ebp)
  68:	eb 6a                	jmp    d4 <transform_code+0x8d>
  6a:	8b 45 0c             	mov    0xc(%ebp),%eax
  6d:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
  74:	83 e0 03             	and    $0x3,%eax
  77:	89 c1                	mov    %eax,%ecx
  79:	d3 7d 08             	sarl   %cl,0x8(%ebp)
  7c:	eb 56                	jmp    d4 <transform_code+0x8d>
  7e:	8b 45 0c             	mov    0xc(%ebp),%eax
  81:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
  88:	f7 d0                	not    %eax
  8a:	21 45 08             	and    %eax,0x8(%ebp)
  8d:	eb 45                	jmp    d4 <transform_code+0x8d>
  8f:	8b 45 0c             	mov    0xc(%ebp),%eax
  92:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
  99:	c1 e0 08             	shl    $0x8,%eax
  9c:	09 45 08             	or     %eax,0x8(%ebp)
  9f:	eb 33                	jmp    d4 <transform_code+0x8d>
  a1:	8b 45 0c             	mov    0xc(%ebp),%eax
  a4:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
  ab:	31 45 08             	xor    %eax,0x8(%ebp)
  ae:	eb 24                	jmp    d4 <transform_code+0x8d>
  b0:	8b 45 0c             	mov    0xc(%ebp),%eax
  b3:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
  ba:	f7 d0                	not    %eax
  bc:	09 45 08             	or     %eax,0x8(%ebp)
  bf:	eb 13                	jmp    d4 <transform_code+0x8d>
  c1:	8b 45 0c             	mov    0xc(%ebp),%eax
  c4:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
  cb:	01 45 08             	add    %eax,0x8(%ebp)
  ce:	eb 04                	jmp    d4 <transform_code+0x8d>
  d0:	f7 5d 08             	negl   0x8(%ebp)
  d3:	90                   	nop
  d4:	8b 45 08             	mov    0x8(%ebp),%eax
  d7:	5d                   	pop    %ebp
  d8:	c3                   	ret    

000000d9 <generate_code>:
  d9:	55                   	push   %ebp
  da:	89 e5                	mov    %esp,%ebp
  dc:	83 ec 10             	sub    $0x10,%esp
  df:	8b 45 08             	mov    0x8(%ebp),%eax
  e2:	a3 00 00 00 00       	mov    %eax,0x0
  e7:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  ee:	eb 1a                	jmp    10a <generate_code+0x31>
  f0:	a1 00 00 00 00       	mov    0x0,%eax
  f5:	ff 75 fc             	pushl  -0x4(%ebp)
  f8:	50                   	push   %eax
  f9:	e8 fc ff ff ff       	call   fa <generate_code+0x21>
  fe:	83 c4 08             	add    $0x8,%esp
 101:	a3 00 00 00 00       	mov    %eax,0x0
 106:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
 10a:	8b 45 fc             	mov    -0x4(%ebp),%eax
 10d:	83 f8 0b             	cmp    $0xb,%eax
 110:	76 de                	jbe    f0 <generate_code+0x17>
 112:	90                   	nop
 113:	c9                   	leave  
 114:	c3                   	ret    

00000115 <encode_1>:
 115:	55                   	push   %ebp
 116:	89 e5                	mov    %esp,%ebp
 118:	83 ec 18             	sub    $0x18,%esp
 11b:	83 ec 0c             	sub    $0xc,%esp
 11e:	ff 75 08             	pushl  0x8(%ebp)
 121:	e8 fc ff ff ff       	call   122 <encode_1+0xd>
 126:	83 c4 10             	add    $0x10,%esp
 129:	89 45 f0             	mov    %eax,-0x10(%ebp)
 12c:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 133:	eb 5b                	jmp    190 <encode_1+0x7b>
 135:	8b 55 f4             	mov    -0xc(%ebp),%edx
 138:	8b 45 08             	mov    0x8(%ebp),%eax
 13b:	01 d0                	add    %edx,%eax
 13d:	0f b6 00             	movzbl (%eax),%eax
 140:	0f be c0             	movsbl %al,%eax
 143:	0f b6 80 00 00 00 00 	movzbl 0x0(%eax),%eax
 14a:	8b 15 00 00 00 00    	mov    0x0,%edx
 150:	31 d0                	xor    %edx,%eax
 152:	89 c1                	mov    %eax,%ecx
 154:	8b 55 f4             	mov    -0xc(%ebp),%edx
 157:	8b 45 08             	mov    0x8(%ebp),%eax
 15a:	01 d0                	add    %edx,%eax
 15c:	83 e1 7f             	and    $0x7f,%ecx
 15f:	89 ca                	mov    %ecx,%edx
 161:	88 10                	mov    %dl,(%eax)
 163:	8b 55 f4             	mov    -0xc(%ebp),%edx
 166:	8b 45 08             	mov    0x8(%ebp),%eax
 169:	01 d0                	add    %edx,%eax
 16b:	0f b6 00             	movzbl (%eax),%eax
 16e:	3c 1f                	cmp    $0x1f,%al
 170:	7e 0f                	jle    181 <encode_1+0x6c>
 172:	8b 55 f4             	mov    -0xc(%ebp),%edx
 175:	8b 45 08             	mov    0x8(%ebp),%eax
 178:	01 d0                	add    %edx,%eax
 17a:	0f b6 00             	movzbl (%eax),%eax
 17d:	3c 7f                	cmp    $0x7f,%al
 17f:	75 0b                	jne    18c <encode_1+0x77>
 181:	8b 55 f4             	mov    -0xc(%ebp),%edx
 184:	8b 45 08             	mov    0x8(%ebp),%eax
 187:	01 d0                	add    %edx,%eax
 189:	c6 00 3f             	movb   $0x3f,(%eax)
 18c:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 190:	8b 45 f4             	mov    -0xc(%ebp),%eax
 193:	3b 45 f0             	cmp    -0x10(%ebp),%eax
 196:	7c 9d                	jl     135 <encode_1+0x20>
 198:	8b 45 f0             	mov    -0x10(%ebp),%eax
 19b:	c9                   	leave  
 19c:	c3                   	ret    

0000019d <encode_2>:
 19d:	55                   	push   %ebp
 19e:	89 e5                	mov    %esp,%ebp
 1a0:	83 ec 18             	sub    $0x18,%esp
 1a3:	83 ec 0c             	sub    $0xc,%esp
 1a6:	ff 75 08             	pushl  0x8(%ebp)
 1a9:	e8 fc ff ff ff       	call   1aa <encode_2+0xd>
 1ae:	83 c4 10             	add    $0x10,%esp
 1b1:	89 45 f0             	mov    %eax,-0x10(%ebp)
 1b4:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 1bb:	eb 5a                	jmp    217 <encode_2+0x7a>
 1bd:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1c0:	8b 45 08             	mov    0x8(%ebp),%eax
 1c3:	01 d0                	add    %edx,%eax
 1c5:	0f b6 00             	movzbl (%eax),%eax
 1c8:	0f be c0             	movsbl %al,%eax
 1cb:	0f b6 80 00 00 00 00 	movzbl 0x0(%eax),%eax
 1d2:	8b 15 00 00 00 00    	mov    0x0,%edx
 1d8:	8d 0c 10             	lea    (%eax,%edx,1),%ecx
 1db:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1de:	8b 45 08             	mov    0x8(%ebp),%eax
 1e1:	01 d0                	add    %edx,%eax
 1e3:	83 e1 7f             	and    $0x7f,%ecx
 1e6:	89 ca                	mov    %ecx,%edx
 1e8:	88 10                	mov    %dl,(%eax)
 1ea:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1ed:	8b 45 08             	mov    0x8(%ebp),%eax
 1f0:	01 d0                	add    %edx,%eax
 1f2:	0f b6 00             	movzbl (%eax),%eax
 1f5:	3c 1f                	cmp    $0x1f,%al
 1f7:	7e 0f                	jle    208 <encode_2+0x6b>
 1f9:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1fc:	8b 45 08             	mov    0x8(%ebp),%eax
 1ff:	01 d0                	add    %edx,%eax
 201:	0f b6 00             	movzbl (%eax),%eax
 204:	3c 7f                	cmp    $0x7f,%al
 206:	75 0b                	jne    213 <encode_2+0x76>
 208:	8b 55 f4             	mov    -0xc(%ebp),%edx
 20b:	8b 45 08             	mov    0x8(%ebp),%eax
 20e:	01 d0                	add    %edx,%eax
 210:	c6 00 2a             	movb   $0x2a,(%eax)
 213:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 217:	8b 45 f4             	mov    -0xc(%ebp),%eax
 21a:	3b 45 f0             	cmp    -0x10(%ebp),%eax
 21d:	7c 9e                	jl     1bd <encode_2+0x20>
 21f:	8b 45 f0             	mov    -0x10(%ebp),%eax
 222:	c9                   	leave  
 223:	c3                   	ret    

00000224 <do_phase>:
 224:	55                   	push   %ebp
 225:	89 e5                	mov    %esp,%ebp
 227:	83 ec 08             	sub    $0x8,%esp
 22a:	68 e8 00 00 00       	push   $0xe8
 22f:	e8 fc ff ff ff       	call   230 <do_phase+0xc>
 234:	83 c4 04             	add    $0x4,%esp
 237:	a1 00 00 00 00       	mov    0x0,%eax
 23c:	83 ec 0c             	sub    $0xc,%esp
 23f:	68 00 00 00 00       	push   $0x0
 244:	ff d0                	call   *%eax
 246:	83 c4 10             	add    $0x10,%esp
 249:	83 ec 0c             	sub    $0xc,%esp
 24c:	68 00 00 00 00       	push   $0x0
 251:	e8 fc ff ff ff       	call   252 <do_phase+0x2e>
 256:	83 c4 10             	add    $0x10,%esp
 259:	90                   	nop
 25a:	c9                   	leave  
 25b:	c3                   	ret    
