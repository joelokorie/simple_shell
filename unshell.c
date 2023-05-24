#include "shell.h"

extern char **environ;
/**
 * unshellprompt - function that prints prompt
 * Return: $$
 */
void unshellprompt(void)
{
	char *prompt = "$$";

	write(1, prompt, 2);
}
/**
 * unshellexecute - function that carries out input command
 * @buf: pointer that stores the commands
 * Return: output or error
 */
void unshellexecute(char *buf)
{
	pid_t thepid;

	thepid = fork();
	if (thepid == -1)
	{
		perror("Error:forking");
		free(buf);
		exit(1);
	}
	else if (thepid == 0)
	{
		char **argv = malloc(sizeof(char *) * 2);

		if (argv == NULL)
		{
			perror("Error:malloc");
			free(buf);
			exit(1);
		}
		argv[0] = buf;
		argv[1] = NULL;


		execve(argv[0], argv, environ);
		perror("Error:execution");
		free(buf);
		exit(1);
	}
	else
	{
		int status;

		waitpid(thepid, &status, 0);
	}
}
/**
 * shellmain - function that executes
 * Return: Always 0
 */

int shellmain(void)
{
	char *buf = NULL;
	size_t n;
	ssize_t getl;

	while (1)
	{
		char *prompt = "$$";

		write(1, prompt, 2);

		getl = getline(&buf, &n, stdin);

		if (getl == -1)
			break;

		if (buf[getl - 1] == '\n')
		{
			buf[getl - 1] = '\0';
		}
		unshellexecute(buf);
	}
	free(buf);
	return (0);
}
