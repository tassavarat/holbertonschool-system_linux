# 0x00. C - ls

## Learning Objectives
* How does `ls` work?
* What are all the functions used by `ls`?

## Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
* No more than 5 functions per file
* All your header files should be include guarded
* Valgrind should show 0 memory leak and 0 error
* Unless specified otherwise, your program must have the exact same output as ls as well as the exact same error output - except for alignment.

## Allowed Functions and System Calls

* opendir (man 3 opendir)
* readdir (man 3 readdir)
* closedir (man 3 closedir)
* exit (man 3 exit)
* free (man 3 free)
* lstat (man 2 lstat)
* malloc (man 3 malloc)
* perror (man 3 perror)
* write (man 2 write)
* printf (man 3 printf)
* sprintf (man 3 sprintf)
* fprintf (man 3 fprintf)
* readlink (man 2 readlink)
* ctime (man 3 ctime)
* getpwuid (man 3 getpwuid)
* getgrgid (man 3 getgrgid)

---

### 0. Let's start with something simple!
Create a program that lists the content of the current directory.

* Usage : hls
* You don’t have to worry about the spacing
* You don’t have to worry about the sorting
```
wilfried@~$ ls
abc  file  File2  file3  folder1  Folder2  folder3  hls
wilfried@~$ ./hls
abc  file  File2  file3  folder1  Folder2  folder3  hls
wilfried@~$
```

### 1. Maybe some parameters?
Your program should now take one or more file or directory names as parameters.

Usage: hls [FILE]...

Errors must be printed the same way than ls does (No such file or directory, Permission denied, etc…) on stderr. Don’t forget the exit value.
```
wilfried@~$ ls test
abc  file  File2  file3  folder1  Folder2  folder3
wilfried@~$ ./hls test
abc  file  File2  file3  folder1  Folder2  folder3
wilfried@~$ ./hls test/folder1/ test
test:
abc  file  File2  file3  folder1  Folder2  folder3

test/folder1/:
folder1-1  folder1-2  folder1-3
/simple_ls$ ./hls test/random
hls: cannot access test/random: No such file or directory
wilfried@~$
```

### 2. What about options?
Implement the -1 option.

Usage: hls [-1] [FILE]...

For the rest of the project, an option will be identified by a command-line argument starting with the character - (like ls).
```
wilfried@~$ ls test -1
abc
file
File2
file3
folder1
Folder2
folder3
wilfried@~$ ./hls test -1
abc
file
File2
file3
folder1
Folder2
folder3
wilfried@~$
```

### 3. Hidden files
Implement the -a option.

Usage: hls [-a1] [FILE]...
```
wilfried@~$ ls -a test
.  ..  abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
wilfried@~$ ./hls -a test
.  ..  abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
wilfried@~$ ./hls -a test/folder1
.  ..  folder1-1  folder1-2  folder1-3
wilfried@~$
```

### 4. Almost all
Implement the -A option.

Usage: hls [-A] [FILE]...
```
wilfried@~$ ls -A test
abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
wilfried@~$ ./hls -A test
abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
wilfried@~$ ./hls -A test/folder1
folder1-1  folder1-2  folder1-3
wilfried@~$
```

### 5. More details 
Implement the -l option.

Usage: hls [-l] [FILE]...
```
wilfried@~$ ls -l test
total 12
-rw-rw-r-- 1 wilfried wilfried    0 May  8 00:19 abc
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
wilfried@~$ ./hls -l test
-rw-rw-r-- 1 wilfried wilfried    0 May  8 00:19 abc
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
wilfried@~$
```

You might notice the total 12 in the first line of ls -l. You can ignore this value for this exercise.

### 6. Mixing options
All options together.

Usage: hls [-1aAl] [FILE]...
```
wilfried@~$ ./hls -lA test
-rw-rw-r-- 1 wilfried wilfried    0 May  8 00:19 abc
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 16:30 .hidden1
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 16:30 .hidden2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 17:08 ..hidden3
wilfried@~$ ./hls -lA -a test
drwxrwxr-x 5 wilfried wilfried 4096 May  8 01:12 .
drwxrwxr-x 4 wilfried wilfried 4096 May 15 11:51 ..
-rw-rw-r-- 1 wilfried wilfried    0 May  8 00:19 abc
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 16:30 .hidden1
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 16:30 .hidden2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 17:08 ..hidden3
wilfried@~$ ./hls -1A test
abc
file
File2
file3
folder1
Folder2
folder3
.hidden1
.hidden2
..hidden3
wilfried@~$
```

