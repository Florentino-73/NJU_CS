
lb3:     file format elf32-i386


Disassembly of section .init:

080482cc <_init>:
 80482cc:	53                   	push   %ebx
 80482cd:	83 ec 08             	sub    $0x8,%esp
 80482d0:	e8 bb 00 00 00       	call   8048390 <__x86.get_pc_thunk.bx>
 80482d5:	81 c3 2b 1d 00 00    	add    $0x1d2b,%ebx
 80482db:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 80482e1:	85 c0                	test   %eax,%eax
 80482e3:	74 05                	je     80482ea <_init+0x1e>
 80482e5:	e8 46 00 00 00       	call   8048330 <__gmon_start__@plt>
 80482ea:	83 c4 08             	add    $0x8,%esp
 80482ed:	5b                   	pop    %ebx
 80482ee:	c3                   	ret    

Disassembly of section .plt:

080482f0 <.plt>:
 80482f0:	ff 35 04 a0 04 08    	pushl  0x804a004
 80482f6:	ff 25 08 a0 04 08    	jmp    *0x804a008
 80482fc:	00 00                	add    %al,(%eax)
	...

08048300 <puts@plt>:
 8048300:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048306:	68 00 00 00 00       	push   $0x0
 804830b:	e9 e0 ff ff ff       	jmp    80482f0 <.plt>

08048310 <__libc_start_main@plt>:
 8048310:	ff 25 10 a0 04 08    	jmp    *0x804a010
 8048316:	68 08 00 00 00       	push   $0x8
 804831b:	e9 d0 ff ff ff       	jmp    80482f0 <.plt>

08048320 <putchar@plt>:
 8048320:	ff 25 14 a0 04 08    	jmp    *0x804a014
 8048326:	68 10 00 00 00       	push   $0x10
 804832b:	e9 c0 ff ff ff       	jmp    80482f0 <.plt>

Disassembly of section .plt.got:

08048330 <__gmon_start__@plt>:
 8048330:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 8048336:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

08048340 <_start>:
 8048340:	31 ed                	xor    %ebp,%ebp
 8048342:	5e                   	pop    %esi
 8048343:	89 e1                	mov    %esp,%ecx
 8048345:	83 e4 f0             	and    $0xfffffff0,%esp
 8048348:	50                   	push   %eax
 8048349:	54                   	push   %esp
 804834a:	52                   	push   %edx
 804834b:	e8 23 00 00 00       	call   8048373 <_start+0x33>
 8048350:	81 c3 b0 1c 00 00    	add    $0x1cb0,%ebx
 8048356:	8d 83 60 e5 ff ff    	lea    -0x1aa0(%ebx),%eax
 804835c:	50                   	push   %eax
 804835d:	8d 83 00 e5 ff ff    	lea    -0x1b00(%ebx),%eax
 8048363:	50                   	push   %eax
 8048364:	51                   	push   %ecx
 8048365:	56                   	push   %esi
 8048366:	c7 c0 56 84 04 08    	mov    $0x8048456,%eax
 804836c:	50                   	push   %eax
 804836d:	e8 9e ff ff ff       	call   8048310 <__libc_start_main@plt>
 8048372:	f4                   	hlt    
 8048373:	8b 1c 24             	mov    (%esp),%ebx
 8048376:	c3                   	ret    
 8048377:	66 90                	xchg   %ax,%ax
 8048379:	66 90                	xchg   %ax,%ax
 804837b:	66 90                	xchg   %ax,%ax
 804837d:	66 90                	xchg   %ax,%ax
 804837f:	90                   	nop

08048380 <_dl_relocate_static_pie>:
 8048380:	f3 c3                	repz ret 
 8048382:	66 90                	xchg   %ax,%ax
 8048384:	66 90                	xchg   %ax,%ax
 8048386:	66 90                	xchg   %ax,%ax
 8048388:	66 90                	xchg   %ax,%ax
 804838a:	66 90                	xchg   %ax,%ax
 804838c:	66 90                	xchg   %ax,%ax
 804838e:	66 90                	xchg   %ax,%ax

08048390 <__x86.get_pc_thunk.bx>:
 8048390:	8b 1c 24             	mov    (%esp),%ebx
 8048393:	c3                   	ret    
 8048394:	66 90                	xchg   %ax,%ax
 8048396:	66 90                	xchg   %ax,%ax
 8048398:	66 90                	xchg   %ax,%ax
 804839a:	66 90                	xchg   %ax,%ax
 804839c:	66 90                	xchg   %ax,%ax
 804839e:	66 90                	xchg   %ax,%ax

