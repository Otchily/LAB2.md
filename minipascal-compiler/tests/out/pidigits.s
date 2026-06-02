	.text
	.file	"pidigits"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	movslq	%edi, %rdi
	callq	mp_init_runtime@PLT
	movl	$1, %edi
	callq	mp_argi@PLT
	movq	n@GOTPCREL(%rip), %rcx
	movq	%rax, (%rcx)
	testq	%rax, %rax
	js	.LBB0_1
# %bb.2:                                # %ifend
	cmpq	$10, (%rcx)
	jl	.LBB0_4
.LBB0_3:                                # %then2
	movq	$9, (%rcx)
.LBB0_4:                                # %ifend3
	movq	scale@GOTPCREL(%rip), %r14
	movq	$1, (%r14)
	movq	(%rcx), %rax
	movq	i@GOTPCREL(%rip), %rcx
	movq	$1, (%rcx)
	movq	%rax, (%rsp)
	.p2align	4, 0x90
.LBB0_5:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rcx), %rax
	cmpq	(%rsp), %rax
	jg	.LBB0_7
# %bb.6:                                # %for.body
                                        #   in Loop: Header=BB0_5 Depth=1
	movq	(%r14), %rax
	addq	%rax, %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rax, (%r14)
	incq	(%rcx)
	jmp	.LBB0_5
.LBB0_7:                                # %for.end
	movq	(%r14), %rax
	leaq	(%rax,%rax,2), %rax
	movq	piScaled@GOTPCREL(%rip), %rsi
	movq	%rax, (%rsi)
	movq	sign@GOTPCREL(%rip), %rdi
	movq	$1, (%rdi)
	movq	denom@GOTPCREL(%rip), %r8
	movq	$2, (%r8)
	movq	terms@GOTPCREL(%rip), %rax
	movq	$3000, (%rax)                   # imm = 0xBB8
	movq	$1, (%rcx)
	movq	$3000, 8(%rsp)                  # imm = 0xBB8
	movq	termValue@GOTPCREL(%rip), %r9
	jmp	.LBB0_8
	.p2align	4, 0x90
.LBB0_11:                               # %else
                                        #   in Loop: Header=BB0_8 Depth=1
	movq	(%r9), %rax
	subq	%rax, (%rsi)
.LBB0_12:                               # %ifend23
                                        #   in Loop: Header=BB0_8 Depth=1
	negq	(%rdi)
	addq	$2, (%r8)
	incq	(%rcx)
.LBB0_8:                                # %for.cond8
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rcx), %rax
	cmpq	8(%rsp), %rax
	jg	.LBB0_13
# %bb.9:                                # %for.body9
                                        #   in Loop: Header=BB0_8 Depth=1
	movq	(%r14), %rax
	shlq	$2, %rax
	movq	(%r8), %r10
	leaq	1(%r10), %rdx
	imulq	%r10, %rdx
	addq	$2, %r10
	imulq	%rdx, %r10
	cqto
	idivq	%r10
	movq	%rax, (%r9)
	cmpq	$1, (%rdi)
	jne	.LBB0_11
# %bb.10:                               # %then22
                                        #   in Loop: Header=BB0_8 Depth=1
	movq	(%r9), %rax
	addq	%rax, (%rsi)
	jmp	.LBB0_12
.LBB0_13:                               # %for.end11
	movq	(%rsi), %rax
	cqto
	idivq	(%r14)
	movq	intPart@GOTPCREL(%rip), %rcx
	movq	%rax, (%rcx)
	movq	fracPart@GOTPCREL(%rip), %r15
	movq	%rdx, (%r15)
	movq	%rax, %rdi
	callq	mp_write_int@PLT
	movl	$.L__unnamed_1, %edi
	callq	mp_write_str@PLT
	movabsq	$7378697629483820647, %rbx      # imm = 0x6666666666666667
	movq	%rbx, %rax
	imulq	(%r14)
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	movq	tmp@GOTPCREL(%rip), %r14
	jmp	.LBB0_14
	.p2align	4, 0x90
.LBB0_17:                               # %ifend44
                                        #   in Loop: Header=BB0_14 Depth=1
	movq	%rbx, %rax
	imulq	(%r14)
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
.LBB0_14:                               # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	%rdx, (%r14)
	cmpq	$0, (%r14)
	jle	.LBB0_18
# %bb.15:                               # %while.body
                                        #   in Loop: Header=BB0_14 Depth=1
	movq	(%r15), %rax
	cmpq	(%r14), %rax
	jge	.LBB0_17
# %bb.16:                               # %then43
                                        #   in Loop: Header=BB0_14 Depth=1
	xorl	%edi, %edi
	callq	mp_write_int@PLT
	jmp	.LBB0_17
.LBB0_18:                               # %while.end
	movq	(%r15), %rdi
	callq	mp_write_int@PLT
	callq	mp_writeln@PLT
	xorl	%eax, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.LBB0_1:                                # %then
	.cfi_def_cfa_offset 48
	movq	$0, (%rcx)
	cmpq	$10, (%rcx)
	jge	.LBB0_3
	jmp	.LBB0_4
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	n,@object                       # @n
	.bss
	.globl	n
	.p2align	3, 0x0
n:
	.quad	0                               # 0x0
	.size	n, 8

	.type	i,@object                       # @i
	.globl	i
	.p2align	3, 0x0
i:
	.quad	0                               # 0x0
	.size	i, 8

	.type	scale,@object                   # @scale
	.globl	scale
	.p2align	3, 0x0
scale:
	.quad	0                               # 0x0
	.size	scale, 8

	.type	terms,@object                   # @terms
	.globl	terms
	.p2align	3, 0x0
terms:
	.quad	0                               # 0x0
	.size	terms, 8

	.type	sign,@object                    # @sign
	.globl	sign
	.p2align	3, 0x0
sign:
	.quad	0                               # 0x0
	.size	sign, 8

	.type	denom,@object                   # @denom
	.globl	denom
	.p2align	3, 0x0
denom:
	.quad	0                               # 0x0
	.size	denom, 8

	.type	piScaled,@object                # @piScaled
	.globl	piScaled
	.p2align	3, 0x0
piScaled:
	.quad	0                               # 0x0
	.size	piScaled, 8

	.type	termValue,@object               # @termValue
	.globl	termValue
	.p2align	3, 0x0
termValue:
	.quad	0                               # 0x0
	.size	termValue, 8

	.type	intPart,@object                 # @intPart
	.globl	intPart
	.p2align	3, 0x0
intPart:
	.quad	0                               # 0x0
	.size	intPart, 8

	.type	fracPart,@object                # @fracPart
	.globl	fracPart
	.p2align	3, 0x0
fracPart:
	.quad	0                               # 0x0
	.size	fracPart, 8

	.type	tmp,@object                     # @tmp
	.globl	tmp
	.p2align	3, 0x0
tmp:
	.quad	0                               # 0x0
	.size	tmp, 8

	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"."
	.size	.L__unnamed_1, 2

	.section	".note.GNU-stack","",@progbits
