.globl swap_context
swap_context:
movq 0(%rsp),%rax
movq %rax,0(%rdi)
movq %rdi,8(%rdi)
movq %rsi,16(%rdi)
movq %rcx,24(%rdi)
movq %rdx,32(%rdi)
movq %r8,40(%rdi)
movq %r9,48(%rdi)
movq %rbx,56(%rdi)
movq %rbp,64(%rdi)
leaq 8(%rsp),%rax
movq %rax,72(%rdi)
movq %r12,80(%rdi)
movq %r13,88(%rdi)
movq %r14,96(%rdi)
movq %r15,104(%rdi)


movq 64(%rsi),%rbp
movq 72(%rsi),%rsp
movq 104(%rsi),%r15
movq 96(%rsi),%r14
movq 88(%rsi),%r13
movq 80(%rsi),%r12

movq 48(%rsi),%r9
movq 40(%rsi),%r8

movq 8(%rsi),%rdi
movq 24(%rsi),%rcx
movq 32(%rsi),%rdx
movq 56(%rsi),%rbx
movq 0(%rsi),%rax
movq 16(%rsi),%rsi
jmp *%rax

