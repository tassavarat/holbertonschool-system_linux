#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define IS_32 (hdr->Ehdr64->e_ident[EI_CLASS] == ELFCLASS32)
#define IS_MSB (hdr->Ehdr64->e_ident[EI_DATA] == ELFDATA2MSB)
#define SET_EHDR(x) (IS_32 ? \
		(void *) &(hdr->Ehdr32->x) : (void *) &(hdr->Ehdr64->x))
#define SET_SHDR(x, i) (IS_32 ? \
		(void *) &(hdr->Shdr32[i].x) : (void *) &(hdr->Shdr64[i].x))
#define SET_YHDR(x, i) (IS_32 ? \
		(void *) &(hdr->Sym32[i].x) : (void *) &(hdr->Sym64[i].x))
#define GET_EHDR(x) (IS_32 ? hdr->Ehdr32->x : hdr->Ehdr64->x)
#define GET_SHDR(x, i) (IS_32 ? hdr->Shdr32[i].x : hdr->Shdr64[i].x)
#define GET_YHDR(x, i) (IS_32 ? hdr->Sym32[i].x : hdr->Sym64[i].x)

/**
 *  struct hdrs - contains 32 and 64 bit ELF header information
 * @Ehdr32: 32-bit ELF header
 * @Ehdr64: 64-bit ELF header
 */
typedef struct hdrs
{
	char *addr;
	Elf32_Ehdr *Ehdr32;
	Elf64_Ehdr *Ehdr64;
	int is_32;
	int is_msb;
	Elf32_Shdr *Shdr32;
	Elf64_Shdr *Shdr64;
	Elf32_Sym *Sym32;
	Elf64_Sym *Sym64;
} hdrs;

#endif /* HELF_H */
