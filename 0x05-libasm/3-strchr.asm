BITS 64

global asm_strchr

section .text
asm_strchr:
	push rbp
	mov rbp, rsp

loop_asm_strchr:
	mov al, [rdi]
	cmp al , sil
	je match
	test al, al
	jz null
	inc rdi
	jmp loop_asm_strchr
null:
	xor rax, rax
	jmp end
match:
	mov rax, rdi
end:
	mov rsp, rbp
	pop rbp
	ret
