#include "signals.h"

/**
 * handler - action to take on SIGQUIT intercept
 * @sig: number of the signal that caused invocation of the handler
 * @info: pointer to a siginfo_t
 * @ucontext: pointer to a ucontext_t
 */
void handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	psiginfo(info, "Caught");
}

/**
 * all_in_one - Sets up a handler for all signals
 */
void all_in_one(void)
{
	int sig;
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	for (sig = 1; sig <= SIGRTMAX; ++sig)
		sigaction(sig, &act, NULL);
}
