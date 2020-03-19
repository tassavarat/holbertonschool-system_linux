#include "helf.h"

/**
 * printhdrsize - prints file header sizes of ELF and an entry in program
 * @hdr: struct containing elf header information
 */
void printhdrsize(Elf64_Ehdr hdr)
{
	printf("%21s%-16c%i%s\n", "Size of this header", ':',
			hdr.e_ehsize, " (bytes)");
	printf("%25s%-12c%i%s\n", "Size of program headers", ':',
			hdr.e_phentsize, " (bytes)");
}

/**
 * printflags - prints processor-specific flags associated with the file
 * @hdr: struct containing elf header information
 */
void printflags(Elf64_Ehdr hdr)
{
	printf("%7s%-30c0x%x\n", "Flags", ':', hdr.e_flags);
}

/**
 * printpshoff - prints program and section header table file offset
 * @hdr: struct containing elf header information
 */
void printpshoff(Elf64_Ehdr hdr)
{
	printf("%26s%-11c%li%s\n", "Start of program headers", ':',
			hdr.e_phoff, " (bytes into file)");
	printf("%26s%-11c%li%s\n", "Start of section headers", ':',
			hdr.e_shoff, " (bytes into file)");
}

/**
 * printentry - prints virtual address where the system first transfers control
 * @hdr: struct containing elf header information
 */
void printentry(Elf64_Ehdr hdr)
{
	printf("%21s%-16c%#lx\n", "Entry point address", ':', hdr.e_entry);
}

/**
 * printfileversion - prints file version
 * @hdr: struct containing elf header information
 */
void printfileversion(Elf64_Ehdr hdr)
{
	printf("%9s%-28c%#x\n", "Version", ':',
			hdr.e_version == EV_NONE ? EV_NONE : EV_CURRENT);
}
