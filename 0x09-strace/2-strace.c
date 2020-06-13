#include "strace.h"
#include "syscalls.h"

/**
 * trace_sysname_ret - print out system call name and return value of process
 * @pid: id of process to trace
 */
void trace_sysname_ret(pid_t pid)
{
	int wstatus;
	long sysnum;

	setbuf(stdout, NULL);
	waitpid(pid, &wstatus, 0);
	ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (!step_syscall(pid))
			break;
		sysnum = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
		printf("%s", syscalls_64_g[sysnum].name);
		if (!step_syscall(pid))
			break;
		syscalls_64_g[sysnum].ret == VOID ? puts(" = ?") :
			printf(" = %#lx\n", ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX));
	}
	syscalls_64_g[sysnum].ret == VOID ? puts(" = ?") :
		printf(" = %#lx\n", ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX));
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
	trace_sysname_ret(pid);
	return (0);
}
