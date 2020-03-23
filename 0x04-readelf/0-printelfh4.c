#include "helf.h"

/**
 * printshstrndx - prints section header table index
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printshstrndx(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Half shstrndx32 = hdr.Ehdr32.e_shstrndx;
	Elf64_Half shstrndx64 = hdr.Ehdr64.e_shstrndx;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &shstrndx32, sizeof(shstrndx32));
		printf("%35s%-2c%i\n", "Section header string table index",
				':', shstrndx32);
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &shstrndx64, sizeof(shstrndx64));
		printf("%35s%-2c%i\n", "Section header string table index",
				':', shstrndx64);
	}
}

/**
 * printshnum - prints number of entries in the section header table
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printshnum(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Half shnum32 = hdr.Ehdr32.e_shnum;
	Elf64_Half shnum64 = hdr.Ehdr64.e_shnum;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &shnum32, sizeof(shnum32));
		printf("%27s%-10c%i\n", "Number of section headers", ':',
				shnum32);
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &shnum64, sizeof(shnum64));
		printf("%27s%-10c%i\n", "Number of section headers", ':',
				shnum64);
	}
}

/**
 * printshentsize - prints a sections header size
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printshentsize(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Half shentsize32 = hdr.Ehdr32.e_shentsize;
	Elf64_Half shentsize64 = hdr.Ehdr64.e_shentsize;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &shentsize32, sizeof(shentsize32));
		printf("%25s%-12c%i%s\n", "Size of section headers", ':',
				shentsize32, " (bytes)");
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &shentsize64, sizeof(shentsize64));
		printf("%25s%-12c%i%s\n", "Size of section headers", ':',
				shentsize64, " (bytes)");
	}
}

/**
 * printphnum - prints number of entries in program header table
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printphnum(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Half phnum32 = hdr.Ehdr32.e_phnum;
	Elf64_Half phnum64 = hdr.Ehdr64.e_phnum;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &phnum32, sizeof(phnum32));
		printf("%27s%-10c%i\n", "Number of program headers", ':',
				phnum32);
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &phnum64, sizeof(phnum64));
		printf("%27s%-10c%i\n", "Number of program headers", ':',
				phnum64);
	}
}
