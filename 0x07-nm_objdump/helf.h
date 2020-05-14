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
#define GET_SYM(x, i) (IS_32 ? hdr->Sym32[i].x : hdr->Sym64[i].x)
#define EHDR_SIZE(x) (IS_32 ? sizeof(hdr->Ehdr32->x) : sizeof(hdr->Ehdr64->x))
#define SHDR_SIZE(x, i) (IS_32 ? \
		sizeof(hdr->Shdr32[i].x) : sizeof(hdr->Shdr64[i].x))
#define SYM_SIZE(x, i) (IS_32 ? \
		sizeof(hdr->Sym32[i].x) : sizeof(hdr->Sym64[i].x))
#define ELFN_ST_BIND (IS_32 ? ELF32_ST_BIND(hdr->Sym32[i].st_info) : \
		ELF64_ST_BIND(hdr->Sym64[i].st_info))
#define ELFN_ST_TYPE (IS_32 ? ELF32_ST_TYPE(hdr->Sym32[i].st_info) : \
		ELF64_ST_TYPE(hdr->Sym64[i].st_info))

/**
 * struct hdrs - contains 32 and 64 bit ELF header information
 * @addr: pointer to mapped area
 * @Ehdr32: 32-bit ELF header
 * @Ehdr64: 64-bit ELF header
 * @is_32: specifies if ELF file is 32-bit
 * @is_msb: specifies if ELF file is big-endian
 * @Shdr32: 32-bit ELF section header
 * @Shdr64: 64-bit ELF section header
 * @Sym32: 32-bit ELF symbol table
 * @Sym64: 64-bit ELF symbol table
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

/* hnm */
void conv_msb(char *ptr, size_t size);

/* elf */
void init_ehdr(hdrs *hdr);
void init_shdr(hdrs *hdr);
int sym(hdrs *hdr);

#endif /* HELF_H */
