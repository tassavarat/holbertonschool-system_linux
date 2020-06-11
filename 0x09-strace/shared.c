#include "strace.h"

/**
 * step_syscall - start or stop process at next entry or exit from system call
 * @pid: id of process to step through
 *
 * Return: 1 if process stopped by signal, 0 if process exited
 */
int step_syscall(pid_t pid)
{
	int wstatus;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, pid, 0, 0);
		if (waitpid(pid, &wstatus, 0) < 0)
			exit(1);
		if (WIFSTOPPED(wstatus) && WSTOPSIG(wstatus) & 0x80)
			return (1);
		if (WIFEXITED(wstatus))
			return (0);
	}
}

/**
 * attach - attach tracer process to specified tracee
 * @args: pointer to array of arguments
 *
 * Return: -1 on failure
 */
int attach(char *args[])
{
	ptrace(PTRACE_TRACEME);
	kill(getpid(), SIGSTOP);
	return (execvp(*args, args));
}

/**
 * parse_args - check for usage errors
 * @argc: number of command-line arguments
 * @argv: pointer to array of character strings that contain the arguments
 *
 * Return: 0 on success, 1 on error
 */
int parse_args(int argc, char *argv[])
{
	struct stat sb;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", *argv);
		return (1);
	}
	if (stat(argv[1], &sb) < 0)
	{
		fprintf(stderr, "%s: Can't stat '%s': No such file or directory\n",
				*argv, argv[1]);
		return (1);
	}
	return (0);
}
