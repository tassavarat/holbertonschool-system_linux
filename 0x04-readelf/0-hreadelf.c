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
	FILE *fp;
	int exit_stat;

	fp = parse_args(argc, argv);
	if (!fp)
		return (1);
	exit_stat = printelfh(fp, *argv);
	return (exit_stat);
}
