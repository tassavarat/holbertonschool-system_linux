#include "helf.h"

/**
 * printmachine2 - prints architecture
 * @machine: int value specifying architecture
 */
void printmachine2(Elf64_Half machine)
{
	switch (machine)
	{
		case EM_PPC64:
			printf("%s\n", "PowerPC 64-bit");
			break;
		case EM_S390:
			printf("%s\n", "IBM S390");
			break;
		case EM_ARM:
			printf("%s\n", "ARM");
			break;
		case EM_SH:
			printf("%s\n", "Hitachi SH");
			break;
		case EM_SPARCV9:
			printf("%s\n", "SPARC v9 64-bit");
			break;
		case EM_IA_64:
			printf("%s\n", "Intel Merced");
			break;
		case EM_X86_64:
			printf("%s\n", "AMD x86-64 architecture");
			break;
		case EM_VAX:
			printf("%s\n", "Digital VAX");
	}
}

/**
 * printmachine - prints architecture
 * @hdr: struct containing elf header information
 */
void printmachine(hdrs hdr)
{
	printf("%9s%-28c", "Machine", ':');
	switch (hdr.hdr64.e_machine)
	{
		case EM_NONE:
			printf("%s\n", "No machine");
			break;
		case EM_M32:
			printf("%s\n", "AT&T WE 32100");
			break;
		case EM_SPARC:
			printf("%s\n", "SUN SPARC");
			break;
		case EM_386:
			printf("%s\n", "Intel 80386");
			break;
		case EM_68K:
			printf("%s\n", "Motorola m68k family");
			break;
		case EM_88K:
			printf("%s\n", "Motorola m88k family");
			break;
		case EM_860:
			printf("%s\n", "Intel 80860");
			break;
		case EM_MIPS:
			printf("%s\n", "MIPS R3000 big-endian");
			break;
		case EM_PARISC:
			printf("%s\n", "HPPA");
			break;
		case EM_SPARC32PLUS:
			printf("%s\n", "Sun's \"v8plus\"");
			break;
		case EM_PPC:
			printf("%s\n", "PowerPC");
			break;
		default:
			printmachine2(hdr.hdr64.e_machine);
	}
}

/**
 * printtype - prints the object file type
 * @hdr: struct containing elf header information
 */
void printtype(hdrs hdr)
{
	printf("%6s%-31c", "Type", ':');
	switch (hdr.hdr64.e_type)
	{
		case ET_NONE:
			printf("%s\n", "NONE (No file type)");
			break;
		case ET_REL:
			printf("%s\n", "REL (Relocatable file)");
			break;
		case ET_EXEC:
			printf("%s\n", "EXEC (Executable file)");
			break;
		case ET_DYN:
			printf("%s\n", "DYN (Shared object file)");
			break;
		case ET_CORE:
			printf("%s\n", "CORE (Core file)");
	}
}

/**
 * printosabi - prints OS, ABI to which the object is targeted, and ABI version
 * @hdr: struct containing elf header information
 */
void printosabi(hdrs hdr)
{
	printf("%8s%-29c%s", "OS/ABI", ':', "UNIX - ");
	switch (hdr.hdr64.e_ident[EI_OSABI])
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
	printf("\n%14s%24i\n", "ABI Version:",
			hdr.hdr64.e_ident[EI_ABIVERSION]);
}

/**
 * printversion - prints version number of ELF specification
 * @hdr: struct containing elf header information
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printversion(hdrs hdr, char *arg_str)
{
	if (hdr.hdr64.e_ident[EI_VERSION] == EV_NONE)
	{
		fprintf(stderr, "%s: Error: Invalid ELF version\n", arg_str);
		return (1);
	}
	printf("%9s%-28c%i (current)\n", "Version", ':', EV_CURRENT);
	return (0);
}
