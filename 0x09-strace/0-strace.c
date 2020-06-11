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
		waitpid(pid, &wstatus, 0);
		if (WIFSTOPPED(wstatus) && WSTOPSIG(wstatus) & 0x80)
			return (1);
		if (WIFEXITED(wstatus))
			return (0);
	}
}

/**
 * trace - trace specified process
 * @pid: id of process to trace
 *
 * Return: 0 on success, 1 on failure
 */
int trace(pid_t pid)
{
	int wstatus;

	setbuf(stdout, NULL);
	if (waitpid(pid, &wstatus, 0) < 0)
		return (1);
	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (!step_syscall(pid))
			break;
		printf("%li\n", ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX));
		if (!step_syscall(pid))
			break;
	}
	return (0);
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

/**
 * main - entry point
 * @argc: number of command-line arguments
 * @argv: pointer to an array of character strings that contain the arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	pid_t pid;

	if (parse_args(argc, argv))
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
		return (attach(argv + 1));
	else
		return (trace(pid));
}
