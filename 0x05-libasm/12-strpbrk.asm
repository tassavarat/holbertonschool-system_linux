BITS 64

global asm_strpbrk

section .text
asm_strpbrk:
	push rbp
	mov rbp, rsp
	push rcx
	push rbx
	push r8
	push r9

	xor rax, rax
	xor rcx, rcx
	xor r8, r8
	xor r9, r9
loop_strpbrk:
	mov r8b, [rdi + rcx]
	test r8b, r8b
	jz end
	xor rbx, rbx
loop_accept:
	mov r9b, [rsi + rbx]
	test r9b, r9b
	jz break
	cmp r8b, r9b
	je set_ptr
	inc rbx
	jmp loop_accept
break:
	inc rcx
	jmp loop_strpbrk
set_ptr:
	mov rax, rdi
	add rax, rcx
end:
	pop r9
	pop r8
	pop rbx
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
