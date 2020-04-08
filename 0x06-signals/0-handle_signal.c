#include "signals.h"

/**
 * siginthandler - action to take on SIGINT delivery
 * @signum: signal value to print
 */
void siginthandler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
}

/**
 * handle_signal - sets a handler for the signal SIGINT
 *
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	signal(SIGINT, siginthandler);
	return (!errno ? 0 : -1);
}
