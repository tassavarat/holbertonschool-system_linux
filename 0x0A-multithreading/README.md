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
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 1-main.c 1-tprintf.c -o 1-tprintf -pthread
alex@~/0x0A-multithreading$ ./1-tprintf
[140095003338496] Hello from thread
[140095011714880] Hello from main thread
alex@~/0x0A-multithreading$ ./1-tprintf
[139794647717632] Hello from thread
[139794656094016] Hello from main thread
alex@~/0x0A-multithreading$
```

### [2. Blur portion of an image](./10-blur_portion.c)
Write a method that blurs a portion of an image using a Gaussian blur.

* Prototype: `void blur_portion(blur_portion_t const *portion);`, where:
	* `portion` points to a data structure described in the project requirements

```
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 10-main.c 10-blur_portion.c -o 10-blur_portion
alex@~/0x0A-multithreading$ ./10-blur_portion images/car.pbm images/kernel_0.knl
Image size -> 960 * 540
Kernel size -> 5
alex@~/0x0A-multithreading$
```

### [3. Blur entire image](./11-blur_image.c)
Write a method that blurs the entirety of an image using a Gaussian blur.

* Prototype: `void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel);`, where:
	* `img_blur` holds the address at which the blured image is stored,
	* `img` points to the source image,
	* `kernel` points to the convolution kernel to use
* You will have to use threads in order to blur the full image.
* Each thread will blur a portion of the image.
* You are free to use as many threads as you want. Keep in mind that too many threads can make your program inefficient.
* You are free to divide the source image in portions of your choice.
* The main goal of this task is to demonstrate that using threads make the process faster.

```
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 11-main.c 11-blur_image.c 10-blur_portion.c -o 11-blur_image -pthread
alex@~/0x0A-multithreading$ time ./11-blur_image images/car.pbm images/kernel_0.knl
Image size -> 960 * 540
Kernel size -> 5

