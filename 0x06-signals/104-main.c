#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

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
 * _signals_unblock - unblocks given set of signals
 * @signals: 0-terminated array of signals
 *
 * Return: 0 on success, -1 on error
 */
int _signals_unblock(int *signals)
{
	sigset_t set;

	if (sigset_init(&set, signals))
		return (-1);
	return (sigprocmask(SIG_UNBLOCK, &set, NULL));
}

/**
 * _signals_block - blocks given set of signals
 * @signals: 0-terminated array of signals
 *
 * Return: 0 on success, -1 on error
 */
int _signals_block(int *signals)
{
	sigset_t set;

	if (sigset_init(&set, signals))
		return (-1);
	return (sigprocmask(SIG_BLOCK, &set, NULL));
}

/**
 * handler - Handler for pending signals
 * @signum: Signal number
 */
void handler(int signum)
{
	printf("\nCaught signal %d\n", signum);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int signals[] = {
		SIGINT,
		SIGQUIT,
		SIGSEGV,
		SIGTRAP,
		0
	};

	if (_signals_block(signals) == -1)
	{
		fprintf(stderr, "Failed to block signals\n");
		return (EXIT_FAILURE);
	}

	sleep(5);
	if (handle_pending(&handler) == -1)
	{
		printf("Failed to set up handler for pending signals\n");
		return (EXIT_FAILURE);
	}

	if (_signals_unblock(signals) == -1)
	{
		fprintf(stderr, "Failed to unblock signals\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
