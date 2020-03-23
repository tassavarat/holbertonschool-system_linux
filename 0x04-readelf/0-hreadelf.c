#include "helf.h"

/**
 * main - calls parse_args and printelfh
 * @argc: number of arguments
 * @argv: pointer to array of characters containing arguments
 *
 * Return: 0 on success, otherwise 1
 */
int main(int argc, char **argv)
{
	FILE *fp64, *fp32;
	int exit_stat;

	fp64 = parse_args(argc, argv);
	if (!fp64)
		return (1);
	fp32 = fopen(argv[1], "rb");
	exit_stat = printelfh(fp64, fp32, *argv);
	return (exit_stat);
}
