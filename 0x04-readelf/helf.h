#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>
/* #include <sys/stat.h> */

typedef struct
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
void printentry(hdrs hdr);
void printpshoff(hdrs hdr);
void printflags(hdrs hdr);
void printhdrsize(hdrs hdr);
void printphnum(hdrs hdr);
void printshentsize(hdrs hdr);
void printshnum(hdrs hdr);
void printshstrndx(hdrs hdr);

#endif /* HELF_H */
