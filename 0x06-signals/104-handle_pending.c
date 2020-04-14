#include "signals.h"

/**
 * handle_pending - sets up a handler for all pending signals
 * @handler: pointer to function to set for pending signals
 *
 * Return: 0 on success, -1 on error
 */
int handle_pending(void (*handler)(int))
{
	sigset_t set;
	struct sigaction act;
	size_t sig;

	act.sa_handler = handler;
	if (sigpending(&set))
		goto out;
	for (sig = 1; sig < NSIG; ++sig)
		if (sigismember(&set, sig) == 1)
			if (sigaction(sig, &act, NULL))
out:
				return (-1);
	return (0);
}
