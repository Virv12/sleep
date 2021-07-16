.intel_syntax noprefix
.globl _start

.text
_start:
	pop rdi
	mov rsi, rsp
	xor rbp, rbp
	and rsp, -16
	jmp start_main
