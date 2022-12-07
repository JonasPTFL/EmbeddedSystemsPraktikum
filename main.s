	.file	"main.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_a2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.globl	setup_led
	.type	setup_led, @function
setup_led:
.LFB0:
	.file 1 "src/led_control.h"
	.loc 1 11 34
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 12 47
	li	a5,268509184
	addi	a5,a5,56
	lw	a3,0(a5)
	.loc 1 12 64
	lw	a5,-20(s0)
	li	a4,1
	sll	a5,a4,a5
	.loc 1 12 50
	not	a4,a5
	.loc 1 12 47
	li	a5,268509184
	addi	a5,a5,56
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 13 46
	li	a5,268509184
	addi	a5,a5,4
	lw	a3,0(a5)
	.loc 1 13 63
	lw	a5,-20(s0)
	li	a4,1
	sll	a5,a4,a5
	.loc 1 13 49
	not	a4,a5
	.loc 1 13 46
	li	a5,268509184
	addi	a5,a5,4
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 14 46
	li	a5,268509184
	addi	a5,a5,8
	lw	a3,0(a5)
	.loc 1 14 62
	lw	a5,-20(s0)
	li	a4,1
	sll	a4,a4,a5
	.loc 1 14 46
	li	a5,268509184
	addi	a5,a5,8
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 15 46
	li	a5,268509184
	addi	a5,a5,12
	lw	a3,0(a5)
	.loc 1 15 62
	lw	a5,-20(s0)
	li	a4,1
	sll	a4,a4,a5
	.loc 1 15 46
	li	a5,268509184
	addi	a5,a5,12
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 16 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE0:
	.size	setup_led, .-setup_led
	.globl	song
	.data
	.align	2
	.type	song, @object
	.size	song, 192
song:
	.word	392
	.word	330
	.word	349
	.word	392
	.word	440
	.word	392
	.word	440
	.word	392
	.word	349
	.word	294
	.word	392
	.word	330
	.word	294
	.word	294
	.word	330
	.word	262
	.word	330
	.word	294
	.word	349
	.word	349
	.word	392
	.word	294
	.word	349
	.word	330
	.word	294
	.word	294
	.word	330
	.word	370
	.word	392
	.word	294
	.word	330
	.word	440
	.word	392
	.word	370
	.word	440
	.word	392
	.word	392
	.word	330
	.word	349
	.word	392
	.word	440
	.word	392
	.word	440
	.word	392
	.word	349
	.word	294
	.word	392
	.word	330
	.globl	duration
	.align	2
	.type	duration, @object
	.size	duration, 192
duration:
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1056964608
	.word	1056964608
	.word	1056964608
	.word	1056964608
	.word	1073741824
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1073741824
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1073741824
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1073741824
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1065353216
	.word	1073741824
	.word	1073741824
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1056964608
	.word	1056964608
	.word	1056964608
	.word	1056964608
	.word	1073741824
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1073741824
	.globl	note_index
	.section	.sbss,"aw",@nobits
	.align	2
	.type	note_index, @object
	.size	note_index, 4
note_index:
	.zero	4
	.text
	.align	1
	.globl	delay
	.type	delay, @function
delay:
.LFB1:
	.file 2 "src/main.c"
	.loc 2 17 34
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 2 18 30
	li	a4,33603584
	addi	a4,a4,-8
	sw	a4,-20(s0)
	.loc 2 19 30
	lw	a4,-20(s0)
	lw	a3,0(a4)
	lw	a4,4(a4)
	.loc 2 19 37
	lw	a0,-36(s0)
	mv	a1,a0
	li	a2,0
	.loc 2 19 59
	srli	a0,a1,27
	slli	a6,a2,5
	or	a6,a0,a6
	slli	a5,a1,5
	.loc 2 19 35
	add	a1,a3,a5
	mv	a0,a1
	sltu	a0,a0,a3
	add	a2,a4,a6
	add	a5,a0,a2
	mv	a2,a5
	mv	a5,a1
	mv	a6,a2
	.loc 2 19 23
	sw	a5,-32(s0)
	sw	a6,-28(s0)
	.loc 2 20 11
	nop
