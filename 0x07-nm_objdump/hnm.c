#include "helf.h"

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

void sym(hdrs *hdr)
{
	int i;
	size_t j, sym_size;
	char *str_table;

	for (i = 0; i < GET_EHDR(e_shnum); ++i)
		if (GET_SHDR(sh_type, i) == SHT_SYMTAB)
			break;
	hdr->Sym32 = (Elf32_Sym *) &hdr->addr[GET_SHDR(sh_offset, i)];
	hdr->Sym64 = (Elf64_Sym *) &hdr->addr[GET_SHDR(sh_offset, i)];
	str_table = &hdr->addr[GET_SHDR(sh_offset, i + 1)];
	/* printf("sizeof st_value 32 %lu\n", sizeof(hdr->Sym32->st_value)); */
	/* printf("sizeof st_value 64 %lu\n", sizeof(hdr->Sym64->st_value)); */
	/* printf("sizeof macro %lu\n", SYM_SIZE(st_value, i)); */
	/* printf("sizeof st_info 32 %lu\n", sizeof(hdr->Sym32->st_info)); */
	/* printf("sizeof st_info 64 %lu\n", sizeof(hdr->Sym64->st_info)); */
	/* printf("sizeof macro %lu\n", SYM_SIZE(st_info, i)); */
	/* printf("sizeof st_name 32 %lu\n", sizeof(hdr->Sym32->st_name)); */
	/* printf("sizeof st_name 64 %lu\n", sizeof(hdr->Sym64->st_name)); */
	/* printf("sizeof macro %lu\n", SYM_SIZE(st_name, i)); */
	/* printf("sh_size\t%lu\n", GET_SHDR(sh_size, i)); */
	/* printf("sh_entsize\t%lu\n", GET_SHDR(sh_entsize, i)); */
	sym_size = GET_SHDR(sh_size, i) / GET_SHDR(sh_entsize, i);
	for (j = 1; j < sym_size; ++j)
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
		printf("%0*lx %s\n", IS_32 ? 8 : 16, GET_SYM(st_value, j),
				&str_table[GET_SYM(st_name, j)]);
	}
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
	/* printf("sizeof sh_type 32 %lu\n", sizeof(hdr->Shdr32->sh_type)); */
	/* printf("sizeof sh_type 64 %lu\n", sizeof(hdr->Shdr64->sh_type)); */
	/* printf("sizeof macro %lu\n", SHDR_SIZE(sh_type, i)); */
	/* printf("sizeof sh_offset 32 %lu\n", sizeof(hdr->Shdr32->sh_offset)); */
	/* printf("sizeof sh_offset 64 %lu\n", sizeof(hdr->Shdr64->sh_offset)); */
	/* printf("sizeof macro %lu\n", SHDR_SIZE(sh_offset, i)); */
	/* printf("sizeof sh_size 32 %lu\n", sizeof(hdr->Shdr32->sh_size)); */
	/* printf("sizeof sh_size 64 %lu\n", sizeof(hdr->Shdr64->sh_size)); */
	/* printf("sizeof macro %lu\n", SHDR_SIZE(sh_size, i)); */
	/* printf("sizeof sh_entsize 32 %lu\n", sizeof(hdr->Shdr32->sh_entsize)); */
	/* printf("sizeof sh_entsize 64 %lu\n", sizeof(hdr->Shdr64->sh_entsize)); */
	/* printf("sizeof macro %lu\n", SHDR_SIZE(sh_entsize, i)); */
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
	/* printf("sizeof e_shoff 32 %lu\n", sizeof(hdr->Ehdr32->e_shoff)); */
	/* printf("sizeof e_shoff 64 %lu\n", sizeof(hdr->Ehdr64->e_shoff)); */
	/* printf("sizeof macro %lu\n", EHDR_SIZE(e_shoff)); */
	/* printf("sizeof e_shentsize 32 %lu\n", sizeof(hdr->Ehdr32->e_shentsize)); */
	/* printf("sizeof e_shentsize 64 %lu\n", sizeof(hdr->Ehdr64->e_shentsize)); */
	/* printf("sizeof macro %lu\n", EHDR_SIZE(e_shentsize)); */
	/* printf("sizeof e_shnum 32 %lu\n", sizeof(hdr->Ehdr32->e_shnum)); */
	/* printf("sizeof e_shnum 64 %lu\n", sizeof(hdr->Ehdr64->e_shnum)); */
	/* printf("sizeof macro %lu\n", EHDR_SIZE(e_shnum)); */
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
	{
		perror(NULL);
		*exit_stat = 1;
		goto out;
	}
	hdr.addr = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
			fileno(fp), 0);
	/* check errors */
	init_ehdr(&hdr);
	if (memcmp(hdr.Ehdr64->e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: %s: file format not recognized\n",
				prog_name, arg_str);
		*exit_stat = 1;
		goto out;
	}
	init_shdr(&hdr);
	sym(&hdr);
	puts("No error");
out:
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
