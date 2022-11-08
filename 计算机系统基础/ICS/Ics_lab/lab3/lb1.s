
lb1:     file format elf32-i386


Disassembly of section .init:

080482a8 <_init>:
 80482a8:	53                   	push   %ebx
 80482a9:	83 ec 08             	sub    $0x8,%esp
 80482ac:	e8 af 00 00 00       	call   8048360 <__x86.get_pc_thunk.bx>
 80482b1:	81 c3 4f 1d 00 00    	add    $0x1d4f,%ebx
 80482b7:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 80482bd:	85 c0                	test   %eax,%eax
 80482bf:	74 05                	je     80482c6 <_init+0x1e>
 80482c1:	e8 3a 00 00 00       	call   8048300 <__gmon_start__@plt>
 80482c6:	83 c4 08             	add    $0x8,%esp
 80482c9:	5b                   	pop    %ebx
 80482ca:	c3                   	ret    

Disassembly of section .plt:

080482d0 <.plt>:
 80482d0:	ff 35 04 a0 04 08    	pushl  0x804a004
 80482d6:	ff 25 08 a0 04 08    	jmp    *0x804a008
 80482dc:	00 00                	add    %al,(%eax)
	...

080482e0 <puts@plt>:
 80482e0:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 80482e6:	68 00 00 00 00       	push   $0x0
 80482eb:	e9 e0 ff ff ff       	jmp    80482d0 <.plt>

080482f0 <__libc_start_main@plt>:
 80482f0:	ff 25 10 a0 04 08    	jmp    *0x804a010
 80482f6:	68 08 00 00 00       	push   $0x8
 80482fb:	e9 d0 ff ff ff       	jmp    80482d0 <.plt>

Disassembly of section .plt.got:

08048300 <__gmon_start__@plt>:
 8048300:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 8048306:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

08048310 <_start>:
 8048310:	31 ed                	xor    %ebp,%ebp
 8048312:	5e                   	pop    %esi
 8048313:	89 e1                	mov    %esp,%ecx
 8048315:	83 e4 f0             	and    $0xfffffff0,%esp
 8048318:	50                   	push   %eax
 8048319:	54                   	push   %esp
 804831a:	52                   	push   %edx
 804831b:	e8 23 00 00 00       	call   8048343 <_start+0x33>
 8048320:	81 c3 e0 1c 00 00    	add    $0x1ce0,%ebx
 8048326:	8d 83 e0 e4 ff ff    	lea    -0x1b20(%ebx),%eax
 804832c:	50                   	push   %eax
 804832d:	8d 83 80 e4 ff ff    	lea    -0x1b80(%ebx),%eax
 8048333:	50                   	push   %eax
 8048334:	51                   	push   %ecx
 8048335:	56                   	push   %esi
 8048336:	c7 c0 26 84 04 08    	mov    $0x8048426,%eax
 804833c:	50                   	push   %eax
 804833d:	e8 ae ff ff ff       	call   80482f0 <__libc_start_main@plt>
 8048342:	f4                   	hlt    
 8048343:	8b 1c 24             	mov    (%esp),%ebx
 8048346:	c3                   	ret    
 8048347:	66 90                	xchg   %ax,%ax
 8048349:	66 90                	xchg   %ax,%ax
 804834b:	66 90                	xchg   %ax,%ax
 804834d:	66 90                	xchg   %ax,%ax
 804834f:	90                   	nop

08048350 <_dl_relocate_static_pie>:
 8048350:	f3 c3                	repz ret 
 8048352:	66 90                	xchg   %ax,%ax
 8048354:	66 90                	xchg   %ax,%ax
 8048356:	66 90                	xchg   %ax,%ax
 8048358:	66 90                	xchg   %ax,%ax
 804835a:	66 90                	xchg   %ax,%ax
 804835c:	66 90                	xchg   %ax,%ax
 804835e:	66 90                	xchg   %ax,%ax

08048360 <__x86.get_pc_thunk.bx>:
 8048360:	8b 1c 24             	mov    (%esp),%ebx
 8048363:	c3                   	ret    
 8048364:	66 90                	xchg   %ax,%ax
 8048366:	66 90                	xchg   %ax,%ax
 8048368:	66 90                	xchg   %ax,%ax
 804836a:	66 90                	xchg   %ax,%ax
 804836c:	66 90                	xchg   %ax,%ax
 804836e:	66 90                	xchg   %ax,%ax

