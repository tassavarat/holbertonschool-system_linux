BITS 64

section .text
	global asm_strncmp
asm_strncmp:
	push rbp
	mov rbp, rsp
	push r8
	push r9
	push rcx

	xor rcx, rcx
	xor r8, r8
	xor r9, r9
	xor eax, eax
loop_asm_strncmp:
	cmp rcx, rdx
	je diff
	mov r8b, [rdi + rcx]
	mov r9b, [rsi + rcx]
	test r8b, r8b
	jz diff
	test r9b, r9b
	jz diff
	cmp r8b, r9b
	jne diff
	inc rcx
	jmp loop_asm_strncmp
diff:
	mov eax, r8d
	sub eax, r9d
	pop rcx
	pop r9
	pop r8
	mov rsp, rbp
	pop rbp
	ret
