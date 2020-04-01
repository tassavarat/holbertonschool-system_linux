#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	/* asm_putc('H'); */
	/* asm_putc('b'); */
	/* asm_putc('t'); */
	/* asm_putc('n'); */
	/* asm_putc('\n'); */
	assert(asm_putc('H') == 1);
	assert(asm_putc('b') == 1);
	assert(asm_putc('t') == 1);
	assert(asm_putc('n') == 1);
	assert(asm_putc('\n') == 1);

	printf("All good!\n");
	return (EXIT_SUCCESS);
}
