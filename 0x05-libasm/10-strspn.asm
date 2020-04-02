BITS 64

global asm_strspn

section .text
asm_strspn:
	push rbp
	mov rbp, rsp
	push rcx
	push r8
	push r9

	xor rax, rax
	xor r8, r8
	xor r9, r9
loop_strspn_rdi:
	mov r8b, [rdi + rax]
	test r8b, r8b
	jz end
	xor rcx, rcx
loop_strspn_rsi:
	mov r9b, [rsi + rcx]
	test r9b, r9b
	jz end
	cmp r8b, r9b
	je break
	inc rcx
	jmp loop_strspn_rsi
break:
	inc eax
	jmp loop_strspn_rdi
end:
	pop r9
	pop r8
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
