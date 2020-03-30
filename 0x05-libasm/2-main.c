#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "Holberton Socool"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	/* char *str1 = "Betty"; */
	/* char *str2 = "Batty"; */

	/* printf("%i\n", strncmp(S1, S3, 1)); */
	/* printf("%i\n", asm_strncmp(S1, S3, 1)); */
	/* printf("%i\n", strncmp(S1, S3, 11)); */
	/* printf("%i\n", asm_strncmp(S1, S3, 11)); */
	/* printf("%i\n", strncmp(S1, S3, 15)); */
	/* printf("%i\n", asm_strncmp(S1, S3, 15)); */
	/* printf("%i\n", strncmp(S1, S1, 16)); */
	/* printf("%i\n", asm_strncmp(S1, S1, 16)); */
	/* printf("%i\n", strncmp(S1, S2, 1)); */
	/* printf("%i\n", asm_strncmp(S1, S2, 1)); */
	/* printf("%i\n", strncmp(S1, S2, 0)); */
	/* printf("%i\n", asm_strncmp(S1, S2, 0)); */
	/* printf("%i\n", strncmp("Betty", "Betto", 5)); */
	/* printf("%i\n", asm_strncmp("Betty", "Betto", 5)); */
	/* printf("%i\n", strncmp("Yetty", "Betto", 5)); */
	/* printf("%i\n", asm_strncmp("Yetty", "Betto", 5)); */
	/* printf("%i\n", strncmp(str1, str2, 5)); */
	/* printf("%i\n", asm_strncmp(str1, str2, 5)); */
	/* printf("%i\n", strncmp(str1, str1, 5)); */
	/* printf("%i\n", asm_strncmp(str1, str1, 5)); */
	assert(strncmp(S1, S3, 1) == asm_strncmp(S1, S3, 1));
	assert(strncmp(S1, S3, 11) == asm_strncmp(S1, S3, 11));
	assert(strncmp(S1, S3, 15) == asm_strncmp(S1, S3, 15));

	printf("All good!\n");
	return (EXIT_SUCCESS);
}