.L3:
	.loc 2 20 13 discriminator 1
	lw	a5,-20(s0)
	lw	a6,4(a5)
	lw	a5,0(a5)
	.loc 2 20 19 discriminator 1
	lw	a3,-32(s0)
	lw	a4,-28(s0)
	.loc 2 20 11 discriminator 1
	mv	a1,a4
	mv	a2,a6
	bgtu	a1,a2,.L3
	mv	a1,a4
	mv	a2,a6
	bne	a1,a2,.L5
	mv	a4,a3
	bgtu	a4,a5,.L3
.L5:
	.loc 2 23 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE1:
	.size	delay, .-delay
	.align	1
	.type	setup, @function
setup:
.LFB2:
	.loc 2 26 17
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 27 5
	call	setup_buzzer
	.loc 2 28 1
	nop
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE2:
	.size	setup, .-setup
	.align	1
	.type	loop, @function
loop:
.LFB3:
	.loc 2 31 16
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	ra,28(sp)
	sw	s0,24(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
.LBB2:
	.loc 2 32 17
	sw	zero,-20(s0)
	.loc 2 32 5
	j	.L8
.L9:
.LBB3:
	.loc 2 34 33 discriminator 3
	lui	a5,%hi(note_index)
	lw	a5,%lo(note_index)(a5)
	lui	a4,%hi(song)
	addi	a4,a4,%lo(song)
	slli	a5,a5,2
	add	a5,a4,a5
	lw	a5,0(a5)
	.loc 2 34 12 discriminator 3
	sw	a5,-24(s0)
	.loc 2 35 35 discriminator 3
	lui	a5,%hi(note_index)
	lw	a5,%lo(note_index)(a5)
	.loc 2 35 11 discriminator 3
	lui	a4,%hi(duration)
	addi	a4,a4,%lo(duration)
	slli	a5,a5,2
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-28(s0)
	.loc 2 37 5 discriminator 3
	lw	a1,-28(s0)
	lw	a0,-24(s0)
	call	play_tone
	.loc 2 39 20 discriminator 3
	lui	a5,%hi(note_index)
	lw	a4,-20(s0)
	sw	a4,%lo(note_index)(a5)
.LBE3:
	.loc 2 32 59 discriminator 3
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L8:
	.loc 2 32 5 discriminator 1
	lw	a4,-20(s0)
	li	a5,47
	bleu	a4,a5,.L9
.LBE2:
	.loc 2 43 1
	nop
	lw	ra,28(sp)
	.cfi_restore 1
	lw	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE3:
	.size	loop, .-loop
	.align	1
	.type	setup_buzzer, @function
setup_buzzer:
.LFB4:
	.loc 2 45 20
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,12(sp)
	.cfi_offset 8, -4
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 46 47
	li	a5,268509184
	addi	a5,a5,56
	lw	a3,0(a5)
	li	a5,268509184
	addi	a5,a5,56
	li	a4,-4096
	addi	a4,a4,2047
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 2 47 46
	li	a5,268509184
	addi	a5,a5,4
	lw	a3,0(a5)
	li	a5,268509184
	addi	a5,a5,4
	li	a4,-4096
	addi	a4,a4,2047
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 2 48 46
	li	a5,268509184
	addi	a5,a5,8
	lw	a3,0(a5)
	li	a5,268509184
	addi	a5,a5,8
	li	a4,4096
	addi	a4,a4,-2048
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 2 49 46
	li	a5,268509184
	addi	a5,a5,12
	lw	a3,0(a5)
	li	a5,268509184
	addi	a5,a5,12
	li	a4,4096
	addi	a4,a4,-2048
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 2 50 1
	nop
	lw	s0,12(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE4:
	.size	setup_buzzer, .-setup_buzzer
	.globl	__floatunsisf
	.globl	__gtsf2
	.align	1
	.globl	play_tone
	.type	play_tone, @function
play_tone:
.LFB5:
	.loc 2 52 59
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	ra,44(sp)
	sw	s0,40(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	sw	a1,-40(s0)
.LBB4:
	.loc 2 53 17
	sw	zero,-20(s0)
	.loc 2 53 5
	j	.L12
.L15:
.LBB5:
	.loc 2 55 21
	sw	zero,-24(s0)
	.loc 2 55 9
	j	.L13
.L14:
	.loc 2 57 57 discriminator 3
	li	a5,268509184
	addi	a5,a5,12
	lw	a3,0(a5)
	li	a5,268509184
	addi	a5,a5,12
	li	a4,4096
	addi	a4,a4,-2048
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 2 58 27 discriminator 3
	li	a4,500
	lw	a5,-36(s0)
	divu	a5,a4,a5
	.loc 2 58 13 discriminator 3
	mv	a0,a5
	call	delay
	.loc 2 59 57 discriminator 3
	li	a5,268509184
	addi	a5,a5,12
	lw	a3,0(a5)
	li	a5,268509184
	addi	a5,a5,12
	li	a4,-4096
	addi	a4,a4,2047
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 2 60 27 discriminator 3
	li	a4,500
	lw	a5,-36(s0)
	divu	a5,a4,a5
	.loc 2 60 13 discriminator 3
	mv	a0,a5
	call	delay
	.loc 2 55 49 discriminator 3
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L13:
	.loc 2 55 9 discriminator 1
	lw	a4,-24(s0)
	lw	a5,-36(s0)
	bltu	a4,a5,.L14
.LBE5:
	.loc 2 62 9 discriminator 2
	li	a0,1
	call	delay
	.loc 2 53 44 discriminator 2
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L12:
	.loc 2 53 26 discriminator 1
	lw	a0,-20(s0)
	call	__floatunsisf
.LVL0:
	mv	a5,a0
	.loc 2 53 5 discriminator 1
	mv	a1,a5
	lw	a0,-40(s0)
	call	__gtsf2
.LVL1:
	mv	a5,a0
	bgt	a5,zero,.L15
.LBE4:
	.loc 2 64 1
	nop
	lw	ra,44(sp)
	.cfi_restore 1
	lw	s0,40(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE5:
	.size	play_tone, .-play_tone
	.align	1
	.globl	main
	.type	main, @function
main:
.LFB6:
	.loc 2 67 15
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 2 69 5
	call	setup
.L17:
	.loc 2 72 9 discriminator 1
	call	loop
	j	.L17
	.cfi_endproc
.LFE6:
	.size	main, .-main
.Letext0:
	.file 3 "src/types.h"
	.file 4 "src/song.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x228
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.byte	0x1
	.4byte	.LASF19
	.byte	0xc
	.4byte	.LASF20
	.4byte	.LASF21
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.byte	0x2
	.4byte	.LASF0
	.byte	0x3
	.byte	0xc
	.byte	0x16
	.4byte	0x31
	.byte	0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF2
	.byte	0x2
	.4byte	.LASF1
	.byte	0x3
	.byte	0xd
	.byte	0x17
	.4byte	0x44
	.byte	0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.byte	0x2
	.4byte	.LASF4
	.byte	0x3
	.byte	0xe
	.byte	0x1c
	.4byte	0x61
	.byte	0x4
	.4byte	0x4b
	.byte	0x5
	.4byte	0x57
	.byte	0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF5
	.byte	0x6
	.4byte	0x78
	.4byte	0x78
	.byte	0x7
	.4byte	0x31
	.byte	0x2f
	.byte	0
	.byte	0x8
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x9
	.4byte	.LASF7
	.byte	0x4
	.byte	0x15
	.byte	0x5
	.4byte	0x68
	.byte	0x5
	.byte	0x3
	.4byte	song
	.byte	0x6
	.4byte	0xa1
	.4byte	0xa1
	.byte	0x7
	.4byte	0x31
	.byte	0x2f
	.byte	0
	.byte	0x3
	.byte	0x4
	.byte	0x4
	.4byte	.LASF6
	.byte	0x9
	.4byte	.LASF8
	.byte	0x4
	.byte	0x1c
	.byte	0x7
	.4byte	0x91
	.byte	0x5
	.byte	0x3
	.4byte	duration
	.byte	0x9
	.4byte	.LASF9
	.byte	0x2
	.byte	0xe
	.byte	0x8
	.4byte	0x25
	.byte	0x5
	.byte	0x3
	.4byte	note_index
	.byte	0xa
	.4byte	.LASF22
	.byte	0x2
	.byte	0x43
	.byte	0x5
	.4byte	0x78
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.byte	0x1
	.byte	0x9c
	.byte	0xb
	.4byte	.LASF14
	.byte	0x2
	.byte	0x34
	.byte	0x6
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.byte	0x1
	.byte	0x9c
	.4byte	0x145
	.byte	0xc
	.4byte	.LASF10
	.byte	0x2
	.byte	0x34
	.byte	0x17
	.4byte	0x25
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xc
	.4byte	.LASF11
	.byte	0x2
	.byte	0x34
	.byte	0x2d
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.byte	0x58
	.byte	0xd
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.byte	0xe
	.string	"i"
	.byte	0x2
	.byte	0x35
	.byte	0x11
	.4byte	0x25
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0xd
	.4byte	.LBB5
	.4byte	.LBE5-.LBB5
	.byte	0xe
	.string	"j"
	.byte	0x2
	.byte	0x37
	.byte	0x15
	.4byte	0x25
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0
	.byte	0
	.byte	0xf
	.4byte	.LASF12
	.byte	0x2
	.byte	0x2d
	.byte	0x6
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x1
	.byte	0x9c
	.byte	0x10
	.4byte	.LASF23
	.byte	0x2
	.byte	0x1f
	.byte	0x6
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x1
	.byte	0x9c
	.4byte	0x1ad
	.byte	0xd
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.byte	0xe
	.string	"i"
	.byte	0x2
	.byte	0x20
	.byte	0x11
	.4byte	0x25
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0xd
	.4byte	.LBB3
	.4byte	.LBE3-.LBB3
	.byte	0x11
	.4byte	.LASF10
	.byte	0x2
	.byte	0x22
	.byte	0xc
	.4byte	0x25
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0x11
	.4byte	.LASF11
	.byte	0x2
	.byte	0x23
	.byte	0xb
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.byte	0x64
	.byte	0
	.byte	0
	.byte	0
	.byte	0x12
	.4byte	.LASF13
	.byte	0x2
	.byte	0x1a
	.byte	0x6
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x1
	.byte	0x9c
	.byte	0x13
	.4byte	.LASF15
	.byte	0x2
	.byte	0x11
	.byte	0x6
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x1
	.byte	0x9c
	.4byte	0x203
	.byte	0xc
	.4byte	.LASF16
	.byte	0x2
	.byte	0x11
	.byte	0x15
	.4byte	0x38
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xe
	.string	"now"
	.byte	0x2
	.byte	0x12
	.byte	0x1e
	.4byte	0x203
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0x11
	.4byte	.LASF17
	.byte	0x2
	.byte	0x13
	.byte	0x17
	.4byte	0x57
	.byte	0x2
	.byte	0x91
	.byte	0x60
	.byte	0
	.byte	0x14
	.byte	0x4
	.4byte	0x5c
	.byte	0x15
	.4byte	.LASF24
	.byte	0x1
	.byte	0xb
	.byte	0x6
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.byte	0xc
	.4byte	.LASF18
	.byte	0x1
	.byte	0xb
	.byte	0x19
	.4byte	0x38
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0x1b
	.byte	0xe
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x10
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x35
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x26
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0x19
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xd
	.byte	0xb
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0xe
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xf
	.byte	0x2e
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x11
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x12
	.byte	0x2e
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x13
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x14
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x15
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF17:
	.string	"then"
.LASF2:
	.string	"unsigned int"
.LASF12:
	.string	"setup_buzzer"
.LASF1:
	.string	"uint32_t"
.LASF14:
	.string	"play_tone"
.LASF24:
	.string	"setup_led"
.LASF13:
	.string	"setup"
.LASF3:
	.string	"long unsigned int"
.LASF5:
	.string	"long long unsigned int"
.LASF20:
	.string	"src/main.c"
.LASF4:
	.string	"uint64_t"
.LASF9:
	.string	"note_index"
.LASF0:
	.string	"uint_t"
.LASF7:
	.string	"song"
.LASF22:
	.string	"main"
.LASF10:
	.string	"tone_frequency"
.LASF21:
	.string	"/home/jp/EmbeddedSystems"
.LASF19:
	.string	"GNU C17 8.3.0 -march=rv32imac -mabi=ilp32 -mcmodel=medlow -g -Os -O0 -fno-builtin-printf"
.LASF11:
	.string	"tone_duration"
.LASF18:
	.string	"gpio_pin"
.LASF8:
	.string	"duration"
.LASF16:
	.string	"milliseconds"
.LASF6:
	.string	"float"
.LASF23:
	.string	"loop"
.LASF15:
	.string	"delay"
	.ident	"GCC: (SiFive GCC 8.3.0-2019.08.0) 8.3.0"