### 7. Esrever
Implement the -r option.

Usage: hls [-1aAlr] [FILE]...
```
wilfried@~$ ./hls test
abc file File2 file3 folder1 Folder2 folder3
wilfried@~$ ./hls test -r
folder3  Folder2  folder1  file3  File2  file  abc
wilfried@~$ ./hls test/folder1/ test/folder3/ -r
test/folder3/:
symlink  folder3-1  file2  file1

test/folder1/:
folder1-3  folder1-2  folder1-1
wilfried@~$
```

### 8. More sorting?
Implement the -S option.

Usage: hls [-1aAlrS] [FILE]...
```
wilfried@~$ ./hls -l test
-rw-rw-r-- 1 wilfried wilfried    0 May 16 12:36 abc
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
wilfried@~$ ./hls -lS test
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
-rw-rw-r-- 1 wilfried wilfried    0 May 16 12:36 abc
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
wilfried@~$ ./hls -lSr test
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 May 16 12:36 abc
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
wilfried@~$
```

### 9. I know you like sorting things.
Implement the -t option.

Usage: hls [-1aAlrSt] [FILE]...
```
wilfried@~$ ./hls -l test
-rw-rw-r-- 1 wilfried wilfried    0 May 16 12:36 abc
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
wilfried@~$ ./hls -lt test
-rw-rw-r-- 1 wilfried wilfried    0 May 16 12:36 abc
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
wilfried@~$ ./hls -ltr test
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3
-rw-rw-r-- 1 wilfried wilfried    0 May 16 12:36 abc
wilfried@~$
```

### 10. The Juggernaut
Implement the -R option.

Usage: hls [-1aAlrStR] [FILE]...
```
wilfried@~$ ./hls -R test
test:
abc  ABC  file  File2  file3  folder1  Folder2  folder3

test/folder1:
folder1-1  folder1-2  folder1-3

test/folder1/folder1-1:
file1  file2  file3

test/folder1/folder1-2:
file1

test/folder1/folder1-3:
file1  file2

test/Folder2:
file1  file2

test/folder3:
file1  file2  folder3-1  symlink

test/folder3/folder3-1:
file1  folder3-1-1

test/folder3/folder3-1/folder3-1-1:
file1  file2
wilfried@~$ ./hls -Rl test
test:
-rw-rw-r-- 1 wilfried wilfried    0 May 16 12:36 abc
-rw-rw-r-- 1 wilfried wilfried    0 May  8 00:19 ABC
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 File2
-rw-rw-r-- 1 wilfried wilfried    0 Apr 18 14:04 file3
drwxrwxr-x 5 wilfried wilfried 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 wilfried wilfried 4096 May  7 15:36 Folder2
drwxrwxr-x 3 wilfried wilfried 4096 May  7 15:37 folder3

test/folder1:
drwxrwxr-x 2 wilfried wilfried 4096 Apr 30 14:59 folder1-1
drwxrwxr-x 2 wilfried wilfried 4096 Apr 30 14:59 folder1-2
drwxrwxr-x 2 wilfried wilfried 4096 Apr 30 14:59 folder1-3

test/folder1/folder1-1:
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 14:59 file1
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 14:59 file2
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 14:59 file3

test/folder1/folder1-2:
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 14:59 file1

test/folder1/folder1-3:
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 14:59 file1
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 14:59 file2

test/Folder2:
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 14:59 file1
-rw-rw-r-- 1 wilfried wilfried 0 May  7 15:36 file2

test/folder3:
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 15:03 file1
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 15:03 file2
drwxrwxr-x 3 wilfried wilfried 4096 Apr 30 15:22 folder3-1
lrwxrwxrwx 1 wilfried wilfried    5 May  8 00:01 symlink -> file2

test/folder3/folder3-1:
-rw-rw-r-- 1 wilfried wilfried    0 Apr 30 15:03 file1
drwxrwxr-x 2 wilfried wilfried 4096 Apr 30 15:03 folder3-1-1

test/folder3/folder3-1/folder3-1-1:
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 15:03 file1
-rw-rw-r-- 1 wilfried wilfried 0 Apr 30 15:03 file2
wilfried@~$
```
