#include "strace.h"

/**
 * trace_sysnum - trace specified process and print out system call number
 * @pid: id of process to trace
 *
 * Return: 0 on success, 1 on failure
 */
int trace_sysnum(pid_t pid)
{
	int wstatus;
	long sysnum;

	setbuf(stdout, NULL);
	if (waitpid(pid, &wstatus, 0) < 0)
		return (1);
	if (ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD) < 0)
		return (1);
	while (1)
	{
		if (!step_syscall(pid))
			break;
		sysnum = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
		if (sysnum < 0)
			return (1);
		printf("%li\n", sysnum);
		if (!step_syscall(pid))
			break;
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
		return (trace_sysnum(pid));
}
