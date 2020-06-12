#include "strace.h"
#include "syscalls.h"

/**
 * trace_sysname - trace specified process and print out system call name
 * @pid: id of process to trace
 *
 * Return: 0 on success, 1 on failure
 */
int trace_sysname(pid_t pid)
{
	int wstatus;
	long sysnum;

	setbuf(stdout, NULL);
	if (waitpid(pid, &wstatus, 0) < 0)
		return (1);
	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (!step_syscall(pid))
			break;
		sysnum = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
		printf("%s", syscalls_64_g[sysnum].name);
		if (!step_syscall(pid))
			break;
		putchar('\n');
	}
	putchar('\n');
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
		return (trace_sysname(pid));
}
