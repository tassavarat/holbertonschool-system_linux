BITS 64

section .text
	global asm_strcmp
asm_strcmp:
	push rbp
	mov rbp, rsp
	push rbx
	push rcx

	xor rcx, rcx
loop_asm_strcmp:
	mov al, [rdi + rcx]
	mov bl, [rsi + rcx]
	test al, al
	jz compare
	test bl, bl
	jz compare
	cmp al, bl
	jne compare
	inc rcx
	jmp loop_asm_strcmp
compare:
	cmp al, bl
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
	pop rcx
	pop rbx
	mov rsp, rbp
	pop rbp
	ret
