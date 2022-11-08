
lb2:     file format elf32-i386


Disassembly of section .init:

080482ec <_init>:
 80482ec:	53                   	push   %ebx
 80482ed:	83 ec 08             	sub    $0x8,%esp
 80482f0:	e8 cb 00 00 00       	call   80483c0 <__x86.get_pc_thunk.bx>
 80482f5:	81 c3 0b 1d 00 00    	add    $0x1d0b,%ebx
 80482fb:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 8048301:	85 c0                	test   %eax,%eax
 8048303:	74 05                	je     804830a <_init+0x1e>
 8048305:	e8 56 00 00 00       	call   8048360 <__gmon_start__@plt>
 804830a:	83 c4 08             	add    $0x8,%esp
 804830d:	5b                   	pop    %ebx
 804830e:	c3                   	ret    

Disassembly of section .plt:

08048310 <.plt>:
 8048310:	ff 35 04 a0 04 08    	pushl  0x804a004
 8048316:	ff 25 08 a0 04 08    	jmp    *0x804a008
 804831c:	00 00                	add    %al,(%eax)
	...

08048320 <strcmp@plt>:
 8048320:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048326:	68 00 00 00 00       	push   $0x0
 804832b:	e9 e0 ff ff ff       	jmp    8048310 <.plt>

08048330 <puts@plt>:
 8048330:	ff 25 10 a0 04 08    	jmp    *0x804a010
 8048336:	68 08 00 00 00       	push   $0x8
 804833b:	e9 d0 ff ff ff       	jmp    8048310 <.plt>

08048340 <strlen@plt>:
 8048340:	ff 25 14 a0 04 08    	jmp    *0x804a014
 8048346:	68 10 00 00 00       	push   $0x10
 804834b:	e9 c0 ff ff ff       	jmp    8048310 <.plt>

08048350 <__libc_start_main@plt>:
 8048350:	ff 25 18 a0 04 08    	jmp    *0x804a018
 8048356:	68 18 00 00 00       	push   $0x18
 804835b:	e9 b0 ff ff ff       	jmp    8048310 <.plt>

Disassembly of section .plt.got:

08048360 <__gmon_start__@plt>:
 8048360:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 8048366:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

08048370 <_start>:
 8048370:	31 ed                	xor    %ebp,%ebp
 8048372:	5e                   	pop    %esi
 8048373:	89 e1                	mov    %esp,%ecx
 8048375:	83 e4 f0             	and    $0xfffffff0,%esp
 8048378:	50                   	push   %eax
 8048379:	54                   	push   %esp
 804837a:	52                   	push   %edx
 804837b:	e8 23 00 00 00       	call   80483a3 <_start+0x33>
 8048380:	81 c3 80 1c 00 00    	add    $0x1c80,%ebx
 8048386:	8d 83 30 e6 ff ff    	lea    -0x19d0(%ebx),%eax
 804838c:	50                   	push   %eax
 804838d:	8d 83 d0 e5 ff ff    	lea    -0x1a30(%ebx),%eax
 8048393:	50                   	push   %eax
 8048394:	51                   	push   %ecx
 8048395:	56                   	push   %esi
 8048396:	c7 c0 86 84 04 08    	mov    $0x8048486,%eax
 804839c:	50                   	push   %eax
 804839d:	e8 ae ff ff ff       	call   8048350 <__libc_start_main@plt>
 80483a2:	f4                   	hlt    
 80483a3:	8b 1c 24             	mov    (%esp),%ebx
 80483a6:	c3                   	ret    
 80483a7:	66 90                	xchg   %ax,%ax
 80483a9:	66 90                	xchg   %ax,%ax
 80483ab:	66 90                	xchg   %ax,%ax
 80483ad:	66 90                	xchg   %ax,%ax
 80483af:	90                   	nop

080483b0 <_dl_relocate_static_pie>:
 80483b0:	f3 c3                	repz ret 
 80483b2:	66 90                	xchg   %ax,%ax
 80483b4:	66 90                	xchg   %ax,%ax
 80483b6:	66 90                	xchg   %ax,%ax
 80483b8:	66 90                	xchg   %ax,%ax
 80483ba:	66 90                	xchg   %ax,%ax
 80483bc:	66 90                	xchg   %ax,%ax
 80483be:	66 90                	xchg   %ax,%ax

080483c0 <__x86.get_pc_thunk.bx>:
 80483c0:	8b 1c 24             	mov    (%esp),%ebx
 80483c3:	c3                   	ret    
 80483c4:	66 90                	xchg   %ax,%ax
 80483c6:	66 90                	xchg   %ax,%ax
 80483c8:	66 90                	xchg   %ax,%ax
 80483ca:	66 90                	xchg   %ax,%ax
 80483cc:	66 90                	xchg   %ax,%ax
 80483ce:	66 90                	xchg   %ax,%ax

