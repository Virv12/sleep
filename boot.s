.intel_syntax noprefix
.globl _start, syscall, sys_write, sys_nanosleep, sys_exit

.text
_start:
	pop rdi
	mov rsi, rsp
	xor rbp, rbp
	and rsp, -16
	call main
	mov rdi, rax

sys_exit:
	mov rax, 60
	syscall

.section .text.sys_write
sys_write:
	mov rax, 1
	syscall
	ret

.section .text.sys_nanosleep
sys_nanosleep:
	mov rax, 35
	syscall
	ret

.section .text.syscall
syscall:
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	mov r10, r8
	mov r8, r9
	syscall
	ret
