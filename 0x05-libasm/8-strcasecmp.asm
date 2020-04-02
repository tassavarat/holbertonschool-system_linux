BITS 64

global asm_strcasecmp

section .text
asm_strcasecmp:
	push rbp
	mov rbp, rsp
	push rcx
	push r8
	push r9

	xor rcx, rcx
	xor r8, r8
	xor r9, r9
	xor eax, eax
loop_asm_strcasecmp:
	mov r8b, [rdi + rcx]
	mov r9b, [rsi + rcx]
	cmp r8b, 65		; begin checking r8b
	jl check_9		; rdi + rcx < 'A'
	cmp r8b, 90
	jg check_9		; rdi + rcx > 'Z'
	add r8b, 32
check_9:
	cmp r9b, 65
	jl cont			; rsi + rcx < 'A'
	cmp r9b, 90
	jg cont			; rsi + rcx > 'Z'
	add r9b, 32
cont:
	mov eax, r8d
	sub eax, r9d
	test eax, eax		; not 0 if difference
	jnz end
	test r8b, r8b
	jz end
	inc rcx
	jmp loop_asm_strcasecmp
end:
	pop r9
	pop r8
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
