# 0x04. C - ELF: readelf

## Learning  Objectives
* What is the ELF format
* What kind of files are in the ELF format
* What are the different parts that constitute an ELF file
* What information are present in the file header
* What information are present in the sections header table
* What information are present in the program header table
* How to parse an ELF file using C structures

## Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* You are not allowed to have more than 5 functions per file
* All your header files should be include guarded

### Allowed Functions and System Calls
* Unless specified otherwise, you are allowed to use the C standard library
* You’re not allowed to use system(3)
* You’re not allowed to use exec*(2 and 3)

---

### [0. ELF file header]
Write a program that displays the information contained in the ELF file header of an ELF file.

* Usage: 0-hreadelf elf_filename
* Your standard output, error output and status should be the exact same as readelf -W -h

Your makefile must define the rule 0-hreadelf and compile the needed sources to form the executable 0-hreadelf
```
alex@~/0x04-readelf$ make 0-hreadelf
[...]
alex@~/0x04-readelf$ ./0-hreadelf ubuntu64
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x400600
  Start of program headers:          64 (bytes into file)
  Start of section headers:          6936 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 28
alex@~/0x04-readelf$
alex@~/0x04-readelf$ ./0-hreadelf netbsd32
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 02 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - NetBSD
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x80484c0
  Start of program headers:          52 (bytes into file)
  Start of section headers:          2752 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         6
  Size of section headers:           40 (bytes)
  Number of section headers:         24
  Section header string table index: 21
alex@~/0x04-readelf$
alex@~/0x04-readelf$ ./0-hreadelf sparcbigendian32
ELF Header:
  Magic:   7f 45 4c 46 01 02 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, big endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Sparc
  Version:                           0x1
  Entry point address:               0x10d20
  Start of program headers:          52 (bytes into file)
  Start of section headers:          84560 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         6
  Size of section headers:           40 (bytes)
  Number of section headers:         24
  Section header string table index: 23
alex@~/0x04-readelf$
```

### [1. ELF sections' headers]
Write a program that displays the information contained in the ELF sections' headers of an ELF file.

* Usage: 1-hreadelf elf_filename
* Your standard output, error output and status should be the exact same as readelf -W -S