08048370 <deregister_tm_clones>:
 8048370:	b8 d0 a1 04 08       	mov    $0x804a1d0,%eax
 8048375:	3d d0 a1 04 08       	cmp    $0x804a1d0,%eax
 804837a:	74 24                	je     80483a0 <deregister_tm_clones+0x30>
 804837c:	b8 00 00 00 00       	mov    $0x0,%eax
 8048381:	85 c0                	test   %eax,%eax
 8048383:	74 1b                	je     80483a0 <deregister_tm_clones+0x30>
 8048385:	55                   	push   %ebp
 8048386:	89 e5                	mov    %esp,%ebp
 8048388:	83 ec 14             	sub    $0x14,%esp
 804838b:	68 d0 a1 04 08       	push   $0x804a1d0
 8048390:	ff d0                	call   *%eax
 8048392:	83 c4 10             	add    $0x10,%esp
 8048395:	c9                   	leave  
 8048396:	c3                   	ret    
 8048397:	89 f6                	mov    %esi,%esi
 8048399:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 80483a0:	f3 c3                	repz ret 
 80483a2:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 80483a9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080483b0 <register_tm_clones>:
 80483b0:	b8 d0 a1 04 08       	mov    $0x804a1d0,%eax
 80483b5:	2d d0 a1 04 08       	sub    $0x804a1d0,%eax
 80483ba:	c1 f8 02             	sar    $0x2,%eax
 80483bd:	89 c2                	mov    %eax,%edx
 80483bf:	c1 ea 1f             	shr    $0x1f,%edx
 80483c2:	01 d0                	add    %edx,%eax
 80483c4:	d1 f8                	sar    %eax
 80483c6:	74 20                	je     80483e8 <register_tm_clones+0x38>
 80483c8:	ba 00 00 00 00       	mov    $0x0,%edx
 80483cd:	85 d2                	test   %edx,%edx
 80483cf:	74 17                	je     80483e8 <register_tm_clones+0x38>
 80483d1:	55                   	push   %ebp
 80483d2:	89 e5                	mov    %esp,%ebp
 80483d4:	83 ec 10             	sub    $0x10,%esp
 80483d7:	50                   	push   %eax
 80483d8:	68 d0 a1 04 08       	push   $0x804a1d0
 80483dd:	ff d2                	call   *%edx
 80483df:	83 c4 10             	add    $0x10,%esp
 80483e2:	c9                   	leave  
 80483e3:	c3                   	ret    
 80483e4:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 80483e8:	f3 c3                	repz ret 
 80483ea:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

080483f0 <__do_global_dtors_aux>:
 80483f0:	80 3d d0 a1 04 08 00 	cmpb   $0x0,0x804a1d0
 80483f7:	75 17                	jne    8048410 <__do_global_dtors_aux+0x20>
 80483f9:	55                   	push   %ebp
 80483fa:	89 e5                	mov    %esp,%ebp
 80483fc:	83 ec 08             	sub    $0x8,%esp
 80483ff:	e8 6c ff ff ff       	call   8048370 <deregister_tm_clones>
 8048404:	c6 05 d0 a1 04 08 01 	movb   $0x1,0x804a1d0
 804840b:	c9                   	leave  
 804840c:	c3                   	ret    
 804840d:	8d 76 00             	lea    0x0(%esi),%esi
 8048410:	f3 c3                	repz ret 
 8048412:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 8048419:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048420 <frame_dummy>:
 8048420:	55                   	push   %ebp
 8048421:	89 e5                	mov    %esp,%ebp
 8048423:	5d                   	pop    %ebp
 8048424:	eb 8a                	jmp    80483b0 <register_tm_clones>