080483d0 <deregister_tm_clones>:
 80483d0:	b8 2c a0 04 08       	mov    $0x804a02c,%eax
 80483d5:	3d 2c a0 04 08       	cmp    $0x804a02c,%eax
 80483da:	74 24                	je     8048400 <deregister_tm_clones+0x30>
 80483dc:	b8 00 00 00 00       	mov    $0x0,%eax
 80483e1:	85 c0                	test   %eax,%eax
 80483e3:	74 1b                	je     8048400 <deregister_tm_clones+0x30>
 80483e5:	55                   	push   %ebp
 80483e6:	89 e5                	mov    %esp,%ebp
 80483e8:	83 ec 14             	sub    $0x14,%esp
 80483eb:	68 2c a0 04 08       	push   $0x804a02c
 80483f0:	ff d0                	call   *%eax
 80483f2:	83 c4 10             	add    $0x10,%esp
 80483f5:	c9                   	leave  
 80483f6:	c3                   	ret    
 80483f7:	89 f6                	mov    %esi,%esi
 80483f9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 8048400:	f3 c3                	repz ret 
 8048402:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 8048409:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048410 <register_tm_clones>:
 8048410:	b8 2c a0 04 08       	mov    $0x804a02c,%eax
 8048415:	2d 2c a0 04 08       	sub    $0x804a02c,%eax
 804841a:	c1 f8 02             	sar    $0x2,%eax
 804841d:	89 c2                	mov    %eax,%edx
 804841f:	c1 ea 1f             	shr    $0x1f,%edx
 8048422:	01 d0                	add    %edx,%eax
 8048424:	d1 f8                	sar    %eax
 8048426:	74 20                	je     8048448 <register_tm_clones+0x38>
 8048428:	ba 00 00 00 00       	mov    $0x0,%edx
 804842d:	85 d2                	test   %edx,%edx
 804842f:	74 17                	je     8048448 <register_tm_clones+0x38>
 8048431:	55                   	push   %ebp
 8048432:	89 e5                	mov    %esp,%ebp
 8048434:	83 ec 10             	sub    $0x10,%esp
 8048437:	50                   	push   %eax
 8048438:	68 2c a0 04 08       	push   $0x804a02c
 804843d:	ff d2                	call   *%edx
 804843f:	83 c4 10             	add    $0x10,%esp
 8048442:	c9                   	leave  
 8048443:	c3                   	ret    
 8048444:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048448:	f3 c3                	repz ret 
 804844a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

08048450 <__do_global_dtors_aux>:
 8048450:	80 3d 2c a0 04 08 00 	cmpb   $0x0,0x804a02c
 8048457:	75 17                	jne    8048470 <__do_global_dtors_aux+0x20>
 8048459:	55                   	push   %ebp
 804845a:	89 e5                	mov    %esp,%ebp
 804845c:	83 ec 08             	sub    $0x8,%esp
 804845f:	e8 6c ff ff ff       	call   80483d0 <deregister_tm_clones>
 8048464:	c6 05 2c a0 04 08 01 	movb   $0x1,0x804a02c
 804846b:	c9                   	leave  
 804846c:	c3                   	ret    
 804846d:	8d 76 00             	lea    0x0(%esi),%esi
 8048470:	f3 c3                	repz ret 
 8048472:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 8048479:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048480 <frame_dummy>:
 8048480:	55                   	push   %ebp
 8048481:	89 e5                	mov    %esp,%ebp
 8048483:	5d                   	pop    %ebp
 8048484:	eb 8a                	jmp    8048410 <register_tm_clones>

08048486 <main>:
 8048486:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 804848a:	83 e4 f0             	and    $0xfffffff0,%esp
 804848d:	ff 71 fc             	pushl  -0x4(%ecx)
 8048490:	55                   	push   %ebp
 8048491:	89 e5                	mov    %esp,%ebp
 8048493:	51                   	push   %ecx
 8048494:	83 ec 04             	sub    $0x4,%esp
 8048497:	a1 28 a0 04 08       	mov    0x804a028,%eax
 804849c:	85 c0                	test   %eax,%eax
 804849e:	74 09                	je     80484a9 <main+0x23>
 80484a0:	a1 28 a0 04 08       	mov    0x804a028,%eax
 80484a5:	ff d0                	call   *%eax
 80484a7:	eb 10                	jmp    80484b9 <main+0x33>
 80484a9:	83 ec 0c             	sub    $0xc,%esp
 80484ac:	68 28 87 04 08       	push   $0x8048728
 80484b1:	e8 7a fe ff ff       	call   8048330 <puts@plt>
 80484b6:	83 c4 10             	add    $0x10,%esp
 80484b9:	b8 00 00 00 00       	mov    $0x0,%eax
 80484be:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 80484c1:	c9                   	leave  
 80484c2:	8d 61 fc             	lea    -0x4(%ecx),%esp
 80484c5:	c3                   	ret    

