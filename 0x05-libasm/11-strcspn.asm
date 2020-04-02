BITS 64

global asm_strcspn

section .text
asm_strcspn:
	push rbp
	mov rbp, rsp
	push rcx
	push r8
	push r9

	xor rax, rax
	xor r8, r8
	xor r9, r9
loop_strcspn_rdi:
	mov r8b, [rdi + rax]
	test r8b, r8b
	jz end
	xor rcx, rcx
loop_strcspn_rsi:
	mov r9b, [rsi + rcx]
	test r9b, r9b
	jz break
	cmp r8b, r9b
	je end
	inc rcx
	jmp loop_strcspn_rsi
break:
	inc eax
	jmp loop_strcspn_rdi
end:
	pop r9
	pop r8
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
