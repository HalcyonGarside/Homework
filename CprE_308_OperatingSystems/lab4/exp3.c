#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void fpe_handler();

int main()
{
	signal(SIGFPE, fpe_handler);
	int a = 4;
	a = a / 0;
}

void fpe_handler()
{
	printf("Caught a SIGFPE\n");
}