080484c6 <VilkAwbaqQ>:
 80484c6:	55                   	push   %ebp
 80484c7:	89 e5                	mov    %esp,%ebp
 80484c9:	83 ec 48             	sub    $0x48,%esp
 80484cc:	c7 45 c4 20 5a 72 57 	movl   $0x57725a20,-0x3c(%ebp)
 80484d3:	c7 45 c8 4b 4c 44 67 	movl   $0x67444c4b,-0x38(%ebp)
 80484da:	c7 45 cc 30 33 71 43 	movl   $0x43713330,-0x34(%ebp)
 80484e1:	c7 45 d0 30 6f 32 44 	movl   $0x44326f30,-0x30(%ebp)
 80484e8:	c7 45 d4 65 56 62 53 	movl   $0x53625665,-0x2c(%ebp)
 80484ef:	c7 45 d8 70 51 51 34 	movl   $0x34515170,-0x28(%ebp)
 80484f6:	c7 45 dc 79 65 52 4f 	movl   $0x4f526579,-0x24(%ebp)
 80484fd:	c7 45 e0 61 55 77 35 	movl   $0x35775561,-0x20(%ebp)
 8048504:	c7 45 e4 42 77 6e 59 	movl   $0x596e7742,-0x1c(%ebp)
 804850b:	c7 45 e8 62 37 36 79 	movl   $0x79363762,-0x18(%ebp)
 8048512:	c7 45 ec 6c 48 6f 5a 	movl   $0x5a6f486c,-0x14(%ebp)
 8048519:	c7 45 f0 59 59 74 00 	movl   $0x745959,-0x10(%ebp)
 8048520:	83 ec 0c             	sub    $0xc,%esp
 8048523:	8d 45 c4             	lea    -0x3c(%ebp),%eax
 8048526:	50                   	push   %eax
 8048527:	e8 14 fe ff ff       	call   8048340 <strlen@plt>
 804852c:	83 c4 10             	add    $0x10,%esp
 804852f:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048532:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
 8048536:	78 15                	js     804854d <VilkAwbaqQ+0x87>
 8048538:	8b 45 08             	mov    0x8(%ebp),%eax
 804853b:	3b 45 f4             	cmp    -0xc(%ebp),%eax
 804853e:	7d 0d                	jge    804854d <VilkAwbaqQ+0x87>
 8048540:	8d 55 c4             	lea    -0x3c(%ebp),%edx
 8048543:	8b 45 08             	mov    0x8(%ebp),%eax
 8048546:	01 d0                	add    %edx,%eax
 8048548:	0f b6 00             	movzbl (%eax),%eax
 804854b:	eb 05                	jmp    8048552 <VilkAwbaqQ+0x8c>
 804854d:	b8 00 00 00 00       	mov    $0x0,%eax
 8048552:	c9                   	leave  
 8048553:	c3                   	ret    

08048554 <DjYmrFYH>:
 8048554:	55                   	push   %ebp
 8048555:	89 e5                	mov    %esp,%ebp
 8048557:	83 ec 08             	sub    $0x8,%esp
 804855a:	83 ec 08             	sub    $0x8,%esp
 804855d:	68 9e 87 04 08       	push   $0x804879e
 8048562:	ff 75 08             	pushl  0x8(%ebp)
 8048565:	e8 b6 fd ff ff       	call   8048320 <strcmp@plt>
 804856a:	83 c4 10             	add    $0x10,%esp
 804856d:	85 c0                	test   %eax,%eax
 804856f:	75 10                	jne    8048581 <DjYmrFYH+0x2d>
 8048571:	83 ec 0c             	sub    $0xc,%esp
 8048574:	ff 75 0c             	pushl  0xc(%ebp)
 8048577:	e8 b4 fd ff ff       	call   8048330 <puts@plt>
 804857c:	83 c4 10             	add    $0x10,%esp
 804857f:	eb 01                	jmp    8048582 <DjYmrFYH+0x2e>
 8048581:	90                   	nop
 8048582:	c9                   	leave  
 8048583:	c3                   	ret    

