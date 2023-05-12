#include "main.h"

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
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (i);
}

/**
 * main - main
 *
 * Return: success
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	char *args[MAX_ARGS+1];
	char *env[] = {NULL};
	ssize_t line_len;
	int argc, status;
	pid_t pid;

	while (true)
	{
		printf("$ ");
		line_len = getline(&line, &len, stdin);
		if (line_len == -1)
			break;
		if (strcmp(line, "exit\n") == 0)
			break;
		if (line[line_len-1] == '\n')
			line[line_len-1] = '\0';

		argc = tokenize(line, args);
		if (argc > 0)
		{
			char path[128] = "/usr/bin/";

			strcat(path, args[0]);
			args[0] = path;
			pid = fork();
			if (pid == -1)
				perror("fork");
			else if (pid == 0)
			{
				if (execve(args[0], args, env) == -1)
				{
					perror(args[0]);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (waitpid(pid, &status, 0) == -1)
					perror("waitpid");
			}
		}
	}
		free(line);
		return (0);
}
