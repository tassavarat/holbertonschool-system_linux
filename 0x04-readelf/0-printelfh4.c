#include "helf.h"

/**
 * printshstrndx - prints section header table index
 * @hdr: struct containing elf header information
 */
void printshstrndx(Elf64_Ehdr hdr)
{
	printf("%35s%-2c%i\n", "Section header string table index", ':',
			hdr.e_shstrndx);
}

/**
 * printshnum - prints number of entries in the section header table
 * @hdr: struct containing elf header information
 */
void printshnum(Elf64_Ehdr hdr)
{
	printf("%27s%-10c%i\n", "Number of section headers", ':',
			hdr.e_shnum);
}

/**
 * printshentsize - prints a sections header size
 * @hdr: struct containing elf header information
 */
void printshentsize(Elf64_Ehdr hdr)
{
	printf("%25s%-12c%i%s\n", "Size of section headers", ':',
			hdr.e_shentsize, " (bytes)");
}

/**
 * printphnum - prints number of entries in program header table
 * @hdr: struct containing elf header information
 */
void printphnum(Elf64_Ehdr hdr)
{
	printf("%27s%-10c%i\n", "Number of program headers", ':', hdr.e_phnum);
}