08048584 <do_phase>:
 8048584:	55                   	push   %ebp
 8048585:	89 e5                	mov    %esp,%ebp
 8048587:	90                   	nop
 8048588:	90                   	nop
 8048589:	90                   	nop
 804858a:	90                   	nop
 804858b:	90                   	nop
 804858c:	90                   	nop
 804858d:	90                   	nop
 804858e:	90                   	nop
 804858f:	90                   	nop
 8048590:	90                   	nop
 8048591:	90                   	nop
 8048592:	90                   	nop
 8048593:	90                   	nop
 8048594:	90                   	nop
 8048595:	90                   	nop
 8048596:	90                   	nop
 8048597:	90                   	nop
 8048598:	90                   	nop
 8048599:	90                   	nop
 804859a:	90                   	nop
 804859b:	90                   	nop
 804859c:	90                   	nop
 804859d:	90                   	nop
 804859e:	90                   	nop
 804859f:	90                   	nop
 80485a0:	90                   	nop
 80485a1:	90                   	nop
 80485a2:	90                   	nop
 80485a3:	90                   	nop
 80485a4:	90                   	nop
 80485a5:	90                   	nop
 80485a6:	90                   	nop
 80485a7:	90                   	nop
 80485a8:	90                   	nop
 80485a9:	90                   	nop
 80485aa:	90                   	nop
 80485ab:	90                   	nop
 80485ac:	90                   	nop
 80485ad:	90                   	nop
 80485ae:	90                   	nop
 80485af:	90                   	nop
 80485b0:	90                   	nop
 80485b1:	90                   	nop
 80485b2:	90                   	nop
 80485b3:	90                   	nop
 80485b4:	90                   	nop
 80485b5:	90                   	nop
 80485b6:	90                   	nop
 80485b7:	90                   	nop
 80485b8:	90                   	nop
 80485b9:	90                   	nop
 80485ba:	90                   	nop
 80485bb:	90                   	nop
 80485bc:	90                   	nop
 80485bd:	90                   	nop
 80485be:	90                   	nop
 80485bf:	90                   	nop
 80485c0:	90                   	nop
 80485c1:	90                   	nop
 80485c2:	90                   	nop
 80485c3:	90                   	nop
 80485c4:	90                   	nop
 80485c5:	90                   	nop
 80485c6:	90                   	nop
 80485c7:	90                   	nop
 80485c8:	5d                   	pop    %ebp
 80485c9:	c3                   	ret    
 80485ca:	66 90                	xchg   %ax,%ax
 80485cc:	66 90                	xchg   %ax,%ax
 80485ce:	66 90                	xchg   %ax,%ax

080485d0 <__libc_csu_init>:
 80485d0:	55                   	push   %ebp
 80485d1:	57                   	push   %edi
 80485d2:	56                   	push   %esi
 80485d3:	53                   	push   %ebx
 80485d4:	e8 e7 fd ff ff       	call   80483c0 <__x86.get_pc_thunk.bx>
 80485d9:	81 c3 27 1a 00 00    	add    $0x1a27,%ebx
 80485df:	83 ec 0c             	sub    $0xc,%esp
 80485e2:	8b 6c 24 28          	mov    0x28(%esp),%ebp
 80485e6:	8d b3 10 ff ff ff    	lea    -0xf0(%ebx),%esi
 80485ec:	e8 fb fc ff ff       	call   80482ec <_init>
 80485f1:	8d 83 0c ff ff ff    	lea    -0xf4(%ebx),%eax
 80485f7:	29 c6                	sub    %eax,%esi
 80485f9:	c1 fe 02             	sar    $0x2,%esi
 80485fc:	85 f6                	test   %esi,%esi
 80485fe:	74 25                	je     8048625 <__libc_csu_init+0x55>
 8048600:	31 ff                	xor    %edi,%edi
 8048602:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048608:	83 ec 04             	sub    $0x4,%esp
 804860b:	55                   	push   %ebp
 804860c:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048610:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048614:	ff 94 bb 0c ff ff ff 	call   *-0xf4(%ebx,%edi,4)
 804861b:	83 c7 01             	add    $0x1,%edi
 804861e:	83 c4 10             	add    $0x10,%esp
 8048621:	39 fe                	cmp    %edi,%esi
 8048623:	75 e3                	jne    8048608 <__libc_csu_init+0x38>
 8048625:	83 c4 0c             	add    $0xc,%esp
 8048628:	5b                   	pop    %ebx
 8048629:	5e                   	pop    %esi
 804862a:	5f                   	pop    %edi
 804862b:	5d                   	pop    %ebp
 804862c:	c3                   	ret    
 804862d:	8d 76 00             	lea    0x0(%esi),%esi

08048630 <__libc_csu_fini>:
 8048630:	f3 c3                	repz ret 

Disassembly of section .fini:

08048634 <_fini>:
 8048634:	53                   	push   %ebx
 8048635:	83 ec 08             	sub    $0x8,%esp
 8048638:	e8 83 fd ff ff       	call   80483c0 <__x86.get_pc_thunk.bx>
 804863d:	81 c3 c3 19 00 00    	add    $0x19c3,%ebx
 8048643:	83 c4 08             	add    $0x8,%esp
 8048646:	5b                   	pop    %ebx
 8048647:	c3                   	ret    
