#include "strace.h"
#include "syscalls.h"

/**
 * print_sys - print specified system call information
 * @data: specifies what data to print
 * @regs: struct containing register values
 * @pid: id of process to trace
 */
void print_sys(int data, struct user_regs_struct regs, pid_t pid)
{
	size_t i;

	if (data == NAME_PARAMS)
	{
		printf("%s(", syscalls_64_g[regs.orig_rax].name);
		for (i = 0; i < syscalls_64_g[regs.orig_rax].nb_params; ++i)
		{
			if (syscalls_64_g[regs.orig_rax].params[i] == VARARGS)
			{
				printf("...");
				break;
			}
			printf("%s%#lx", !i ? "" : ", ", (unsigned long) (regs.rdi + i * 8));
		}
	}
	else if (data == RET)
	{
		ptrace(PTRACE_GETREGS, pid, NULL, &regs);
		syscalls_64_g[regs.orig_rax].ret == VOID ? puts(" = ?") :
			printf(") = %#lx\n", (unsigned long) regs.rax);
	}
}

/**
 * trace_sysfull - print out system call name and return value of process
 * @pid: id of process to trace
 */
void trace_sysfull(pid_t pid)
{
	int wstatus;
	struct user_regs_struct regs;

	setbuf(stdout, NULL);
	waitpid(pid, &wstatus, 0);
	ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (!step_syscall(pid))
			break;
		ptrace(PTRACE_GETREGS, pid, NULL, &regs);
		print_sys(NAME_PARAMS, regs, pid);
		if (!step_syscall(pid))
			break;
		print_sys(RET, regs, pid);
	}
	print_sys(RET, regs, pid);
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
	trace_sysfull(pid);
	return (0);
}
