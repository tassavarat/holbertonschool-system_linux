#include "helf.h"

/**
 * printhdrsize - prints file header sizes of ELF and an entry in program
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printhdrsize(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Half ehsize32 = hdr.Ehdr32.e_ehsize;
	Elf32_Half phentsize32 = hdr.Ehdr32.e_phentsize;
	Elf64_Half ehsize64 = hdr.Ehdr64.e_ehsize;
	Elf64_Half phentsize64 = hdr.Ehdr64.e_phentsize;

	if (is_32)
	{
		if (is_msb)
		{
			convertmsb((char *) &ehsize32, sizeof(ehsize32));
			convertmsb((char *) &phentsize32, sizeof(phentsize32));
		}
		printf("%21s%-16c%i%s\n", "Size of this header", ':', ehsize32,
				" (bytes)");
		printf("%25s%-12c%i%s\n", "Size of program headers", ':',
				phentsize32, " (bytes)");
	}
	else
	{
		if (is_msb)
		{
			convertmsb((char *) &ehsize64, sizeof(ehsize64));
			convertmsb((char *) &phentsize64, sizeof(phentsize64));
		}
		printf("%21s%-16c%i%s\n", "Size of this header", ':', ehsize64,
				" (bytes)");
		printf("%25s%-12c%i%s\n", "Size of program headers", ':',
				phentsize64, " (bytes)");
	}
}

/**
 * printflags - prints processor-specific flags associated with the file
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printflags(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Word flags32 = hdr.Ehdr32.e_flags;
	Elf64_Word flags64 = hdr.Ehdr64.e_flags;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &flags32, sizeof(flags32));
		printf("%7s%-30c0x%x\n", "Flags", ':', flags32);
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &flags64, sizeof(flags64));
		printf("%7s%-30c0x%x\n", "Flags", ':', flags64);
	}
}

/**
 * printpshoff - prints program and section header table file offset
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printpshoff(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Off phoff32 = hdr.Ehdr32.e_phoff;
	Elf32_Off shoff32 = hdr.Ehdr32.e_shoff;
	Elf64_Off phoff64 = hdr.Ehdr64.e_phoff;
	Elf64_Off shoff64 = hdr.Ehdr64.e_shoff;

	if (is_32)
	{
		if (is_msb)
		{
			convertmsb((char *) &phoff32, sizeof(phoff32));
			convertmsb((char *) &shoff32, sizeof(shoff32));
		}
		printf("%26s%-11c%i%s\n", "Start of program headers", ':',
				phoff32, " (bytes into file)");
		printf("%26s%-11c%i%s\n", "Start of section headers", ':',
				shoff32, " (bytes into file)");
	}
	else
	{
		if (is_msb)
		{
			convertmsb((char *) &phoff64, sizeof(phoff64));
			convertmsb((char *) &shoff64, sizeof(shoff64));
		}
		printf("%26s%-11c%li%s\n", "Start of program headers", ':',
				phoff64, " (bytes into file)");
		printf("%26s%-11c%li%s\n", "Start of section headers", ':',
				shoff64, " (bytes into file)");
	}
}

/**
 * printentry - prints virtual address where the system first transfers control
 * @hdr: struct containing elf header information
 * @is_32: specifies whether ELF file is 32-bit
 * @is_msb: specifies if ELF file is big endian
 */
void printentry(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Addr entry32 = hdr.Ehdr64.e_entry;
	Elf64_Addr entry64 = hdr.Ehdr64.e_entry;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &entry32, sizeof(entry32));
		printf("%21s%-16c0x%x\n", "Entry point address", ':', entry32);
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &entry64, sizeof(entry64));
		printf("%21s%-16c0x%lx\n", "Entry point address", ':', entry64);
	}
}

/**
 * printfileversion - prints file version
 * @hdr: struct containing elf header information
 * @is_msb: specifies if ELF file is big endian
 */
void printfileversion(hdrs hdr, int is_msb)
{
	Elf64_Word version = hdr.Ehdr64.e_version;

	if (is_msb)
		convertmsb((char *) &version, sizeof(version));
	printf("%9s%-28c%#x\n", "Version", ':',
			version == EV_NONE ? EV_NONE : EV_CURRENT);
}
