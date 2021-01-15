.intel_syntax noprefix
.text
.globl _start, sys_write, sys_nanosleep

_start:
	pop rdi
	mov rsi, rsp
	xor rbp, rbp
	and rsp, -16
	call main
	mov rdi, rax
	mov rax, 60
	syscall

sys_write:
	mov rax, 1
	jmp syscall

sys_nanosleep:
	mov rax, 35

syscall:
	syscall
	ret
