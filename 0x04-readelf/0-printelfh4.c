#include "helf.h"

/**
 * printshstrndx - prints section header table index
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printshstrndx(hdrs hdr, int is_32)
{
	printf("%35s%-2c%i\n", "Section header string table index", ':',
			is_32 ? hdr.hdr32.e_shstrndx : hdr.hdr64.e_shstrndx);
}

/**
 * printshnum - prints number of entries in the section header table
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printshnum(hdrs hdr, int is_32)
{
	printf("%27s%-10c%i\n", "Number of section headers", ':',
			is_32 ? hdr.hdr32.e_shnum : hdr.hdr64.e_shnum);
}

/**
 * printshentsize - prints a sections header size
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printshentsize(hdrs hdr, int is_32)
{
	printf("%25s%-12c%i%s\n", "Size of section headers", ':',
			is_32 ? hdr.hdr32.e_shentsize : hdr.hdr64.e_shentsize,
			" (bytes)");
}

/**
 * printphnum - prints number of entries in program header table
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printphnum(hdrs hdr, int is_32)
{
	printf("%27s%-10c%i\n", "Number of program headers", ':',
			is_32 ? hdr.hdr32.e_phnum : hdr.hdr64.e_phnum);
}
