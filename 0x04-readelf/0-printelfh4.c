#include "helf.h"

/**
 * printshstrndx - prints section header table index
 * @hdr: struct containing elf header information
 */
void printshstrndx(hdrs hdr)
{
	printf("%35s%-2c%i\n", "Section header string table index", ':',
			hdr.hdr64.e_shstrndx);
}

/**
 * printshnum - prints number of entries in the section header table
 * @hdr: struct containing elf header information
 */
void printshnum(hdrs hdr)
{
	printf("%27s%-10c%i\n", "Number of section headers", ':',
			hdr.hdr64.e_shnum);
}

/**
 * printshentsize - prints a sections header size
 * @hdr: struct containing elf header information
 */
void printshentsize(hdrs hdr)
{
	printf("%25s%-12c%i%s\n", "Size of section headers", ':',
			hdr.hdr64.e_shentsize, " (bytes)");
}

/**
 * printphnum - prints number of entries in program header table
 * @hdr: struct containing elf header information
 */
void printphnum(hdrs hdr)
{
	printf("%27s%-10c%i\n", "Number of program headers", ':',
			hdr.hdr64.e_phnum);
}
