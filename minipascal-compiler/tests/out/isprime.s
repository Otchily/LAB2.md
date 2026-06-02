	.text
	.file	"isprime"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movslq	%edi, %rdi
	callq	mp_init_runtime@PLT
	movl	$1, %edi
	callq	mp_argi@PLT
	movq	n@GOTPCREL(%rip), %rcx
	movq	%rax, (%rcx)
	cmpq	$1, %rax
	jg	.LBB0_3
# %bb.1:                                # %then
	movq	prime@GOTPCREL(%rip), %rax
	movb	$0, (%rax)
.LBB0_2:                                # %ifend
	movq	prime@GOTPCREL(%rip), %rax
	movzbl	(%rax), %edi
	callq	mp_write_bool@PLT
	callq	mp_writeln@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.LBB0_3:                                # %else
	.cfi_def_cfa_offset 16
	movq	prime@GOTPCREL(%rip), %rsi
	movb	$1, (%rsi)
	movq	i@GOTPCREL(%rip), %rdi
	movq	$2, (%rdi)
	jmp	.LBB0_4
	.p2align	4, 0x90
.LBB0_7:                                # %ifend6
                                        #   in Loop: Header=BB0_4 Depth=1
	incq	(%rdi)
.LBB0_4:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rdi), %rax
	imulq	%rax, %rax
	cmpq	(%rcx), %rax
	jg	.LBB0_2
# %bb.5:                                # %while.body
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	(%rcx), %rax
	cqto
	idivq	(%rdi)
	testq	%rdx, %rdx
	jne	.LBB0_7
# %bb.6:                                # %then5
                                        #   in Loop: Header=BB0_4 Depth=1
	movb	$0, (%rsi)
	movq	(%rcx), %rax
	movq	%rax, (%rdi)
	jmp	.LBB0_7
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

	.type	prime,@object                   # @prime
	.globl	prime
prime:
	.byte	0                               # 0x0
	.size	prime, 1

	.section	".note.GNU-stack","",@progbits
