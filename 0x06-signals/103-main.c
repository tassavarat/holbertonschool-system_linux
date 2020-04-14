#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "signals.h"

/**
 * _sigset_init - initialises sigset
 * @set: pointer to signal set to initialise
 * @signals: 0-terminated array of signals
 *
 * Return: 0 on success, -1 on error
 */
int _sigset_init(sigset_t *set, int *signals)
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
 * _signals_block - blocks given set of signals
 * @signals: 0-terminated array of signals
 *
 * Return: 0 on success, -1 on error
 */
int _signals_block(int *signals)
{
	sigset_t set;

	if (_sigset_init(&set, signals))
		return (-1);
	return (sigprocmask(SIG_BLOCK, &set, NULL));
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int signals_to_block[] = {
		SIGINT,
		SIGQUIT,
		SIGSEGV,
		SIGTRAP,
		0
	};
	int signals_to_unblock[] = {
		SIGINT,
		SIGSEGV,
		SIGTRAP,
		0
	};

	if (_signals_block(signals_to_block) == -1)
	{
		fprintf(stderr, "Failed to block signals\n");
		return (EXIT_FAILURE);
	}
	if (signals_unblock(signals_to_unblock) == -1)
	{
		fprintf(stderr, "Failed to block signals\n");
		return (EXIT_FAILURE);
	}
	while (98)
	{
		sleep(5);
	}
	return (EXIT_SUCCESS);
}
