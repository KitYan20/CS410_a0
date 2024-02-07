	.intel_syntax noprefix
	.section .data
string:
	.ascii "Hello World\n"
length:
	.quad 0

	.section .text
	.global _start
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, OFFSET [string]
	mov rcx, OFFSET [length]
	sub rcx, rsi
	mov rdx, rcx
	syscall
	
	mov rax, 60
	mov rdi, 0
	syscall
