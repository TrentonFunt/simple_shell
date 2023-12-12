#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define MAX_INPUT 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function declarations */
void displayPrompt(void);
char *readUserInput(void);
char *extractCommand(char *inputLine);
void executeCommand(char *command);
int exit_Shell(char *command);
void create_CP(char *args[]);
void executeCommand(char *command);

#endif /* SIMPLE_SHELL_H */