real    0m0.143s
user    0m0.197s
sys 0m0.076s
alex@~/0x0A-multithreading$
```

### [4. Thread logger v2](./20-tprintf.c)
Write a function that uses the `printf` family to print out a given formatted string.

This time, you will also have to use a `mutex` to avoid race conditions. As you know, a mutex needs to be initialized, and destroyed, but we don’t want to have to do that ourselves in our `main.c` program. Please read about [Constructors and Destructors](https://intranet.hbtn.io/rltoken/NIY4q_RrLXWTzaHN2wVcqg) with GCC and it should all make sense :).

* Prototype: `int tprintf(char const *format, ...);`
* The output must be preceded by the calling thread ID, as the following output shows.
* Tip: You are allowed to use global variables

NOTE: In the following example, we first compile with our first version of `tprintf` to show the consequence of the race condition.

```
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 1-tprintf.c -o 20-tprintf -pthread
alex@~/0x0A-multithreading$ ./20-tprintf
[139996670035712] [139996678428416] [139996686821120] [139996695197504] Hello from thread
[139996644857600] Hello from thread
[139996628072192] Hello from thread
[139996619679488] Hello from thread
Hello from main thread
Hello from thread
Hello from thread
[139996611286784] Hello from thread
[139996661643008] Hello from thread
[139996636464896] Hello from thread
[139996653250304] Hello from thread
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 20-tprintf.c -o 20-tprintf -pthread
alex@~/0x0A-multithreading$ ./20-tprintf
[140146877490944] Hello from thread
[140146852312832] Hello from thread
[140146843920128] Hello from thread
[140146860705536] Hello from thread
[140146835527424] Hello from thread
[140146869098240] Hello from thread
[140146818742016] Hello from thread
[140146885867328] Hello from main thread
[140146810349312] Hello from thread
[140146801956608] Hello from thread
[140146827134720] Hello from thread
alex@~/0x0A-multithreading$
```

### [5. Number to prime factors](./21-prime_factors.c)
Write a function that factorizes a number into a list of prime factors.

* Prototype: `list_t *prime_factors(char const *s);`, where
	* `s` is the string representation of the number to factorize.
	* This number will be positive and fit into an `unsigned long`
* Your code will be compiled with the file `list.c`
	* [list.h](https://intranet.hbtn.io/rltoken/1tXdlAoHScAbpO2KSd6qnQ)
	* [list.c](https://holbertonintranet.s3.amazonaws.com/uploads/text/2020/6/876fd3ce1c3a690faa56139f88efd28a0561fbf9.c?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIARDDGGGOUWMNL5ANN%2F20200707%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20200707T095805Z&X-Amz-Expires=345600&X-Amz-SignedHeaders=host&X-Amz-Signature=2ab2a74f1bd5567b10bc01bd2c17b3b99f87d3dfb544cc4da3e00efaff75448d)
* NOTE: This task does not require multithreading, and will not be linked to the pthread library.

```
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 21-main.c 21-prime_factors.c list.c -o 21-prime_factors
alex@~/0x0A-multithreading$ ./21-prime_factors 745 872346 79283472974
745 = 5 * 149
872346 = 2 * 3 * 145391
79283472974 = 2 * 757 * 52366891
alex@~/0x0A-multithreading$ ./21-prime_factors 1048576
1048576 = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
alex@~/0x0A-multithreading$ ./21-prime_factors 18446744073709551612 18446744073709551609 18446744073709551608
18446744073709551612 = 2 * 2 * 3 * 715827883 * 2147483647
18446744073709551609 = 3 * 3 * 818923289 * 2502845209
18446744073709551608 = 2 * 2 * 2 * 2305843009213693951
alex@~/0x0A-multithreading$
```

### [6. Number to prime factors v2](./22-prime_factors.c)
The goal of this task is to reproduce the previous task, and to improve it using a thread pool. The tread pool will have for purpose to execute a list of tasks.

For this task, you will have to write 3 functions (all in the same file):

* Create task
	* Prototype: `task_t *create_task(task_entry_t entry, void *param);`, where
		* `entry` is a pointer to the entry function of the task,
		* `param` is the parameter that will later be passed to the entry function
	* This function must return a pointer to the created task structure

* Destroy task
	* Prototype: `void destroy_task(task_t *task);`, where
		* `task` is a pointer to the task to destroy

* Execute task list - Thread entry
	* Prototype: `void *exec_tasks(list_t const *tasks);`, where
		* `tasks` is a pointer to the list of tasks to be executed
	* This function serves as a thread entry
	* This function can safely return NULL as its return value will not be retrieved
	* This function must go through the list of tasks and execute them, but there’s a challenge:
        	* Multiple thread will be going through the list of tasks, and a task must only be executed once
    	* You must use `tprintf` to print when a task is started, and completed

Structures
```
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 22-main.c 22-prime_factors.c 21-prime_factors.c list.c 20-tprintf.c -o 22-prime_factors -pthread
alex@~/0x0A-multithreading$ ./22-prime_factors 234 23456 908345 9803475893 389475 9384 7538 4753876348956746 4985 39485734 9587398 7938475839 324 3453450
Executing 14 tasks on 8 threads
[139770218567424] [00] Started
[139770218567424] [00] Success
[139770218567424] [08] Started
[139770218567424] [08] Success
[139770218567424] [09] Started
[139770218567424] [09] Success
[139770218567424] [10] Started
[139770218567424] [10] Success
[139770218567424] [11] Started
[139770218567424] [11] Success
[139770218567424] [12] Started
[139770218567424] [12] Success
[139770218567424] [13] Started
[139770218567424] [13] Success
[139770159818496] [07] Started
[139770159818496] [07] Success
[139770201782016] [02] Started
[139770201782016] [02] Success
[139770184996608] [04] Started
[139770184996608] [04] Success
[139770168211200] [06] Started
[139770168211200] [06] Success
[139770193389312] [03] Started
[139770193389312] [03] Success
[139770176603904] [05] Started
[139770176603904] [05] Success
[139770210174720] [01] Started
[139770210174720] [01] Success
234 = 2 * 3 * 3 * 13
23456 = 2 * 2 * 2 * 2 * 2 * 733
908345 = 5 * 181669
9803475893 = 1153 * 8502581
389475 = 3 * 3 * 3 * 5 * 5 * 577
9384 = 2 * 2 * 2 * 3 * 17 * 23
7538 = 2 * 3769
4753876348956746 = 2 * 11 * 67 * 89 * 89 * 3373 * 120713
4985 = 5 * 997
39485734 = 2 * 37 * 47 * 11353
9587398 = 2 * 2141 * 2239
7938475839 = 3 * 3 * 7 * 7 * 17 * 53 * 19979
324 = 2 * 2 * 3 * 3 * 3 * 3
3453450 = 2 * 3 * 5 * 5 * 7 * 11 * 13 * 23
alex@~/0x0A-multithreading$
```
