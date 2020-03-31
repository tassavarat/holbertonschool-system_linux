BITS 64

section .text
	global asm_strchr
asm_strchr:
	push rbp
	mov rbp, rsp

loop_asm_strchr:
	mov al, [rdi]
	cmp al , sil
	je end
	inc rdi
	test dil, dil
	jz end
	jmp loop_asm_strchr
end:
	mov rax, rdi
	mov rsp, rbp
	pop rbp
	ret
