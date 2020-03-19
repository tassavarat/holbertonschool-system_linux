#include "helf.h"

/**
 * printversion - prints version number of ELF specification
 * @hdr: struct containing elf header information
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printversion(Elf64_Ehdr hdr, char *arg_str)
{
	if (hdr.e_ident[EI_VERSION] == EV_NONE)
	{
		fprintf(stderr, "%s: Error: Invalid ELF version\n", arg_str);
		return (1);
	}
	printf("%10s%28i (current)\n", "Version:", EV_CURRENT);
	return (0);
}

/**
 * printdata - prints data encoding of processor-specific data in the file
 * @hdr: struct containing elf header information
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printdata(Elf64_Ehdr hdr, char *arg_str)
{
	if (hdr.e_ident[EI_DATA] == ELFDATANONE)
	{
		fprintf(stderr, "%s: Error: Invalid data encoding\n", arg_str);
		return (1);
	}
	printf("%7s%46s%s\n", "Data:", "2's complement, ",
			hdr.e_ident[EI_DATA] == ELFDATA2LSB ?
			"little endian" : "big endian");
	return (0);
}

/**
 * printclass - prints architecture information
 * @hdr: struct containing elf header information
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printclass(Elf64_Ehdr hdr, char *arg_str)
{
	if (hdr.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		fprintf(stderr, "%s: Error: Invalid class\n", arg_str);
		return (1);
	}
	printf("%8s%32s%i\n", "Class:", "ELF",
			hdr.e_ident[EI_CLASS] == ELFCLASS32 ? 32 : 64);
	return (0);
}

/**
 * printmag - prints the magic numbers
 * @hdr: struct containing elf header information
 */
void printmag(Elf64_Ehdr hdr)
{
	size_t i;

	printf("%11s", "Magic:   ");
	for (i = 0; i < EI_NIDENT; ++i)
	{
		printf("%02x", hdr.e_ident[i]);
		if (i < EI_NIDENT - 1)
			putchar(' ');
	}
	putchar('\n');
}

/**
 * printelfh - prints elf header
 * @fp: pointer to file stream
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printelfh(FILE *fp, char *arg_str)
{
	Elf64_Ehdr hdr;
	int exit_stat;

	fread(&hdr, 1, sizeof(hdr), fp);
	if (memcmp(hdr.e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: %s%s\n", arg_str,
				"Error: Not an ELF file - ",
				"it has the wrong magic bytes at the start");
		exit_stat = 1;
		goto out;
	}
	puts("ELF Header:");
	printmag(hdr);
	exit_stat = printclass(hdr, arg_str);
	if (exit_stat)
		goto out;
	exit_stat = printdata(hdr, arg_str);
	if (exit_stat)
		goto out;
	exit_stat = printversion(hdr, arg_str);
	if (exit_stat)
		goto out;
	printosabi(hdr);
	printtype(hdr);
	printmachine(hdr);
	printfileversion(hdr);
	exit_stat = 0;
out:
	fclose(fp);
	if (exit_stat)
		return (1);
	return (0);
}