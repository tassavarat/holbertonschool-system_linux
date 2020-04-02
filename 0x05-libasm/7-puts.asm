BITS 64

global asm_puts
extern asm_strlen

section .text
asm_puts:
	push rbp
	mov rbp, rsp
	push rdi

	call asm_strlen
	pop rdi

	push rdi
	push rsi
	push rdx
	mov rdx, rax	; bytes to write
	mov rax, 1	; write syscall
	mov rsi, rdi	; buffer address
	mov rdi, 1	; stdout fd
	syscall

	pop rdx
	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret
