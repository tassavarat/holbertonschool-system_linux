#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/**
 * struct hdrs - struct containing 32 and 64 bit ELF header information
 * @hdr32: 32-bit ELF header
 * @hdr64: 64-bit ELF header
 */
typedef struct hdrs
{
	Elf32_Ehdr hdr32;
	Elf64_Ehdr hdr64;
} hdrs;

/* shared */
FILE *parse_args(int argc, char **argv);
void convertmsb(char *type, size_t size);

/* 0-printelfh */
int printelfh(FILE *fp, FILE *fp2, char *arg_str);
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
