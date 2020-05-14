#include "helf.h"

/* char get_info(hdrs *hdr, int i) */
/* { */
/* 	char c; */

/* 	if (ELFN_ST_BIND == STB_GNU_UNIQUE) */
/* 		c = 'u'; */
/* 	else if (ELFN_ST_BIND == STB_WEAK) */
/* 		c = GET_SYM(st_shndx, i) == SHN_UNDEF ? 'w' : 'W'; */
/* 	else if (ELFN_ST_BIND == STB_WEAK && ELFN_ST_TYPE == STT_OBJECT) */
/* 		c = GET_SYM(st_shndx, i) == SHN_UNDEF ? 'v' : 'V'; */
/* 	else if (GET_SYM(st_shndx, i) == SHN_UNDEF) */
/* 		c = 'U'; */
/* 	else if (GET_SYM(st_shndx, i) == SHN_ABS) */
/* 		c = 'A'; */
/* 	else if (GET_SYM(st_shndx, i) == SHN_COMMON) */
/* 		c = 'C'; */
/* 	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i)) == SHT_NOBITS */
/* 			&& GET_SHDR(sh_flags, GET_SYM(st_shndx, i) == */
/* 				(SHF_ALLOC | SHF_WRITE))) */
/* 		c = 'B'; */
/* 	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i) == SHT_PROGBITS */
/* 				&& GET_SHDR(sh_flags, GET_SYM(st_shndx, i) == */
/* 					SHF_ALLOC))) */
/* 		c = 'R'; */
/* 	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i) == SHT_PROGBITS */
/* 				&& GET_SHDR(sh_flags, GET_SYM(st_shndx, i) == */
/* 					(SHF_ALLOC | SHF_WRITE)))) */
/* 		c = 'D'; */
/* 	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i) == SHT_PROGBITS */
/* 				&& GET_SHDR(sh_flags, GET_SYM(st_shndx, i) == */
/* 					(SHF_ALLOC | SHF_EXECINSTR)))) */
/* 		c = 'T'; */
/* 	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i) == SHT_DYNAMIC)) */
/* 		c = 'D'; */
/* 	else */
/* 		c = '?'; */
/* 	if (ELFN_ST_BIND == STB_LOCAL && c != '?') */
/* 		c += 32; */
/* 	return c; */
/* } */

/* char print_type(Elf64_Sym sym, Elf64_Shdr *shdr) */
/* { */
/* 	char c; */

/* 	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE) */
/* 		c = 'u'; */
/* 	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) */
/* 	{ */
/* 		c = 'W'; */
/* 		if (sym.st_shndx == SHN_UNDEF) */
/* 			c = 'w'; */
/* 	} */
/* 	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) */
/* 	{ */
/* 		c = 'V'; */
/* 		if (sym.st_shndx == SHN_UNDEF) */
/* 			c = 'v'; */
/* 	} */
/* 	else if (sym.st_shndx == SHN_UNDEF) */
/* 		c = 'U'; */
/* 	else if (sym.st_shndx == SHN_ABS) */
/* 		c = 'A'; */
/* 	else if (sym.st_shndx == SHN_COMMON) */
/* 		c = 'C'; */
/* 	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS */
/* 			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) */
/* 		c = 'B'; */
/* 	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS */
/* 			&& shdr[sym.st_shndx].sh_flags == SHF_ALLOC) */
/* 		c = 'R'; */
/* 	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS */
/* 			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) */
/* 		c = 'D'; */
/* 	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS */
/* 			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) */
/* 		c = 'T'; */
/* 	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC) */
/* 		c = 'D'; */
/* 	else */
/* 		c = '?'; */
/* 	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?') */
/* 		c += 32; */
/* 	return c; */
/* } */

/**
 * conv_msb - convert to big endian by reversing given array
 * @ptr: pointer to first octet of word
 * @size: size of type ptr points to
 */
void conv_msb(char *ptr, size_t size)
{
	size_t start, end;

	for (start = 0, end = size - 1; start < end; ++start, --end)
	{
		ptr[start] ^= ptr[end];
		ptr[end] ^= ptr[start];
		ptr[start] ^= ptr[end];
	}
}

