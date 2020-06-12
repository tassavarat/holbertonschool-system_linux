#include "strace.h"
#include "syscalls.h"

/**
 * ret - prints return value of system call
 * @pid: id of process to print
 * @sysnum: system call value
 *
 * Return: 0 on success, 1 on error
 */
int ret(pid_t pid, long sysnum)
{
	long retval;

	if (syscalls_64_g[sysnum].ret == VOID)
		puts(" = ?");
	else
	{
		retval = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX);
		if (retval == -1)
			return (1);
		printf(" = %#lx\n", retval);
	}
	return (0);
}

/**
 * trace_sysname_ret - print out system call name and return value of process
 * @pid: id of process to trace
 *
 * Return: 0 on success, 1 on failure
 */
int trace_sysname_ret(pid_t pid)
{
	int wstatus;
	long sysnum;

	setbuf(stdout, NULL);
	if (waitpid(pid, &wstatus, 0) == -1)
		return (1);
	if (ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD) == -1)
		return (1);
	while (1)
	{
		if (!step_syscall(pid))
			break;
		sysnum = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
		if (sysnum == -1)
			return (1);
		printf("%s", syscalls_64_g[sysnum].name);
		if (!step_syscall(pid))
			break;
		if (ret(pid, sysnum))
			return (1);
	}
	if (ret(pid, sysnum))
		return (1);
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
	if (pid == -1)
		return (1);
	if (!pid)
		return (attach(argv + 1) == -1);
	else
		return (trace_sysname_ret(pid));
}
