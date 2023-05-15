#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 16
extern char **environ;
int tokenize(char *input, char *args[]);

#endif /* MAIN_H */
