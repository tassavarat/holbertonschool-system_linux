#include "helf.h"

/**
 * printhdrsize - prints file header sizes of ELF and an entry in program
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printhdrsize(hdrs hdr, int is_32)
{
	printf("%21s%-16c%i%s\n", "Size of this header", ':',
			is_32 ? hdr.hdr32.e_ehsize : hdr.hdr64.e_ehsize,
			" (bytes)");
	printf("%25s%-12c%i%s\n", "Size of program headers", ':',
			is_32 ? hdr.hdr32.e_phentsize : hdr.hdr64.e_phentsize,
			" (bytes)");
}

/**
 * printflags - prints processor-specific flags associated with the file
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printflags(hdrs hdr, int is_32)
{
	printf("%7s%-30c0x%x\n", "Flags", ':', is_32 ? hdr.hdr32.e_flags :
			hdr.hdr64.e_flags);
}

/**
 * printpshoff - prints program and section header table file offset
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printpshoff(hdrs hdr, int is_32)
{
	printf("%26s%-11c%li%s\n", "Start of program headers", ':',
			is_32 ? hdr.hdr32.e_phoff : hdr.hdr64.e_phoff,
			" (bytes into file)");
	printf("%26s%-11c%li%s\n", "Start of section headers", ':',
			is_32 ? hdr.hdr32.e_shoff : hdr.hdr64.e_shoff,
			" (bytes into file)");
}

/**
 * printentry - prints virtual address where the system first transfers control
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 */
void printentry(hdrs hdr, int is_32)
{
	printf("%21s%-16c%#lx\n", "Entry point address", ':',
			is_32 ? hdr.hdr32.e_entry : hdr.hdr64.e_entry);
}

/**
 * printfileversion - prints file version
 * @hdr: struct containing elf header information
 */
void printfileversion(hdrs hdr)
{
	printf("%9s%-28c%#x\n", "Version", ':',
			hdr.hdr64.e_version == EV_NONE ? EV_NONE : EV_CURRENT);
}
