	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"main.c"
@ GNU C (Debian 4.6.3-8+rpi1) version 4.6.3 (arm-linux-gnueabihf)
@	compiled by GNU C version 4.6.3, GMP version 5.0.5, MPFR version 3.1.0-p10, MPC version 0.9
@ GGC heuristics: --param ggc-min-expand=47 --param ggc-min-heapsize=31880
@ options passed:  -imultilib . -imultiarch arm-linux-gnueabihf main.c
@ -march=armv6 -mfloat-abi=hard -mfpu=vfp -auxbase-strip main.s
@ -fverbose-asm
@ options enabled:  -fauto-inc-dec -fbranch-count-reg -fcommon
@ -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
@ -feliminate-unused-debug-types -ffunction-cse -fgcse-lm -fident
@ -finline-functions-called-once -fira-share-save-slots
@ -fira-share-spill-slots -fivopts -fkeep-static-consts
@ -fleading-underscore -fmath-errno -fmerge-debug-strings
@ -fmove-loop-invariants -fpeephole -fprefetch-loop-arrays
@ -freg-struct-return -fsched-critical-path-heuristic
@ -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
@ -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
@ -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fshow-column
@ -fsigned-zeros -fsplit-ivs-in-unroller -fstrict-volatile-bitfields
@ -ftrapping-math -ftree-cselim -ftree-forwprop -ftree-loop-if-convert
@ -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
@ -ftree-parallelize-loops= -ftree-phiprop -ftree-pta -ftree-reassoc
@ -ftree-scev-cprop -ftree-slp-vectorize -ftree-vect-loop-version
@ -funit-at-a-time -fverbose-asm -fzero-initialized-in-bss -mglibc
@ -mlittle-endian -msched-prolog

@ Compiler executable checksum: 3c5b59c0ef1fec28e05e457a89f35c2f

	.section	.rodata
	.align	2
.LC0:
	.ascii	"Function1: Name\000"
	.align	2
.LC1:
	.ascii	"Function2: ID\000"
	.align	2
.LC2:
	.ascii	"Main Function:\000"
	.align	2
.LC3:
	.ascii	"*****Print All*****\000"
	.align	2
.LC4:
	.ascii	"Team 01\000"
	.align	2
.LC5:
	.ascii	"10027001   Peter Huang\000"
	.align	2
.LC6:
	.ascii	"10027002   Mary Sue\000"
	.align	2
.LC7:
	.ascii	"10027003   Tom Smith\000"
	.align	2
.LC8:
	.ascii	"ID Summation = 30081006\000"
	.align	2
.LC9:
	.ascii	"*****End Print*****\000"
	.align	2
.LC10:
	.ascii	"\012***** Please enter p to draw Julia Set animatio"
	.ascii	"n *****\000"
	.align	2
.LC11:
	.ascii	"clear\000"
	.align	2
.LC12:
	.ascii	"/dev/fb0\000"
	.align	2
.LC13:
	.ascii	"Frame Buffer Device Open Error!!\000"
	.align	2
.LC14:
	.ascii	".*.*.*.<:: Happy New Year ::>.*.*.*.\000"
	.align	2
