#include "helf.h"

static int is_32;
static int is_msb;

void printoffset(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Off offset32 = hdr.Shdr32.sh_offset;
	Elf64_Off offset64 = hdr.Shdr64.sh_offset;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &offset32, sizeof(offset32));
		printf("offset %#x:\n\n", offset32);
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &offset64, sizeof(offset64));
		printf("offset %#lx:\n\n", offset64);
	}
}

int shnum(hdrs hdr, int is_32, int is_msb)
{
	Elf32_Half shnum32 = hdr.Ehdr32.e_shnum;
	Elf64_Half shnum64 = hdr.Ehdr64.e_shnum;

	if (is_32)
	{
		if (is_msb)
			convertmsb((char *) &shnum32, sizeof(shnum32));
		return (shnum32);
	}
	else
	{
		if (is_msb)
			convertmsb((char *) &shnum64, sizeof(shnum64));
		return (shnum64);
	}
}

int checkbitend(hdrs hdr, char *arg_str)
{
	if (hdr.Ehdr64.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		fprintf(stderr, "%s: Error: Invalid class\n", arg_str);
		goto out;
	}
	if (hdr.Ehdr64.e_ident[EI_DATA] == ELFDATANONE)
	{
		fprintf(stderr, "%s: Error: Invalid data encoding\n", arg_str);
out:
		return (1);
	}
	if (hdr.Ehdr64.e_ident[EI_CLASS] == ELFCLASS32)
		is_32 = 1;
	if (hdr.Ehdr64.e_ident[EI_DATA] == ELFDATA2MSB)
		is_msb = 1;
	return (0);
}

/**
 * printelfh - prints elf header
 * @fp: pointer to file stream
 * @arg_str: string containing name of program
 *
 * Return: 0 on success, otherwise 1
 */
int printelfsh(FILE *fp, char *arg_str)
{
	hdrs hdr;
	int exit_stat;

	fread(&hdr.Ehdr64, 1, sizeof(hdr.Ehdr64), fp);
	rewind(fp);
	fread(&hdr.Ehdr32, 1, sizeof(hdr.Ehdr32), fp);
	rewind(fp);
	fread(&hdr.Shdr64, 1, sizeof(hdr.Shdr64), fp);
	rewind(fp);
	fread(&hdr.Shdr32, 1, sizeof(hdr.Shdr32), fp);
	if (memcmp(hdr.Ehdr64.e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: %s%s\n", arg_str,
				"Error: Not an ELF file - ",
				"it has the wrong magic bytes at the start");
		exit_stat = 1;
		goto out;
	}
	exit_stat = checkbitend(hdr, arg_str);
	if (exit_stat)
		goto out;
	printf("There are %i section headers, starting at ",
			shnum(hdr, is_32, is_msb));
	printoffset(hdr, is_32, is_msb);
	/* puts("ELF Header:"); */
	/* printmag(hdr); */
	/* exit_stat = printclass(hdr, arg_str); */
	/* if (exit_stat) */
	/* 	goto out; */
	/* exit_stat = printdata(hdr, arg_str); */
	/* if (exit_stat) */
	/* 	goto out; */
	/* exit_stat = printversion(hdr, arg_str); */
	/* if (exit_stat) */
	/* 	goto out; */
	/* printelfhwrapper(hdr); */
	exit_stat = 0;
out:
	fclose(fp);
	if (exit_stat)
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	FILE *fp;
	int exit_stat;

	fp = parse_args(argc, argv);
	if (!fp)
		return (1);
	exit_stat = printelfsh(fp, *argv);
	return (exit_stat);
}
