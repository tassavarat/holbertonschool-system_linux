#include "helf.h"

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
	printf("%6s%-31c%s%s\n", "Data", ':', "2's complement, ",
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
	printf("%7s%-30c%s%i\n", "Class", ':', "ELF",
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
		printf("%02x ", hdr.e_ident[i]);
	putchar('\n');
}

/**
 * printelfh2 - wrapper function to handle printing of elf header
 * @hdr: struct containing elf header information
 */
void printelfh2(Elf64_Ehdr hdr)
{
	printosabi(hdr);
	printtype(hdr);
	printmachine(hdr);
	printfileversion(hdr);
	printentry(hdr);
	printpshoff(hdr);
	printflags(hdr);
	printhdrsize(hdr);
	printphnum(hdr);
	printshentsize(hdr);
	printshnum(hdr);
	printshstrndx(hdr);
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
	printelfh2(hdr);
	exit_stat = 0;
out:
	fclose(fp);
	if (exit_stat)
		return (1);
	return (0);
}
