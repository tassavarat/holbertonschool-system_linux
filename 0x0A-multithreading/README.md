# 0x0A. Multithreading

## Learning Objectives
* What is a thread
* What are the differences between a thread and a process
* What is the difference between Concurrency and Parallelism
* How to create a thread
* How to properly exit a thread
* How to handle mutual execution
* What is a deadlock
* What is a race condition

## Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
* You are not allowed to have more than 5 functions per file
* The prototypes of all your functions should be included in your header file called multithreading.h
* Don’t forget to push your header files
* All your header files should be include guarded
* You are allowed to use global variables
* You are allowed to use static functions and variables

---

### [0. Thread entry point](./0-thread_entry.c)
Write a function that will serve as the entry point to a new thread.
* Prototype: `void *thread_entry(void *arg);`, where:
	* `arg` holds the address of a string that must be printed and followed by a new line.
* Make sure to respect the order in which strings are printed out in the following example:
```
alex@~/0x0A-multithreading$ cat 0-main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, &thread_entry, "Holberton School");

    sleep(1);
    printf("Created thread ID -> %lu\n", tid);

    thread_entry("C is fun");
    printf("Should not be printed\n");
    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 0-main.c 0-thread_entry.c -o 0-thread_entry -pthread
alex@~/0x0A-multithreading$ ./0-thread_entry
Holberton School
Created thread ID -> 139851772159744
C is fun
alex@~/0x0A-multithreading$
```

### [1. Thread Logger](./1-tprintf.c)
Write a function that uses the `printf` family to print out a given formatted string.
* Prototype: `int tprintf(char const *format, ...);`
* The output must be preceded by the calling thread ID, as the following output shows.
```
alex@~/0x0A-multithreading$ cat 1-main.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused))void *arg)
{
    tprintf("Hello from thread\n");
    return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, &_thread_entry, NULL);
    pthread_join(tid, NULL);

    tprintf("Hello from main thread\n");

    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 1-main.c 1-tprintf.c -o 1-tprintf -pthread
alex@~/0x0A-multithreading$ ./1-tprintf
[140095003338496] Hello from thread
[140095011714880] Hello from main thread
alex@~/0x0A-multithreading$ ./1-tprintf
[139794647717632] Hello from thread
[139794656094016] Hello from main thread
alex@~/0x0A-multithreading$
```