Your makefile must define the rule 1-hreadelf and compile the needed sources to form the executable 1-hreadelf
```
alex@~/0x04-readelf$ make 1-hreadelf
[...]
alex@~/0x04-readelf$ ./1-hreadelf ubuntu64
There are 31 section headers, starting at offset 0x1b18:

Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
  [ 1] .interp           PROGBITS        0000000000400238 000238 00001c 00   A  0   0  1
  [ 2] .note.ABI-tag     NOTE            0000000000400254 000254 000020 00   A  0   0  4
  [ 3] .note.gnu.build-id NOTE            0000000000400274 000274 000024 00   A  0   0  4
  [ 4] .gnu.hash         GNU_HASH        0000000000400298 000298 00001c 00   A  5   0  8
  [ 5] .dynsym           DYNSYM          00000000004002b8 0002b8 0000f0 18   A  6   1  8
  [ 6] .dynstr           STRTAB          00000000004003a8 0003a8 000076 00   A  0   0  1
  [ 7] .gnu.version      VERSYM          000000000040041e 00041e 000014 02   A  5   0  2
  [ 8] .gnu.version_r    VERNEED         0000000000400438 000438 000030 00   A  6   1  8
  [ 9] .rela.dyn         RELA            0000000000400468 000468 000018 18   A  5   0  8
  [10] .rela.plt         RELA            0000000000400480 000480 0000c0 18  AI  5  24  8
  [11] .init             PROGBITS        0000000000400540 000540 00001a 00  AX  0   0  4
  [12] .plt              PROGBITS        0000000000400560 000560 000090 10  AX  0   0 16
  [13] .plt.got          PROGBITS        00000000004005f0 0005f0 000008 00  AX  0   0  8
  [14] .text             PROGBITS        0000000000400600 000600 000382 00  AX  0   0 16
  [15] .fini             PROGBITS        0000000000400984 000984 000009 00  AX  0   0  4
  [16] .rodata           PROGBITS        0000000000400990 000990 000067 00   A  0   0  8
  [17] .eh_frame_hdr     PROGBITS        00000000004009f8 0009f8 000034 00   A  0   0  4
  [18] .eh_frame         PROGBITS        0000000000400a30 000a30 0000f4 00   A  0   0  8
  [19] .init_array       INIT_ARRAY      0000000000600e10 000e10 000008 00  WA  0   0  8
  [20] .fini_array       FINI_ARRAY      0000000000600e18 000e18 000008 00  WA  0   0  8
  [21] .jcr              PROGBITS        0000000000600e20 000e20 000008 00  WA  0   0  8
  [22] .dynamic          DYNAMIC         0000000000600e28 000e28 0001d0 10  WA  6   0  8
  [23] .got              PROGBITS        0000000000600ff8 000ff8 000008 08  WA  0   0  8
  [24] .got.plt          PROGBITS        0000000000601000 001000 000058 08  WA  0   0  8
  [25] .data             PROGBITS        0000000000601058 001058 000010 00  WA  0   0  8
  [26] .bss              NOBITS          0000000000601068 001068 000008 00  WA  0   0  1
  [27] .comment          PROGBITS        0000000000000000 001068 000034 01  MS  0   0  1
  [28] .shstrtab         STRTAB          0000000000000000 001a06 00010c 00      0   0  1
  [29] .symtab           SYMTAB          0000000000000000 0010a0 0006d8 18     30  47  8
  [30] .strtab           STRTAB          0000000000000000 001778 00028e 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
alex@~/0x04-readelf$
alex@~/0x04-readelf$ ./1-hreadelf netbsd32
There are 24 section headers, starting at offset 0xac0:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .interp           PROGBITS        080480f4 0000f4 000017 00   A  0   0  1
  [ 2] .note.netbsd.ident NOTE            0804810c 00010c 000034 00   A  0   0  4
  [ 3] .hash             HASH            08048140 000140 0000a0 04   A  4   0  4
  [ 4] .dynsym           DYNSYM          080481e0 0001e0 000150 10   A  5   1  4
  [ 5] .dynstr           STRTAB          08048330 000330 0000bf 00   A  0   0  1
  [ 6] .rel.got          REL             080483f0 0003f0 000030 08   A  4  16  4
  [ 7] .rel.plt          REL             08048420 000420 000020 08   A  4   9  4
  [ 8] .init             PROGBITS        08048440 000440 000030 00  AX  0   0  4
  [ 9] .plt              PROGBITS        08048470 000470 000050 04  AX  0   0  4
  [10] .text             PROGBITS        080484c0 0004c0 000304 00  AX  0   0  4
  [11] .fini             PROGBITS        080487c4 0007c4 00001d 00  AX  0   0  4
  [12] .rodata           PROGBITS        08048800 000800 0000a7 00   A  0   0 32
  [13] .data             PROGBITS        080498a8 0008a8 000014 00  WA  0   0  4
  [14] .ctors            PROGBITS        080498bc 0008bc 000008 00  WA  0   0  4
  [15] .dtors            PROGBITS        080498c4 0008c4 000008 00  WA  0   0  4
  [16] .got              PROGBITS        080498cc 0008cc 000034 04  WA  0   0  4
  [17] .dynamic          DYNAMIC         08049900 000900 000088 08  WA  5   0  4
  [18] .bss              NOBITS          08049988 000988 00000c 00  WA  0   0  4
  [19] .note             NOTE            08049994 000988 000050 00      0   0  1
  [20] .ident            PROGBITS        080499e4 0009d8 000035 00      0   0  1
  [21] .shstrtab         STRTAB          00000000 000a0d 0000b1 00      0   0  1
  [22] .symtab           SYMTAB          00000000 000e80 000390 10     23  27  4
  [23] .strtab           STRTAB          00000000 001210 000125 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
alex@~/0x04-readelf$
alex@~/0x04-readelf$ ./1-hreadelf sparcbigendian32
There are 24 section headers, starting at offset 0x14a50:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .interp           PROGBITS        000100f4 0000f4 000013 00   A  0   0  1
  [ 2] .note.ABI-tag     NOTE            00010108 000108 000020 00   A  0   0  4
  [ 3] .hash             HASH            00010128 000128 00019c 04   A  4   0  4
  [ 4] .dynsym           DYNSYM          000102c4 0002c4 000400 10   A  5   1  4
  [ 5] .dynstr           STRTAB          000106c4 0006c4 00025a 00   A  0   0  1
  [ 6] .gnu.version      VERSYM          0001091e 00091e 000080 02   A  4   0  2
  [ 7] .gnu.version_r    VERNEED         000109a0 0009a0 000060 00   A  5   2  4
  [ 8] .rela.dyn         RELA            00010a00 000a00 000054 0c   A  4   0  4
  [ 9] .rela.plt         RELA            00010a54 000a54 00027c 0c   A  4  20  4
  [10] .init             PROGBITS        00010ce0 000ce0 000038 00  AX  0   0 32
  [11] .text             PROGBITS        00010d20 000d20 01226c 00  AX  0   0 32
  [12] .fini             PROGBITS        00022fa0 012fa0 000030 00  AX  0   0 32
  [13] .rodata           PROGBITS        00022fd0 012fd0 0013a0 00   A  0   0  8
  [14] .data             PROGBITS        00034370 014370 000270 00  WA  0   0  4
  [15] .eh_frame         PROGBITS        000345e0 0145e0 000004 00   A  0   0  4
  [16] .dynamic          DYNAMIC         000345e4 0145e4 0000d0 08  WA  5   0  4
  [17] .ctors            PROGBITS        000346b4 0146b4 000008 00  WA  0   0  4
  [18] .dtors            PROGBITS        000346bc 0146bc 000008 00  WA  0   0  4
  [19] .jcr              PROGBITS        000346c4 0146c4 000004 00  WA  0   0  4
  [20] .plt              PROGBITS        000346c8 0146c8 0002b0 0c WAX  0   0  4
  [21] .got              PROGBITS        00034978 014978 000020 04  WA  0   0  4
  [22] .bss              NOBITS          00034998 014998 0442e0 00  WA  0   0  8
  [23] .shstrtab         STRTAB          00000000 014998 0000b7 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
alex@~/0x04-readelf$
```

