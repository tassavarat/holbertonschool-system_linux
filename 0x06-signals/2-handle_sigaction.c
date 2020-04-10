#include "signals.h"

void siginthandler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
}

int handle_sigaction(void)
{
	struct sigaction act;

	act.sa_handler = siginthandler;
	return (sigaction(SIGINT, &act, NULL));
}