080483a0 <deregister_tm_clones>:
 80483a0:	b8 28 a0 04 08       	mov    $0x804a028,%eax
 80483a5:	3d 28 a0 04 08       	cmp    $0x804a028,%eax
 80483aa:	74 24                	je     80483d0 <deregister_tm_clones+0x30>
 80483ac:	b8 00 00 00 00       	mov    $0x0,%eax
 80483b1:	85 c0                	test   %eax,%eax
 80483b3:	74 1b                	je     80483d0 <deregister_tm_clones+0x30>
 80483b5:	55                   	push   %ebp
 80483b6:	89 e5                	mov    %esp,%ebp
 80483b8:	83 ec 14             	sub    $0x14,%esp
 80483bb:	68 28 a0 04 08       	push   $0x804a028
 80483c0:	ff d0                	call   *%eax
 80483c2:	83 c4 10             	add    $0x10,%esp
 80483c5:	c9                   	leave  
 80483c6:	c3                   	ret    
 80483c7:	89 f6                	mov    %esi,%esi
 80483c9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 80483d0:	f3 c3                	repz ret 
 80483d2:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 80483d9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080483e0 <register_tm_clones>:
 80483e0:	b8 28 a0 04 08       	mov    $0x804a028,%eax
 80483e5:	2d 28 a0 04 08       	sub    $0x804a028,%eax
 80483ea:	c1 f8 02             	sar    $0x2,%eax
 80483ed:	89 c2                	mov    %eax,%edx
 80483ef:	c1 ea 1f             	shr    $0x1f,%edx
 80483f2:	01 d0                	add    %edx,%eax
 80483f4:	d1 f8                	sar    %eax
 80483f6:	74 20                	je     8048418 <register_tm_clones+0x38>
 80483f8:	ba 00 00 00 00       	mov    $0x0,%edx
 80483fd:	85 d2                	test   %edx,%edx
 80483ff:	74 17                	je     8048418 <register_tm_clones+0x38>
 8048401:	55                   	push   %ebp
 8048402:	89 e5                	mov    %esp,%ebp
 8048404:	83 ec 10             	sub    $0x10,%esp
 8048407:	50                   	push   %eax
 8048408:	68 28 a0 04 08       	push   $0x804a028
 804840d:	ff d2                	call   *%edx
 804840f:	83 c4 10             	add    $0x10,%esp
 8048412:	c9                   	leave  
 8048413:	c3                   	ret    
 8048414:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048418:	f3 c3                	repz ret 
 804841a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

08048420 <__do_global_dtors_aux>:
 8048420:	80 3d 40 a0 04 08 00 	cmpb   $0x0,0x804a040
 8048427:	75 17                	jne    8048440 <__do_global_dtors_aux+0x20>
 8048429:	55                   	push   %ebp
 804842a:	89 e5                	mov    %esp,%ebp
 804842c:	83 ec 08             	sub    $0x8,%esp
 804842f:	e8 6c ff ff ff       	call   80483a0 <deregister_tm_clones>
 8048434:	c6 05 40 a0 04 08 01 	movb   $0x1,0x804a040
 804843b:	c9                   	leave  
 804843c:	c3                   	ret    
 804843d:	8d 76 00             	lea    0x0(%esi),%esi
 8048440:	f3 c3                	repz ret 
 8048442:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 8048449:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048450 <frame_dummy>:
 8048450:	55                   	push   %ebp
 8048451:	89 e5                	mov    %esp,%ebp
 8048453:	5d                   	pop    %ebp
 8048454:	eb 8a                	jmp    80483e0 <register_tm_clones>

08048456 <main>:
 8048456:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 804845a:	83 e4 f0             	and    $0xfffffff0,%esp
 804845d:	ff 71 fc             	pushl  -0x4(%ecx)
 8048460:	55                   	push   %ebp
 8048461:	89 e5                	mov    %esp,%ebp
 8048463:	51                   	push   %ecx
 8048464:	83 ec 04             	sub    $0x4,%esp
 8048467:	a1 24 a0 04 08       	mov    0x804a024,%eax
 804846c:	85 c0                	test   %eax,%eax
 804846e:	74 09                	je     8048479 <main+0x23>
 8048470:	a1 24 a0 04 08       	mov    0x804a024,%eax
 8048475:	ff d0                	call   *%eax
 8048477:	eb 10                	jmp    8048489 <main+0x33>
 8048479:	83 ec 0c             	sub    $0xc,%esp
 804847c:	68 48 86 04 08       	push   $0x8048648
 8048481:	e8 7a fe ff ff       	call   8048300 <puts@plt>
 8048486:	83 c4 10             	add    $0x10,%esp
 8048489:	b8 00 00 00 00       	mov    $0x0,%eax
 804848e:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 8048491:	c9                   	leave  
 8048492:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048495:	c3                   	ret    

