#include "helf.h"

/**
 * printmachine2 - prints architecture
 * @machine: int value specifying architecture
 */
void printmachine2(Elf64_Half machine)
{
	switch (machine)
	{
		case EM_PPC:
			printf("%s\n", "PowerPC");
			break;
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
			printf("%s\n", "Advanced Micro Devices X86-64");
			break;
		case EM_VAX:
			printf("%s\n", "Digital VAX");
	}
}

/**
 * printmachine - prints architecture
 * @hdr: struct containing elf header information
 * @is_msb: specifies if ELF file is big endian
 */
void printmachine(hdrs hdr, int is_msb)
{
	Elf64_Half machine = hdr.Ehdr64.e_machine;

	if (is_msb)
		convertmsb((char *) &machine, sizeof(machine));
	printf("%9s%-28c", "Machine", ':');
	switch (machine)
	{
		case EM_NONE:
			printf("%s\n", "No machine");
			break;
		case EM_M32:
			printf("%s\n", "AT&T WE 32100");
			break;
		case EM_SPARC:
			printf("%s\n", "Sparc");
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
		default:
			printmachine2(machine);
	}
}

/**
 * printtype - prints the object file type
 * @hdr: struct containing elf header information
 * @is_msb: specifies if ELF file is big endian
 */
void printtype(hdrs hdr, int is_msb)
{
	Elf64_Half type = hdr.Ehdr64.e_type;

	if (is_msb)
		convertmsb((char *) &type, sizeof(type));
	printf("%6s%-31c", "Type", ':');
	switch (type)
	{
		case ET_NONE:
			puts("NONE (No file type)");
			break;
		case ET_REL:
			puts("REL (Relocatable file)");
			break;
		case ET_EXEC:
			puts("EXEC (Executable file)");
			break;
		case ET_DYN:
			puts("DYN (Shared object file)");
			break;
		case ET_CORE:
			puts("CORE (Core file)");
	}
}

/**
 * printosabi - prints OS, ABI to which the object is targeted, and ABI version
 * @hdr: struct containing elf header information
 */
void printosabi(hdrs hdr)
{
	printf("%8s%-29c", "OS/ABI", ':');
	switch (hdr.Ehdr64.e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("UNIX - System V\n");
			break;
		case ELFOSABI_HPUX:
			printf("UNIX - HP-UX\n");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD\n");
			break;
		case ELFOSABI_LINUX:
			printf("UNIX - Linux\n");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris\n");
			break;
		case ELFOSABI_IRIX:
			printf("UNIX - SGI Irix\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("UNIX - FreeBSD\n");
			break;
		case ELFOSABI_TRU64:
			printf("UNIX - Compaq TRU64\n");
			break;
		case ELFOSABI_ARM:
			printf("UNIX - ARM\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("UNIX - Standalone (embedded) application\n");
			break;
		default:
			printf("<unknown: %x>\n", hdr.Ehdr64.e_ident[EI_OSABI]);
	}
	printf("%14s%24i\n", "ABI Version:",
			hdr.Ehdr64.e_ident[EI_ABIVERSION]);
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
	if (hdr.Ehdr64.e_ident[EI_VERSION] == EV_NONE)
	{
		fprintf(stderr, "%s: Error: Invalid ELF version\n", arg_str);
		return (1);
	}
	printf("%9s%-28c%i (current)\n", "Version", ':', EV_CURRENT);
	return (0);
}
