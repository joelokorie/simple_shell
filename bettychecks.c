#include <stdio.h>
#include <unistd.h>

/**
 * main - PID and PPID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t current_pid;
	pid_t parent_pid;

	current_pid = getpid();
	printf("%u\n", current_pid);

	parent_pid = getppid();
	printf("%u\n", parent_pid);

	return (0);
}
