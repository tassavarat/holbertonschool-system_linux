#include "helf.h"

/**
 * printosabi - prints operating system and ABI to which the object is targeted
 * @hdr: struct containing elf header information
 */
void printosabi(Elf64_Ehdr hdr)
{
	printf("%10s%34s", "OS/ABI: ", "UNIX - ");
	switch (hdr.e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("System V");
			break;
		case ELFOSABI_HPUX:
			printf("HP-UX");
			break;
		case ELFOSABI_NETBSD:
			printf("NetBSD");
			break;
		case ELFOSABI_LINUX:
			printf("Linux");
			break;
		case ELFOSABI_SOLARIS:
			printf("Sun Solaris");
			break;
		case ELFOSABI_IRIX:
			printf("SGI Irix");
			break;
		case ELFOSABI_FREEBSD:
			printf("FreeBSD");
			break;
		case ELFOSABI_TRU64:
			printf("Compaq TRU64");
			break;
		case ELFOSABI_ARM:
			printf("ARM");
			break;
		case ELFOSABI_STANDALONE:
			printf("Standalone (embedded) application");
	}
	putchar('\n');
}
