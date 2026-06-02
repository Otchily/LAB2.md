	.text
	.file	"fibonacci"
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
	movq	n@GOTPCREL(%rip), %rdx
	movq	%rax, (%rdx)
	testq	%rax, %rax
	jg	.LBB0_3
# %bb.1:                                # %then
	xorl	%edi, %edi
	jmp	.LBB0_2
.LBB0_3:                                # %else
	movq	a@GOTPCREL(%rip), %rax
	movq	$0, (%rax)
	movq	b@GOTPCREL(%rip), %rcx
	movq	$1, (%rcx)
	movq	(%rdx), %rsi
	decq	%rsi
	movq	i@GOTPCREL(%rip), %rdx
	movq	$1, (%rdx)
	movq	%rsi, (%rsp)
	movq	next@GOTPCREL(%rip), %rsi
	.p2align	4, 0x90
.LBB0_4:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rdx), %rdi
	cmpq	(%rsp), %rdi
	jg	.LBB0_6
# %bb.5:                                # %for.body
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	(%rcx), %rdi
	movq	(%rax), %r8
	addq	%rdi, %r8
	movq	%r8, (%rsi)
	movq	%rdi, (%rax)
	movq	%r8, (%rcx)
	incq	(%rdx)
	jmp	.LBB0_4
.LBB0_6:                                # %for.end
	movq	(%rcx), %rdi
.LBB0_2:                                # %ifend
	callq	mp_write_int@PLT
	callq	mp_writeln@PLT
	xorl	%eax, %eax
	popq	%rcx
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

	.type	a,@object                       # @a
	.globl	a
	.p2align	3, 0x0
a:
	.quad	0                               # 0x0
	.size	a, 8

	.type	b,@object                       # @b
	.globl	b
	.p2align	3, 0x0
b:
	.quad	0                               # 0x0
	.size	b, 8

	.type	i,@object                       # @i
	.globl	i
	.p2align	3, 0x0
i:
	.quad	0                               # 0x0
	.size	i, 8

	.type	next,@object                    # @next
	.globl	next
	.p2align	3, 0x0
next:
	.quad	0                               # 0x0
	.size	next, 8

	.section	".note.GNU-stack","",@progbits
