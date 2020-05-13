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
	str_table = &hdr->addr[GET_SHDR(sh_offset, i + 1)];
	/* printf("%s\n", str_table + 1); */
	hdr->Sym32 = (Elf32_Sym *) &hdr->addr[GET_SHDR(sh_offset, i)];
	hdr->Sym64 = (Elf64_Sym *) &hdr->addr[GET_SHDR(sh_offset, i)];
	sym_size = GET_SHDR(sh_size, i) / GET_SHDR(sh_entsize, i);
	/* printf("%lu\n", sym_size); */
	for (j = 1; j < sym_size; ++j)
	{
		if (IS_MSB)
		{
			conv_msb((char *) SET_YHDR(st_value, j),
					sizeof(GET_YHDR(st_value, j)));
			conv_msb((char *) SET_YHDR(st_info, j),
					sizeof(GET_YHDR(st_info, j)));
			conv_msb((char *) SET_YHDR(st_name, j),
					sizeof(GET_YHDR(st_name, j)));
		}
		if ((GET_YHDR(st_info, j) & 0xf) == STT_SECTION || (GET_YHDR(st_info, j) & 0xf) == STT_FILE)
			continue;
		printf("%0*lx %s\n", IS_32 ? 8 : 16, GET_YHDR(st_value, j),
				&str_table[GET_YHDR(st_name, j)]);
	}
}

void init_shdr(hdrs *hdr)
{
	int i;

	hdr->Shdr32 = (Elf32_Shdr *) &hdr->addr[GET_EHDR(e_shoff)];
	hdr->Shdr64 = (Elf64_Shdr *) &hdr->addr[GET_EHDR(e_shoff)];
	if (IS_MSB)
		for (i = 0; i < GET_EHDR(e_shnum); ++i)
		{
			printf("i is %i\n", i);
			conv_msb((char *) SET_SHDR(sh_type, i),
					sizeof(GET_SHDR(sh_type, i)));
			conv_msb((char *) SET_SHDR(sh_offset, i),
					sizeof(GET_SHDR(sh_offset, i)));
			conv_msb((char *) SET_SHDR(sh_size, i),
					sizeof(GET_SHDR(sh_size, i)));
			conv_msb((char *) SET_SHDR(sh_entsize, i),
					sizeof(GET_SHDR(sh_entsize, i)));
		}
}

/**
 * checkbitend - checks system bit and endian
 * @hdr: struct containing elf header information
 * @arg_str: string containing name of program
 */
void init_ehdr(hdrs *hdr)
{
	hdr->Ehdr32 = (Elf32_Ehdr *) hdr->addr;
	hdr->Ehdr64 = (Elf64_Ehdr *) hdr->addr;
	if (IS_MSB)
	{
		printf("is_32 %i\n", IS_32);
		conv_msb((char *) SET_EHDR(e_shoff),
				sizeof(GET_EHDR(e_shoff)));
		conv_msb((char *) SET_EHDR(e_shentsize),
				sizeof(GET_EHDR(e_shentsize)));
		conv_msb((char *) SET_EHDR(e_shnum),
				sizeof(GET_EHDR(e_shnum)));
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
	hdr.addr = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fileno(fp), 0);
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
