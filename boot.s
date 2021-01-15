.intel_syntax noprefix
.text
.globl _start, syscall

_start:
	pop rdi
	mov rsi, rsp
	xor rbp, rbp
	and rsp, -16
	call main
	mov rdi, rax
	mov rax, 60
	syscall

syscall:
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	mov r10, r8
	mov r8, r9
	syscall
	ret