08048426 <main>:
 8048426:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 804842a:	83 e4 f0             	and    $0xfffffff0,%esp
 804842d:	ff 71 fc             	pushl  -0x4(%ecx)
 8048430:	55                   	push   %ebp
 8048431:	89 e5                	mov    %esp,%ebp
 8048433:	51                   	push   %ecx
 8048434:	83 ec 04             	sub    $0x4,%esp
 8048437:	a1 cc a1 04 08       	mov    0x804a1cc,%eax
 804843c:	85 c0                	test   %eax,%eax
 804843e:	74 09                	je     8048449 <main+0x23>
 8048440:	a1 cc a1 04 08       	mov    0x804a1cc,%eax
 8048445:	ff d0                	call   *%eax
 8048447:	eb 10                	jmp    8048459 <main+0x33>
 8048449:	83 ec 0c             	sub    $0xc,%esp
 804844c:	68 c8 85 04 08       	push   $0x80485c8
 8048451:	e8 8a fe ff ff       	call   80482e0 <puts@plt>
 8048456:	83 c4 10             	add    $0x10,%esp
 8048459:	b8 00 00 00 00       	mov    $0x0,%eax
 804845e:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 8048461:	c9                   	leave  
 8048462:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048465:	c3                   	ret    

08048466 <do_phase>:
 8048466:	55                   	push   %ebp
 8048467:	89 e5                	mov    %esp,%ebp
 8048469:	83 ec 08             	sub    $0x8,%esp
 804846c:	b8 64 a1 04 08       	mov    $0x804a164,%eax
 8048471:	83 ec 0c             	sub    $0xc,%esp
 8048474:	50                   	push   %eax
 8048475:	e8 66 fe ff ff       	call   80482e0 <puts@plt>
 804847a:	83 c4 10             	add    $0x10,%esp
 804847d:	90                   	nop
 804847e:	c9                   	leave  
 804847f:	c3                   	ret    

08048480 <__libc_csu_init>:
 8048480:	55                   	push   %ebp
 8048481:	57                   	push   %edi
 8048482:	56                   	push   %esi
 8048483:	53                   	push   %ebx
 8048484:	e8 d7 fe ff ff       	call   8048360 <__x86.get_pc_thunk.bx>
 8048489:	81 c3 77 1b 00 00    	add    $0x1b77,%ebx
 804848f:	83 ec 0c             	sub    $0xc,%esp
 8048492:	8b 6c 24 28          	mov    0x28(%esp),%ebp
 8048496:	8d b3 10 ff ff ff    	lea    -0xf0(%ebx),%esi
 804849c:	e8 07 fe ff ff       	call   80482a8 <_init>
 80484a1:	8d 83 0c ff ff ff    	lea    -0xf4(%ebx),%eax
 80484a7:	29 c6                	sub    %eax,%esi
 80484a9:	c1 fe 02             	sar    $0x2,%esi
 80484ac:	85 f6                	test   %esi,%esi
 80484ae:	74 25                	je     80484d5 <__libc_csu_init+0x55>
 80484b0:	31 ff                	xor    %edi,%edi
 80484b2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80484b8:	83 ec 04             	sub    $0x4,%esp
 80484bb:	55                   	push   %ebp
 80484bc:	ff 74 24 2c          	pushl  0x2c(%esp)
 80484c0:	ff 74 24 2c          	pushl  0x2c(%esp)
 80484c4:	ff 94 bb 0c ff ff ff 	call   *-0xf4(%ebx,%edi,4)
 80484cb:	83 c7 01             	add    $0x1,%edi
 80484ce:	83 c4 10             	add    $0x10,%esp
 80484d1:	39 fe                	cmp    %edi,%esi
 80484d3:	75 e3                	jne    80484b8 <__libc_csu_init+0x38>
 80484d5:	83 c4 0c             	add    $0xc,%esp
 80484d8:	5b                   	pop    %ebx
 80484d9:	5e                   	pop    %esi
 80484da:	5f                   	pop    %edi
 80484db:	5d                   	pop    %ebp
 80484dc:	c3                   	ret    
 80484dd:	8d 76 00             	lea    0x0(%esi),%esi

080484e0 <__libc_csu_fini>:
 80484e0:	f3 c3                	repz ret 

Disassembly of section .fini:

080484e4 <_fini>:
 80484e4:	53                   	push   %ebx
 80484e5:	83 ec 08             	sub    $0x8,%esp
 80484e8:	e8 73 fe ff ff       	call   8048360 <__x86.get_pc_thunk.bx>
 80484ed:	81 c3 13 1b 00 00    	add    $0x1b13,%ebx
 80484f3:	83 c4 08             	add    $0x8,%esp
 80484f6:	5b                   	pop    %ebx
 80484f7:	c3                   	ret    
