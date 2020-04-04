#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  "School"
#define S3  "Socool"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	/* printf("%s\t%s\n", strstr(S1, S2), asm_strstr(S1, S2));		/1* School *1/ */
	/* printf("%i\n", strstr(S1, S3) == asm_strstr(S1, S3));		/1* NULL *1/ */
	/* printf("%s\t%s\n", strstr(S1, S1), asm_strstr(S1, S1));		/1* Holberton School *1/ */
	assert(strstr(S1, S2) == asm_strstr(S1, S2));
	assert(strstr(S1, S3) == asm_strstr(S1, S3));
	assert(strstr(S1, S1) == asm_strstr(S1, S1));

	printf("All good!\n");
	return (EXIT_SUCCESS);
}
