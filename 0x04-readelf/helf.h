#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/**
 * struct hdrs - struct containing 32 and 64 bit ELF header information
 * @Ehdr32: 32-bit ELF header
 * @Ehdr64: 64-bit ELF header
 * @Shdr32: 32-bit ELF section header
 * @Shdr64: 64-bit ELF section header
 */
typedef struct hdrs
{
	Elf32_Ehdr Ehdr32;
	Elf64_Ehdr Ehdr64;
	Elf32_Shdr Shdr32;
	Elf64_Shdr Shdr64;
} hdrs;

/* shared */
FILE *parse_args(int argc, char **argv);
void convertmsb(char *type, size_t size);

/* 0-printelfh */
int printelfh(FILE *fp, char *arg_str);
int printversion(hdrs hdr, char *arg_str);
void printosabi(hdrs hdr);
void printtype(hdrs hdr, int is_msb);
void printmachine(hdrs hdr, int is_msb);
void printfileversion(hdrs hdr, int is_msb);
void printentry(hdrs hdr, int is_32, int is_msb);
void printpshoff(hdrs hdr, int is_32, int is_msb);
void printflags(hdrs hdr, int is_32, int is_msb);
void printhdrsize(hdrs hdr, int is_32, int is_msb);
void printphnum(hdrs hdr, int is_32, int is_msb);
void printshentsize(hdrs hdr, int is_32, int is_msb);
void printshnum(hdrs hdr, int is_32, int is_msb);
void printshstrndx(hdrs hdr, int is_32, int is_msb);

#endif /* HELF_H */
