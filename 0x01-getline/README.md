# 0x01. C - Static variables, getline

## Learning Objectives
* What are static variables?
* How and when to use them?

## Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
* All your header files should be include guarded
* You are allowed to have up to 6 functions in _getline.c

## Allowed Functions and System Calls
* `read`
* `write`
* `malloc`
* `free`
* `strcpy`
* `strncpy`
* `strcat`
* `strdup`
* `memset`
* `memcpy`

---

### [0. Racing cars](./laps.c)
Write a function that keeps track of the number of laps made by several cars in a race.

* Prototype : `void race_state(int *id, size_t size)`
* `id` is an array of `int` representing the “identifier” of each car.
* `size` is the size of this array
* Each car identifier is unique
* If an identifier is unknown:
	* Create a new car with the number of laps = 0
	* Print `Car X joined the race` followed by a new line (where `X` is the identifier)
* Each time the function is called:
        * The number of laps of each cars listed in `id` must be incremented by 1
        * Print the state of the race:
	    * Header: `Race state:`` followed by a new line
	    * For each car sorted by the identifier: `Car X [Y laps]` (where `X` is the identifier and `Y` the number of laps already done)
* If your function is called with `size = 0`, you must free all allocated memory.

```
julien@ubuntu:~/0x01-getline$ cat 0-main.c
#include "laps.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main()
{

    int ids1[3] = {1, 42, 101};
    int ids2[1] = {11};

    race_state(ids1, 3);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(NULL, 0);
    return (0);
}
julien@ubuntu:~/0x01-getline$ gcc -Wall -Wextra -Werror -pedantic 0-main.c laps.c  -o laps
julien@ubuntu:~/0x01-getline$ ./laps
Car 1 joined the race
Car 42 joined the race
Car 101 joined the race
Race state:
Car 1 [0 laps]
Car 42 [0 laps]
Car 101 [0 laps]
--
Race state:
Car 1 [1 laps]
Car 42 [1 laps]
Car 101 [1 laps]
--
Race state:
Car 1 [2 laps]
Car 42 [2 laps]
Car 101 [2 laps]
--
Car 11 joined the race
Race state:
Car 1 [2 laps]
Car 11 [0 laps]
Car 42 [2 laps]
Car 101 [2 laps]
--
Race state:
Car 1 [3 laps]
Car 11 [0 laps]
Car 42 [3 laps]
Car 101 [3 laps]
--
Race state:
Car 1 [3 laps]
Car 11 [1 laps]
Car 42 [3 laps]
Car 101 [3 laps]
--
Race state:
Car 1 [4 laps]
Car 11 [1 laps]
Car 42 [4 laps]
Car 101 [4 laps]
--
Race state:
Car 1 [4 laps]
Car 11 [2 laps]
Car 42 [4 laps]
Car 101 [4 laps]
--
Race state:
Car 1 [5 laps]
Car 11 [2 laps]
Car 42 [5 laps]
Car 101 [5 laps]
--
Race state:
Car 1 [5 laps]
Car 11 [3 laps]
Car 42 [5 laps]
Car 101 [5 laps]
--
julien@ubuntu:~/0x01-getline$
```

### [1. _getline ](./_getline.c)
Write a function that reads an entire line from a file descriptor.

* Prototype : `char *_getline(const int fd)`
* Where `fd` is the file descriptor to read from
* If there are no more lines to return, or if there is an error, the function should return `NULL`
* The function returns a null-terminated string that does not include the newline character
* Your header file `_getline.h` should define a macro called `READ_SIZE`.
	* This macro defines the number of bytes you will read each time you will call `read`: `read(fd, buffer, READ_SIZE)`
	* You are not allowed to read more or less than `READ_SIZE` bytes at once from fd
	* You are free to pick the value that you want for `READ_SIZE`
* You can assume that `fd` will always be the same

```
julien@ubuntu:~/0x01-getline$ cat 1-main.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
    int fd;
    char *line;

    fd = open("1-main.c", 0);
    while ((line = _getline(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
julien@ubuntu:~/0x01-getline$ gcc -Wall -Wextra -Werror -pedantic 1-main.c _getline.c -o getline
julien@ubuntu:~/0x01-getline$ ./getline
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - entry point.
 *
 * Return: always 0.
 */
#include "_getline.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("1-main.c", 0);
    while ((line = _getline(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
julien@ubuntu:~/0x01-getline$
```

### [2. _getline: multi-fd](./_getline.c)
Handle multiple file descriptors.

* when called with `-1` you should free everything and reset all your static variables

```
julien@ubuntu:~/0x01-getline$ cat 2-main.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
    int fd1, fd2, fd3;
    char *line1;
    char *line2;
    char *line3;
    int i;

    fd1 = open("the_swing", O_RDONLY);
    fd2 = open("man_gcc", O_RDONLY);
    fd3 = open("man_cat", O_RDONLY);
    printf("---------THE SWING (first 5 lines)-----------\n");
    i = 0;
    while ((line1 = _getline(fd1)))
    {
        printf("%s\n", line1);
        free(line1);
        i++;
        if (i == 5)
        {
            break;
        }
    }
    printf("----------MAN GCC (first 5 lines)----------\n");
    i = 0;
    while ((line2 = _getline(fd2)))
    {
        printf("%s\n", line2);
        free(line2);
        i++;
        if (i == 5)
        {
            break;
        }
    }
    printf("-----------MAN CAT (first 5 lines)---------\n");
    i = 0;
    while ((line3 = _getline(fd3)))
    {
        printf("%s\n", line3);
        free(line3);
        i++;
        if (i == 5)
        {
            break;
        }
    }
    printf("---------THE SWING (END)-----------\n");
    while ((line1 = _getline(fd1)))
    {
        printf("%s\n", line1);
        free(line1);
    }
    close(fd1);
    close(fd2);
    close(fd3);
    _getline(-1);
    printf("---------THE SWING (FULL-TEXT)-----------\n");
    fd1 = open("the_swing", O_RDONLY);
    while ((line1 = _getline(fd1)))
    {
        printf("%s\n", line1);
        free(line1);
    }
    close(fd1);
    _getline(-1);
    return (EXIT_SUCCESS);
}
julien@ubuntu:~/0x01-getline$ gcc -Wall -Wextra -pedantic -Werror 2-main.c _getline.c -o getline
julien@ubuntu:~/0x01-getline$ ./getline
---------THE SWING (first 5 lines)-----------
The Swing
BY ROBERT LOUIS STEVENSON
How do you like to go up in a swing,
   Up in the air so blue?
Oh, I do think it the pleasantest thing
----------MAN GCC (first 5 lines)----------
GCC(1)                                 GNU                                 GCC(1)

NAME
       gcc - GNU project C and C++ compiler

-----------MAN CAT (first 5 lines)---------
CAT(1)                            User Commands                            CAT(1)

NAME
       cat - concatenate files and print on the standard output

---------THE SWING (END)-----------
   Ever a child can do!

Up in the air and over the wall,
   Till I can see so wide,
Rivers and trees and cattle and all
   Over the countryside—

Till I look down on the garden green,
   Down on the roof so brown—
Up in the air I go flying again,
   Up in the air and down!again,
---------THE SWING (FULL-TEXT)-----------
The Swing
BY ROBERT LOUIS STEVENSON
How do you like to go up in a swing,
   Up in the air so blue?
Oh, I do think it the pleasantest thing
   Ever a child can do!

Up in the air and over the wall,
   Till I can see so wide,
Rivers and trees and cattle and all
   Over the countryside—

Till I look down on the garden green,
   Down on the roof so brown—
Up in the air I go flying again,
   Up in the air and down!again,
julien@ubuntu:~/0x01-getline$ valgrind ./getline
==4832== Memcheck, a memory error detector
==4832== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==4832== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==4832== Command: ./a.out
==4832==
---------THE SWING (first 5 lines)-----------
The Swing
BY ROBERT LOUIS STEVENSON
How do you like to go up in a swing,
   Up in the air so blue?
Oh, I do think it the pleasantest thing
----------MAN GCC (first 5 lines)----------
GCC(1)                                 GNU                                 GCC(1)

NAME
       gcc - GNU project C and C++ compiler

-----------MAN CAT (first 5 lines)---------
CAT(1)                            User Commands                            CAT(1)

NAME
       cat - concatenate files and print on the standard output

---------THE SWING (END)-----------
   Ever a child can do!

Up in the air and over the wall,
   Till I can see so wide,
Rivers and trees and cattle and all
   Over the countryside—

Till I look down on the garden green,
   Down on the roof so brown—
Up in the air I go flying again,
   Up in the air and down!
---------THE SWING (FULL-TEXT)-----------
The Swing
BY ROBERT LOUIS STEVENSON
How do you like to go up in a swing,
   Up in the air so blue?
Oh, I do think it the pleasantest thing
   Ever a child can do!

Up in the air and over the wall,
   Till I can see so wide,
Rivers and trees and cattle and all
   Over the countryside—

Till I look down on the garden green,
   Down on the roof so brown—
Up in the air I go flying again,
   Up in the air and down!
==4832==
==4832== HEAP SUMMARY:
==4832==     in use at exit: 0 bytes in 0 blocks
==4832==   total heap usage: 84 allocs, 84 frees, 2,320 bytes allocated
==4832==
==4832== All heap blocks were freed -- no leaks are possible
==4832==
==4832== For counts of detected and suppressed errors, rerun with: -v
==4832== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
julien@ubuntu:~/0x01-getline$
```

### [3. _getline: ^@](./_getline.c)
Handle characters `\0` in lines.
```
julien@ubuntu:~/0x01-getline$ cat 100-main.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

#define LINE_LEN 21

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
    int fd;
    char *line;
    int i;

    fd = open("zero", O_RDONLY);
    if (-1 == fd)
    {
        fprintf(stderr, "nop\n");
        return (EXIT_FAILURE);
    }
    while ((line = _getline(fd)))
    {
        for (i = 0; i < LINE_LEN; i++)
        {
            if (i)
            {
                printf(" ");
            }
            printf("%02x", line[i]);
        }
        printf("\n");
        free(line);
    }
    close(fd);
    return (EXIT_SUCCESS);
}
julien@ubuntu:~/0x01-getline$ cat zero
line 1 Holberton.....
line 2 still line 2
line 3 ......School()
julien@ubuntu:~/0x01-getline$ gcc -g -Wall -Wextra -pedantic 100-main.c _getline.c && ./a.out
6c 69 6e 65 20 31 20 48 6f 6c 62 65 72 74 6f 6e 2e 2e 2e 2e 2e
6c 69 6e 65 20 32 20 00 73 74 69 6c 6c 20 6c 69 6e 65 20 32 00
6c 69 6e 65 20 33 20 2e 2e 2e 2e 2e 2e 53 63 68 6f 6f 6c 28 29
julien@ubuntu:~/0x01-getline$
```
