BITS 64

global asm_strcasecmp

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
	cmp r8b, 65		; rdi + rcx >= 'A'
	jge check_8_end
check_9:
	cmp r9b, 65		; rsi + rcx >= 'A'
	jge check_9_end
cont:
	test r8b, r8b
	jz dif
	test r9b, r9b
	jz dif
	cmp r8b, r9b
	jne dif
	inc rcx
	jmp loop_asm_strcasecmp
check_8_end:
	cmp r8b, 90		; rdi + rcx <= 'Z'
	jle conv_8
	jmp check_9
check_9_end:
	cmp r9b, 90		; rsi + rcx <= 'Z'
	jle conv_9
	jmp cont
conv_8:
	add r8b, 32
	jmp check_9
conv_9:
	add r9b, 32
	jmp cont
dif:
	mov eax, r8d
	sub eax, r9d
end:
	pop r9
	pop r8
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
