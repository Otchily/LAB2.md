	.text
	.file	"factor"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movslq	%edi, %rdi
	callq	mp_init_runtime@PLT
	movl	$1, %edi
	callq	mp_argi@PLT
	movq	n@GOTPCREL(%rip), %rbx
	movq	%rax, (%rbx)
	movq	d@GOTPCREL(%rip), %r14
	movq	$2, (%r14)
	.p2align	4, 0x90
.LBB0_1:                                # %while.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_5 Depth 2
	movq	(%r14), %rax
	imulq	%rax, %rax
	cmpq	(%rbx), %rax
	jle	.LBB0_5
	jmp	.LBB0_2
	.p2align	4, 0x90
.LBB0_6:                                # %while.body3
                                        #   in Loop: Header=BB0_5 Depth=2
	movq	(%r14), %rdi
	callq	mp_write_int@PLT
	movl	$.L__unnamed_1, %edi
	callq	mp_write_str@PLT
	movq	(%rbx), %rax
	cqto
	idivq	(%r14)
	movq	%rax, (%rbx)
.LBB0_5:                                # %while.cond2
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%rbx), %rax
	cqto
	idivq	(%r14)
	testq	%rdx, %rdx
	je	.LBB0_6
# %bb.7:                                # %while.end4
                                        #   in Loop: Header=BB0_1 Depth=1
	incq	(%r14)
	jmp	.LBB0_1
.LBB0_2:                                # %while.end
	cmpq	$1, (%rbx)
	jle	.LBB0_4
# %bb.3:                                # %then
	movq	(%rbx), %rdi
	callq	mp_write_int@PLT
.LBB0_4:                                # %else
	callq	mp_writeln@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
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

	.type	d,@object                       # @d
	.globl	d
	.p2align	3, 0x0
d:
	.quad	0                               # 0x0
	.size	d, 8

	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	" "
	.size	.L__unnamed_1, 2

	.section	".note.GNU-stack","",@progbits
