#include "helf.h"

static int is_32;
static int is_msb;

/**
 * printdata - prints data encoding of processor-specific data in the file
 * @hdr: struct containing elf header information
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printdata(hdrs hdr, char *arg_str)
{
	if (hdr.Ehdr64.e_ident[EI_DATA] == ELFDATANONE)
	{
		fprintf(stderr, "%s: Error: Invalid data encoding\n", arg_str);
		return (1);
	}
	if (hdr.Ehdr64.e_ident[EI_DATA] == ELFDATA2LSB)
	{
		printf("%6s%-31c%s%s\n", "Data", ':', "2's complement, ",
				"little endian");
	}
	else
	{
		printf("%6s%-31c%s%s\n", "Data", ':', "2's complement, ",
				"big endian");
		is_msb = 1;
	}
	return (0);
}

/**
 * printclass - prints architecture information
 * @hdr: struct containing elf header information
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printclass(hdrs hdr, char *arg_str)
{
	if (hdr.Ehdr64.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		fprintf(stderr, "%s: Error: Invalid class\n", arg_str);
		return (1);
	}
	if (hdr.Ehdr64.e_ident[EI_CLASS] == ELFCLASS32)
	{
		printf("%7s%-30c%s\n", "Class", ':', "ELF32");
		is_32 = 1;
	}
	else
	{
		printf("%7s%-30c%s\n", "Class", ':', "ELF64");

	}
	return (0);
}

/**
 * printmag - prints the magic numbers
 * @hdr: struct containing elf header information
 */
void printmag(hdrs hdr)
{
	size_t i;

	printf("%11s", "Magic:   ");
	for (i = 0; i < EI_NIDENT; ++i)
		printf("%02x ", hdr.Ehdr64.e_ident[i]);
	putchar('\n');
}

/**
 * printelfhwrapper - wrapper function to handle printing of elf header
 * @hdr: struct containing elf header information
 */
void printelfhwrapper(hdrs hdr)
{
	printosabi(hdr);
	printtype(hdr, is_msb);
	printmachine(hdr, is_msb);
	printfileversion(hdr, is_msb);
	printentry(hdr, is_32, is_msb);
	printpshoff(hdr, is_32, is_msb);
	printflags(hdr, is_32, is_msb);
	printhdrsize(hdr, is_32, is_msb);
	printphnum(hdr, is_32, is_msb);
	printshentsize(hdr, is_32, is_msb);
	printshnum(hdr, is_32, is_msb);
	printshstrndx(hdr, is_32, is_msb);
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
	hdrs hdr;
	int exit_stat;

	fread(&hdr.Ehdr64, sizeof(hdr.Ehdr64), 1, fp);
	rewind(fp);
	fread(&hdr.Ehdr32, sizeof(hdr.Ehdr32), 1, fp);
	if (memcmp(hdr.Ehdr64.e_ident, ELFMAG, SELFMAG))
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
	printelfhwrapper(hdr);
	exit_stat = 0;
out:
	fclose(fp);
	if (exit_stat)
		return (1);
	return (0);
}
