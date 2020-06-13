#ifndef STRACE_H
#define STRACE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#define NAME_PARAMS	0
#define RET		1

/* shared */
int parse_args(int argc, char *argv[]);
int attach(char *args[]);
int step_syscall(pid_t pid);

#endif /* STRACE_H */
