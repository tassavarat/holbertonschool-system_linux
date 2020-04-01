BITS 64

section .text
	global asm_memcpy
asm_memcpy:
	push rbp
	mov rbp, rsp
	push rbx

loop_asm_memcpy:
	test rdx, rdx
	jz end
	mov bl, [rsi]
	mov [rdi], bl
	inc rdi
	inc rsi
	dec rdx
	jmp loop_asm_memcpy
end:
	pop rbx
	mov rsp, rbp
	pop rbp
	ret
