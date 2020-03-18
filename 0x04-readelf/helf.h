#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>

/* printelfh */
int printelfh(FILE *fp, char *arg_str);
void printosabi(Elf64_Ehdr hdr);

#endif /* HELF_H */
