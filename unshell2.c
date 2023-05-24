#include "shell.h"
/**
 */

extern char **environ;
/**
 * unshell2prompt - function that displays prompt
 * Return: $$
 */
void unshell2prompt(void)
{
	char *prompt = "$$";

	write(1, prompt, 2);
}
/**
 * unshell2execute - function that executes variable
 * @buf: pointer
 * @argv: command input by user
 * Return: output
 */
void unshell2execute(char *buf, char *argv[])
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
		execve(buf, argv, environ);
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
 * unshell2parse - function that parses commands
 * @buf: pointer
 * @argv: command input by user
 * Return: argc
 */
int unshell2parse(char *buf, char *argv[])
{
	int argc = 0;
	char *token = strtok(buf, " ");

	while (token != NULL && argc < MAX_ARGUMENTS)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;

	return (argc);
}

int unshell2main(void)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t getl;
	char *argv[MAX_ARGUMENTS];
	int argc;

	while (1)
	{
		char *prompt = "$$";

		write(1, prompt, 2);
		getl = getline(&buf, &n, stdin);
		if (getl == -1)
		{
			break;
		}
		if (buf[getl - 1] == '\n')
		{
			buf[getl - 1] = '\0';
		}
		argc = unshell2parse(buf, argv);

		if (argc > 2)
		{
			unshell2execute(argv[0], argv);
		}
	}
	free(buf);
	return (0);
}
