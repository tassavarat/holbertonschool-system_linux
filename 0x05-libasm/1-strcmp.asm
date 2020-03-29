BITS 64

section .text
	global asm_strcmp
asm_strcmp:
	push rbp
	mov rbp, rsp
	push bx
	push rcx

	xor rcx, rcx
loop_asm_strcmp:
	mov ax, [rdi + rcx]
	mov bx, [rsi + rcx]
	test ax, ax
	jz compare
	test bx, bx
	jz compare
	cmp ax, bx
	jne compare
	inc rcx
	jmp loop_asm_strcmp
compare:
	sub ax, bx
	je equal
	jl less
	jg greater
equal:
	mov rax, 0
	jmp end
less:
	mov rax, -1
	jmp end
greater:
	mov rax, 1
	jmp end
end:
	pop bx
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
