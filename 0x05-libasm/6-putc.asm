BITS 64

section .text
	global asm_putc
asm_putc:
	push rbp
	mov rbp, rsp
	push rdi
	push rsi
	push rdx

	mov rax, 1
	mov [rsi], rdi
	mov rdi, 1
	mov rdx, 1
	syscall

	pop rdx
	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret
