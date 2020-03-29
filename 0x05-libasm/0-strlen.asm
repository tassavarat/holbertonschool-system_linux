BITS 64

section .text
	global asm_strlen
asm_strlen:
	push rbp
	mov rbp, rsp
	push rcx

	xor rcx, rcx
loop_asm_strlen:
	cmp byte [rdi + rcx], 0
	je end
	inc rcx
	jmp loop_asm_strlen
end:
	mov rax, rcx
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
