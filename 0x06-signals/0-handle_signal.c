#include "signals.h"

/**
 * siginthandler - action to take on SIGINT delivery
 * @signum: signal value to print
 */
void siginthandler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - sets a handler for the signal SIGINT
 *
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	return (signal(SIGINT, siginthandler) == SIG_ERR ? -1 : 0);
}