int sym(hdrs *hdr)
{
	int i;
	size_t j, sym_size;
	char *str_table;

	for (i = 0; i < GET_EHDR(e_shnum); ++i)
		if (GET_SHDR(sh_type, i) == SHT_SYMTAB)
			break;
	if (i == GET_EHDR(e_shnum))
		return (0);
	hdr->Sym32 = (Elf32_Sym *) &hdr->addr[GET_SHDR(sh_offset, i)];
	hdr->Sym64 = (Elf64_Sym *) &hdr->addr[GET_SHDR(sh_offset, i)];
	str_table = &hdr->addr[GET_SHDR(sh_offset, i + 1)];
	sym_size = GET_SHDR(sh_size, i) / GET_SHDR(sh_entsize, i);
	for (j = 0; j < sym_size; ++j)
	{
		if ((GET_SYM(st_info, j) & 0xf) == STT_SECTION ||
				(GET_SYM(st_info, j) & 0xf) == STT_FILE)
			continue;
		if (IS_MSB)
		{
			conv_msb((char *) SET_YHDR(st_value, j),
					SYM_SIZE(st_value, i));
			conv_msb((char *) SET_YHDR(st_info, j),
					SYM_SIZE(st_info, i));
			conv_msb((char *) SET_YHDR(st_name, j),
					SYM_SIZE(st_name, i));
		}
		/* printf("%0*lx %c %s\n", IS_32 ? 8 : 16, GET_SYM(st_value, j), */
		/* 		get_info(hdr, i), */
		/* 		&str_table[GET_SYM(st_name, j)]); */
		/* printf("%0*lx %c %s\n", IS_32 ? 8 : 16, GET_SYM(st_value, j), */
		/* 		print_type(hdr->Sym64[i], hdr->Shdr64), */
		/* 		&str_table[GET_SYM(st_name, j)]); */
		printf("%0*lx %s\n", IS_32 ? 8 : 16, GET_SYM(st_value, j),
				&str_table[GET_SYM(st_name, j)]);
	}
	return (1);
}

/**
 * init_shdr - initialises ElfN_Shdr
 * @hdr: struct containing elf header information
 *
 * Converts entries to msb if needed
 */
void init_shdr(hdrs *hdr)
{
	int i;

	hdr->Shdr32 = (Elf32_Shdr *) &hdr->addr[GET_EHDR(e_shoff)];
	hdr->Shdr64 = (Elf64_Shdr *) &hdr->addr[GET_EHDR(e_shoff)];
	if (IS_MSB)
		for (i = 0; i < GET_EHDR(e_shnum); ++i)
		{
			conv_msb((char *) SET_SHDR(sh_type, i),
					SHDR_SIZE(sh_type, i));
			conv_msb((char *) SET_SHDR(sh_offset, i),
					SHDR_SIZE(sh_offset, i));
			conv_msb((char *) SET_SHDR(sh_size, i),
					SHDR_SIZE(sh_size, i));
			conv_msb((char *) SET_SHDR(sh_entsize, i),
					SHDR_SIZE(sh_entsize, i));
		}
}

/**
 * init_ehdr - initialises ElfN_Ehdr
 * @hdr: struct containing elf header information
 *
 * Converts entries to msb if needed
 */
void init_ehdr(hdrs *hdr)
{
	hdr->Ehdr32 = (Elf32_Ehdr *) hdr->addr;
	hdr->Ehdr64 = (Elf64_Ehdr *) hdr->addr;
	if (IS_MSB)
	{
		conv_msb((char *) SET_EHDR(e_shoff), EHDR_SIZE(e_shoff));
		conv_msb((char *) SET_EHDR(e_shentsize),
				EHDR_SIZE(e_shentsize));
		conv_msb((char *) SET_EHDR(e_shnum), EHDR_SIZE(e_shnum));
	}
}

/**
 * getelf - get ELF information
 * @fp: pointer to file stream
 * @prog_name: name of program
 * @arg_str: pointer to name of file to get ELF information from
 * @exit_stat: current exit status to update accordingly
 */
void getelf(FILE *fp, char *prog_name, char *arg_str, int *exit_stat)
{
	hdrs hdr;
	struct stat sb;

	memset(&hdr, 0, sizeof(hdr));
	if (stat(arg_str, &sb))
		goto prnterr;
	hdr.addr = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
			fileno(fp), 0);
	if (hdr.addr == MAP_FAILED)
	{
prnterr:
		perror(NULL);
		goto out;
	}
	init_ehdr(&hdr);
	if (memcmp(hdr.Ehdr64->e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: %s: file format not recognized\n",
				prog_name, arg_str);
out:
		*exit_stat = 1;
		fclose(fp);
		return;
	}
	init_shdr(&hdr);
	if (!sym(&hdr))
		fprintf(stderr, "%s: %s: no symbols\n",
				prog_name, arg_str);
	fclose(fp);
}

/**
 * parse_args - check for usage errors
 * @argc: count of arguments
 * @argv: pointer to array containing arguments
 * @i: index for argv
 *
 * Return: pointer to file stream, otherwise NULL
 */
FILE *parse_args(int argc, char *argv[], int i)
{
	FILE *fp;
	struct stat sb;

	if (argc == 1)
		argv[1] = "a.out";
	stat(argv[i], &sb);
	if (S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "%s: Warning: '%s' is a directory\n",
				argv[0], argv[i]);
		return (NULL);
	}
	fp = fopen(argv[i], "r+b");
	if (!fp)
	{
		fprintf(stderr, "%s: '%s': No such file\n", argv[0], argv[i]);
		return (NULL);
	}
	return (fp);
}

/**
 * main - entry point
 * @argc: count of arguments
 * @argv: pointer to an array containing arguments
 *
 * Return: 0 on success, otherwise 1
 */
int main(int argc, char *argv[])
{
	FILE *fp;
	int exit_stat = 0, i = 1;

	do {
		fp = parse_args(argc, argv, i);
		if (!fp)
			exit_stat = 1;
		else
			getelf(fp, argv[0], argv[i], &exit_stat);
	} while (++i < argc);
	return (exit_stat);
}
