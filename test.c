#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 16  // maximum number of arguments

/**
 * Tokenizes the input string into an array of arguments.
 * Returns the number of arguments.
 */
int tokenize(char *input, char *args[]) {
    // tokenize the input string
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // set the last argument to NULL
    return i;
}

int main(void) {
    char *line = NULL;
    size_t len = 0;
    char *args[MAX_ARGS+1];
    char *env[] = {NULL};
    ssize_t line_len;
    while (true) {
        printf("$ ");

        line_len = getline(&line, &len, stdin);
        if (line_len == -1)  // end of file or error
            break;

        if (strcmp(line, "exit\n") == 0)  // exit the shell
            break;

        // remove trailing newline
        if (line[line_len-1] == '\n')
            line[line_len-1] = '\0';

        int argc = tokenize(line, args);  // tokenize the input
        if (argc > 0) {
            // build a new argument list with full path to the executable
            char path[128] = "/usr/bin/";
            strcat(path, args[0]);
            args[0] = path;

            pid_t pid = fork();
            if (pid == -1) {  // fork failed
                perror("fork");
            } else if (pid == 0) {  // child process
                if (execve(args[0], args, env) == -1) {  // execute the command
                    perror(args[0]);
                    exit(EXIT_FAILURE);
                }
            } else {  // parent process
                int status;
                if (waitpid(pid, &status, 0) == -1) {  // wait for the child to finish
                    perror("waitpid");
                }
            }
        }
    }

return (0);
}

