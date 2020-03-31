BITS 64

section .text
	global asm_strchr
asm_strchr:
	push rbp
	mov rbp, rsp

loop_asm_strchr:
	test sil, sil
	jz null
	mov al, [rdi]
	test al, al
	jz null
	cmp al , sil
	je match
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