.LC15:
	.ascii	"by Team 01\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 614424
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}	@,
	add	fp, sp, #4	@,,
	sub	sp, sp, #614400	@,,
	sub	sp, sp, #32	@,,
	ldr	r3, .L9	@ tmp138,
	str	r3, [fp, #-12]	@ tmp138, max_cX
	ldr	r3, .L9+4	@ tmp139,
	str	r3, [fp, #-16]	@ tmp139, min_cY
	mvn	r3, #4	@ tmp140,
	str	r3, [fp, #-20]	@ tmp140, cY_step
	ldr	r3, .L9	@ tmp141,
	str	r3, [fp, #-24]	@ tmp141, cX
	ldr	r0, .L9+8	@,
	bl	puts	@
	bl	name	@
	ldr	r0, .L9+12	@,
	bl	puts	@
	bl	id	@
	ldr	r0, .L9+16	@,
	bl	puts	@
	ldr	r0, .L9+20	@,
	bl	puts	@
	ldr	r0, .L9+24	@,
	bl	puts	@
	ldr	r0, .L9+28	@,
	bl	puts	@
	ldr	r0, .L9+32	@,
	bl	puts	@
	ldr	r0, .L9+36	@,
	bl	puts	@
	ldr	r0, .L9+40	@,
	bl	puts	@
	ldr	r0, .L9+44	@,
	bl	puts	@
	ldr	r0, .L9+48	@,
	bl	puts	@
	mov	r0, r0	@ nop
.L2:
	bl	getchar	@
	mov	r3, r0	@ D.2628,
	cmp	r3, #112	@ D.2628,
	bne	.L2	@,
	ldr	r0, .L9+52	@,
	bl	system	@
	ldr	r0, .L9+56	@,
	ldr	r1, .L9+60	@,
	bl	open	@
	str	r0, [fp, #-28]	@, fd
	ldr	r3, [fp, #-28]	@ tmp142, fd
	cmp	r3, #0	@ tmp142,
	bge	.L3	@,
	ldr	r0, .L9+64	@,
	bl	puts	@
	b	.L8	@
.L3:
	mov	r3, #400	@ tmp143,
	str	r3, [fp, #-8]	@ tmp143, cY
	b	.L5	@
.L6:
	sub	r3, fp, #614400	@ tmp144,,
	sub	r3, r3, #4	@ tmp144, tmp144,
	sub	r3, r3, #24	@ tmp144, tmp144,
	str	r3, [sp, #0]	@ tmp144,
	ldr	r0, [fp, #-24]	@, cX
	ldr	r1, [fp, #-8]	@, cY
	mov	r2, #640	@,
	mov	r3, #480	@,
	bl	drawJuliaSet	@
	sub	r3, fp, #614400	@ tmp145,,
	sub	r3, r3, #4	@ tmp145, tmp145,
	sub	r3, r3, #24	@ tmp145, tmp145,
	ldr	r0, [fp, #-28]	@, fd
	mov	r1, r3	@, tmp145
	mov	r2, #614400	@,
	bl	write	@
	ldr	r0, [fp, #-28]	@, fd
	mov	r1, #0	@,
	mov	r2, #0	@,
	bl	lseek	@
	ldr	r2, [fp, #-8]	@ tmp146, cY
	ldr	r3, [fp, #-20]	@ tmp147, cY_step
	add	r3, r2, r3	@ tmp148, tmp146, tmp147
	str	r3, [fp, #-8]	@ tmp148, cY
.L5:
	ldr	r2, [fp, #-8]	@ tmp149, cY
	ldr	r3, [fp, #-16]	@ tmp150, min_cY
	cmp	r2, r3	@ tmp149, tmp150
	bge	.L6	@,
	ldr	r0, .L9+68	@,
	bl	puts	@
	ldr	r0, .L9+72	@,
	bl	puts	@
	ldr	r0, .L9+28	@,
	bl	puts	@
	ldr	r0, .L9+32	@,
	bl	puts	@
	ldr	r0, .L9+36	@,
	bl	puts	@
	ldr	r0, [fp, #-28]	@, fd
	bl	close	@
.L8:
	mov	r0, r0	@ nop
.L7:
	bl	getchar	@
	mov	r3, r0	@ D.2632,
	cmp	r3, #112	@ D.2632,
	bne	.L7	@,
	mov	r3, #0	@ D.2633,
	mov	r0, r3	@, <retval>
	sub	sp, fp, #4	@,,
	ldmfd	sp!, {fp, pc}
.L10:
	.align	2
.L9:
	.word	-700
	.word	270
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	1052674
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.size	main, .-main
	.ident	"GCC: (Debian 4.6.3-8+rpi1) 4.6.3"
	.section	.note.GNU-stack,"",%progbits
