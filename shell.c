#include "main.h"


/**
 * env_blt - print the environment
 *
 * Return: void
 */
void env_blt(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		write(1, *env, _strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}
/**
 * tokenize - Tokenizes the input string into an array of arguments.
 * @input: userinput
 * @args: argements
 *
 * Return: the number of arguments.
 */
int tokenize(char *input, char *args[])
{
	int i = 0;
	char *token = strtok(input, " ");

	while (token != NULL && i < MAX_ARGS)
	{
		args[i++] = token;
		token = strtok(NULL, " \n\t\r");
	}
	args[i] = NULL;
	return (i);
}
/**
 * exe - execute command
 * @args: argement
 * @env: envirement
 * @av: agenment vector
 * Return: int
 */
int exe(char *args[], char *env[], char **av)
{
	pid_t pid;
	char path[128] = "/usr/bin/";
	char cmd[64];

	_strcpy(cmd, args[0]);
	_strcat(path, args[0]);
	args[0] = path;
	pid = fork();
	if (pid < 0)
	{
		perror("Fork fail");
		return (0);
	}
	else if (!pid)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror(av[0]);
			return (0);
		}
	}
	else
		wait(NULL);
	return (1);
}

/**
 * main - main
 * @ac: argenment count
 * @av: argement vector
 * Return: success
 */

int main(__attribute__((unused))int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	char *args[MAX_ARGS + 1];
	char *env[] = {NULL};
	ssize_t line_len;
	int argc;

	while (true)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		line_len = getline(&line, &len, stdin);
		if (line_len == -1)
			exit(0);
		
		if (_strcmp(line, "exit\n") == 0)
			break;
		if (_strcmp(line, "env\n") == 0)
		{
			env_blt();
			continue;
		}
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		argc = tokenize(line, args);
		if (argc > 0)
			exe(args, env, av);
	}
		free(line);
		return (0);
}