08048496 <do_phase>:
 8048496:	55                   	push   %ebp
 8048497:	89 e5                	mov    %esp,%ebp
 8048499:	83 ec 18             	sub    $0x18,%esp
 804849c:	c7 45 ea 67 6c 77 69 	movl   $0x69776c67,-0x16(%ebp)
 80484a3:	c7 45 ee 7a 71 6e 72 	movl   $0x726e717a,-0x12(%ebp)
 80484aa:	66 c7 45 f2 76 00    	movw   $0x76,-0xe(%ebp)
 80484b0:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 80484b7:	eb 28                	jmp    80484e1 <do_phase+0x4b>
 80484b9:	8d 55 ea             	lea    -0x16(%ebp),%edx
 80484bc:	8b 45 f4             	mov    -0xc(%ebp),%eax
 80484bf:	01 d0                	add    %edx,%eax
 80484c1:	0f b6 00             	movzbl (%eax),%eax
 80484c4:	0f b6 c0             	movzbl %al,%eax
 80484c7:	0f b6 80 60 a0 04 08 	movzbl 0x804a060(%eax),%eax
 80484ce:	0f be c0             	movsbl %al,%eax
 80484d1:	83 ec 0c             	sub    $0xc,%esp
 80484d4:	50                   	push   %eax
 80484d5:	e8 46 fe ff ff       	call   8048320 <putchar@plt>
 80484da:	83 c4 10             	add    $0x10,%esp
 80484dd:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 80484e1:	8b 45 f4             	mov    -0xc(%ebp),%eax
 80484e4:	83 f8 08             	cmp    $0x8,%eax
 80484e7:	76 d0                	jbe    80484b9 <do_phase+0x23>
 80484e9:	83 ec 0c             	sub    $0xc,%esp
 80484ec:	6a 0a                	push   $0xa
 80484ee:	e8 2d fe ff ff       	call   8048320 <putchar@plt>
 80484f3:	83 c4 10             	add    $0x10,%esp
 80484f6:	90                   	nop
 80484f7:	c9                   	leave  
 80484f8:	c3                   	ret    
 80484f9:	66 90                	xchg   %ax,%ax
 80484fb:	66 90                	xchg   %ax,%ax
 80484fd:	66 90                	xchg   %ax,%ax
 80484ff:	90                   	nop

08048500 <__libc_csu_init>:
 8048500:	55                   	push   %ebp
 8048501:	57                   	push   %edi
 8048502:	56                   	push   %esi
 8048503:	53                   	push   %ebx
 8048504:	e8 87 fe ff ff       	call   8048390 <__x86.get_pc_thunk.bx>
 8048509:	81 c3 f7 1a 00 00    	add    $0x1af7,%ebx
 804850f:	83 ec 0c             	sub    $0xc,%esp
 8048512:	8b 6c 24 28          	mov    0x28(%esp),%ebp
 8048516:	8d b3 10 ff ff ff    	lea    -0xf0(%ebx),%esi
 804851c:	e8 ab fd ff ff       	call   80482cc <_init>
 8048521:	8d 83 0c ff ff ff    	lea    -0xf4(%ebx),%eax
 8048527:	29 c6                	sub    %eax,%esi
 8048529:	c1 fe 02             	sar    $0x2,%esi
 804852c:	85 f6                	test   %esi,%esi
 804852e:	74 25                	je     8048555 <__libc_csu_init+0x55>
 8048530:	31 ff                	xor    %edi,%edi
 8048532:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048538:	83 ec 04             	sub    $0x4,%esp
 804853b:	55                   	push   %ebp
 804853c:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048540:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048544:	ff 94 bb 0c ff ff ff 	call   *-0xf4(%ebx,%edi,4)
 804854b:	83 c7 01             	add    $0x1,%edi
 804854e:	83 c4 10             	add    $0x10,%esp
 8048551:	39 fe                	cmp    %edi,%esi
 8048553:	75 e3                	jne    8048538 <__libc_csu_init+0x38>
 8048555:	83 c4 0c             	add    $0xc,%esp
 8048558:	5b                   	pop    %ebx
 8048559:	5e                   	pop    %esi
 804855a:	5f                   	pop    %edi
 804855b:	5d                   	pop    %ebp
 804855c:	c3                   	ret    
 804855d:	8d 76 00             	lea    0x0(%esi),%esi

08048560 <__libc_csu_fini>:
 8048560:	f3 c3                	repz ret 

Disassembly of section .fini:

08048564 <_fini>:
 8048564:	53                   	push   %ebx
 8048565:	83 ec 08             	sub    $0x8,%esp
 8048568:	e8 23 fe ff ff       	call   8048390 <__x86.get_pc_thunk.bx>
 804856d:	81 c3 93 1a 00 00    	add    $0x1a93,%ebx
 8048573:	83 c4 08             	add    $0x8,%esp
 8048576:	5b                   	pop    %ebx
 8048577:	c3                   	ret    
