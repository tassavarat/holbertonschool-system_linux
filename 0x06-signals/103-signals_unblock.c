#include "signals.h"

/**
 * sigset_init - initialises sigset
 * @set: pointer to signal set to initialise
 * @signals: 0-terminated array of signals
 *
 * Return: 0 on success, -1 on error
 */
int sigset_init(sigset_t *set, int *signals)
{
	int i;

	if (sigemptyset(set))
		goto out;
	for (i = 0; signals[i]; ++i)
		if (sigaddset(set, signals[i]))
out:
			return (-1);
	return (0);
}

/**
 * signals_unblock - unblocks given set of signals
 * @signals: 0-terminated array of signals
 *
 * Return: 0 on success, -1 on error
 */
int signals_unblock(int *signals)
{
	sigset_t set;

	if (sigset_init(&set, signals))
		return (-1);
	return (sigprocmask(SIG_UNBLOCK, &set, NULL));
}
