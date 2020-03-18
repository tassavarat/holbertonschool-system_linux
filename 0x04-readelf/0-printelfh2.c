#include "helf.h"

/**
 * printfileversion - prints file version
 * @hdr: struct containing elf header information
 */
void printfileversion(Elf64_Ehdr hdr)
{
	printf("%10s%29s%x\n", "Version:", "0x",
			hdr.e_version == EV_NONE ? EV_NONE : EV_CURRENT);
}

/**
 * printmachine2 - prints architecture
 * @machine: int value specifying architecture
 */
void printmachine2(Elf64_Half machine)
{
	switch (machine)
	{
		case EM_PPC64:
			printf("%41s\n", "PowerPC 64-bit");
			break;
		case EM_S390:
			printf("%35s\n", "IBM S390");
			break;
		case EM_ARM:
			printf("%30s\n", "ARM");
			break;
		case EM_SH:
			printf("%37s\n", "Hitachi SH");
			break;
		case EM_SPARCV9:
			printf("%42s\n", "SPARC v9 64-bit");
			break;
		case EM_IA_64:
			printf("%39s\n", "Intel Merced");
			break;
		case EM_X86_64:
			printf("%50s\n", "AMD x86-64 architecture");
			break;
		case EM_VAX:
			printf("%38s\n", "Digital VAX");
	}
}

/**
 * printmachine - prints architecture
 * @hdr: struct containing elf header information
 */
void printmachine(Elf64_Ehdr hdr)
{
	printf("%10s", "Machine:");
	switch (hdr.e_machine)
	{
		case EM_NONE:
			printf("%34s\n", "EM_NONE");
			break;
		case EM_M32:
			printf("%40s\n", "AT&T WE 32100");
			break;
		case EM_SPARC:
			printf("%36s\n", "SUN SPARC");
			break;
		case EM_386:
			printf("%33s\n", "EM_386");
			break;
		case EM_68K:
			printf("%33s\n", "EM_68K");
			break;
		case EM_88K:
			printf("%47s\n", "Motorola m88k family");
			break;
		case EM_860:
			printf("%38s\n", "Intel 80860");
			break;
		case EM_MIPS:
			printf("%48s\n", "MIPS R3000 big-endian");
			break;
		case EM_PARISC:
			printf("%31s\n", "HPPA");
			break;
		case EM_SPARC32PLUS:
			printf("%41s\n", "Sun's \"v8plus\"");
			break;
		case EM_PPC:
			printf("%34s\n", "PowerPC");
			break;
		default:
			printmachine2(hdr.e_machine);
	}
}

/**
 * printtype - prints the object file type
 * @hdr: struct containing elf header information
 */
void printtype(Elf64_Ehdr hdr)
{
	printf("%7s", "Type:");
	switch (hdr.e_type)
	{
		case ET_NONE:
			printf("%49s\n", "NONE (No file type)");
			break;
		case ET_REL:
			printf("%52s\n", "REL (Relocatable file)");
			break;
		case ET_EXEC:
			printf("%44s\n", "EXEC (ET_EXEC)");
			break;
		case ET_DYN:
			printf("%54s\n", "DYN (Shared object file)");
			break;
		case ET_CORE:
			printf("%46s\n", "CORE (Core file)");
	}
}

/**
 * printosabi - prints OS, ABI to which the object is targeted, and ABI version
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
	printf("\n%14s%24i\n", "ABI Version:", hdr.e_ident[EI_ABIVERSION]);
}
