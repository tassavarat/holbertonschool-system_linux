#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>

/* printelfh */
int printelfh(FILE *fp, char *arg_str);
int printversion(Elf64_Ehdr hdr, char *arg_str);
void printosabi(Elf64_Ehdr hdr);
void printtype(Elf64_Ehdr hdr);
void printmachine(Elf64_Ehdr hdr);
void printfileversion(Elf64_Ehdr hdr);
void printentry(Elf64_Ehdr hdr);
void printpshoff(Elf64_Ehdr hdr);
void printflags(Elf64_Ehdr hdr);
void printhdrsize(Elf64_Ehdr hdr);
void printphnum(Elf64_Ehdr hdr);
void printshentsize(Elf64_Ehdr hdr);
void printshnum(Elf64_Ehdr hdr);
void printshstrndx(Elf64_Ehdr hdr);

#endif /* HELF_H */
