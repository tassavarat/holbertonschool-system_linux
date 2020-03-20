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

/* printelfh */
int printelfh(FILE *fp, FILE *fp2, char *arg_str);
int printversion(hdrs hdr, char *arg_str);
void printosabi(hdrs hdr);
void printtype(hdrs hdr);
void printmachine(hdrs hdr);
void printfileversion(hdrs hdr);
void printentry(hdrs hdr, int is_32);
void printpshoff(hdrs hdr, int is_32);
void printflags(hdrs hdr, int is_32);
void printhdrsize(hdrs hdr, int is_32);
void printphnum(hdrs hdr, int is_32);
void printshentsize(hdrs hdr, int is_32);
void printshnum(hdrs hdr, int is_32);
void printshstrndx(hdrs hdr, int is_32);

#endif /* HELF_H */