### [2. ELF program headers]
Write a program that displays the information contained in the ELF program headers of an ELF file.

* Usage: 2-hreadelf elf_filename
* Your standard output, error output and status should be the exact same as readelf -W -l

Your makefile must define the rule 2-hreadelf and compile the needed sources to form the executable 2-hreadelf
```
alex@~/0x04-readelf$ make 2-hreadelf
[...]
alex@~/0x04-readelf$ ./2-hreadelf ubuntu64

Elf file type is EXEC (Executable file)
Entry point 0x400600
There are 9 program headers, starting at offset 64

Program Headers:
  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align
  PHDR           0x000040 0x0000000000400040 0x0000000000400040 0x0001f8 0x0001f8 R E 0x8
  INTERP         0x000238 0x0000000000400238 0x0000000000400238 0x00001c 0x00001c R   0x1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x000000 0x0000000000400000 0x0000000000400000 0x000b24 0x000b24 R E 0x200000
  LOAD           0x000e10 0x0000000000600e10 0x0000000000600e10 0x000258 0x000260 RW  0x200000
  DYNAMIC        0x000e28 0x0000000000600e28 0x0000000000600e28 0x0001d0 0x0001d0 RW  0x8
  NOTE           0x000254 0x0000000000400254 0x0000000000400254 0x000044 0x000044 R   0x4
  GNU_EH_FRAME   0x0009f8 0x00000000004009f8 0x00000000004009f8 0x000034 0x000034 R   0x4
  GNU_STACK      0x000000 0x0000000000000000 0x0000000000000000 0x000000 0x000000 RW  0x10
  GNU_RELRO      0x000e10 0x0000000000600e10 0x0000000000600e10 0x0001f0 0x0001f0 R   0x1

 Section to Segment mapping:
  Segment Sections...
   00
   01     .interp
   02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .plt.got .text .fini .rodata .eh_frame_hdr .eh_frame
   03     .init_array .fini_array .jcr .dynamic .got .got.plt .data .bss
   04     .dynamic
   05     .note.ABI-tag .note.gnu.build-id
   06     .eh_frame_hdr
   07
   08     .init_array .fini_array .jcr .dynamic .got
alex@~/0x04-readelf$
alex@~/0x04-readelf$ ./2-hreadelf netbsd32

Elf file type is EXEC (Executable file)
Entry point 0x80484c0
There are 6 program headers, starting at offset 52

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  PHDR           0x000034 0x08048034 0x08048034 0x000c0 0x000c0 R E 0x4
  INTERP         0x0000f4 0x080480f4 0x080480f4 0x00017 0x00017 R   0x1
      [Requesting program interpreter: /usr/libexec/ld.elf_so]
  LOAD           0x000000 0x08048000 0x08048000 0x008a7 0x008a7 R E 0x1000
  LOAD           0x0008a8 0x080498a8 0x080498a8 0x000e0 0x000ec RW  0x1000
  DYNAMIC        0x000900 0x08049900 0x08049900 0x00088 0x00088 RW  0x4
  NOTE           0x00010c 0x0804810c 0x0804810c 0x00034 0x00034 R   0x4

 Section to Segment mapping:
  Segment Sections...
   00
   01     .interp
   02     .interp .note.netbsd.ident .hash .dynsym .dynstr .rel.got .rel.plt .init .plt .text .fini .rodata
   03     .data .ctors .dtors .got .dynamic .bss
   04     .dynamic
   05     .note.netbsd.ident
alex@~/0x04-readelf$
alex@~/0x04-readelf$ ./2-hreadelf sparcbigendian32

Elf file type is EXEC (Executable file)
Entry point 0x10d20
There are 6 program headers, starting at offset 52

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  PHDR           0x000034 0x00010034 0x00010034 0x000c0 0x000c0 R E 0x4
  INTERP         0x0000f4 0x000100f4 0x000100f4 0x00013 0x00013 R   0x1
      [Requesting program interpreter: /lib/ld-linux.so.2]
  LOAD           0x000000 0x00010000 0x00010000 0x14370 0x14370 R E 0x10000
  LOAD           0x014370 0x00034370 0x00034370 0x00628 0x44908 RWE 0x10000
  DYNAMIC        0x0145e4 0x000345e4 0x000345e4 0x000d0 0x000d0 RW  0x4
  NOTE           0x000108 0x00010108 0x00010108 0x00020 0x00020 R   0x4

 Section to Segment mapping:
  Segment Sections...
   00
   01     .interp
   02     .interp .note.ABI-tag .hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .text .fini .rodata
   03     .data .eh_frame .dynamic .ctors .dtors .jcr .plt .got .bss
   04     .dynamic
   05     .note.ABI-tag
alex@~/0x04-readelf$
```
