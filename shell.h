#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>



/* Convert characters to lowercase option */
#define TO_LOWERCASE	1
/* Convert to unsigned integer option */
#define TO_UNSIGNED	2

/* Flag indicating whether to use the system's getline() function */
#define INIT_SYSTEM_GETLINE 0
/* Flag indicating whether to use the system's strtok() function */
#define INIT_SYSTEM_STRTOK 0

/* Regular command execution without chaining */
#define NORMAL_COMMAND	0
/* Executes next command if the previous one succeeds */
#define AND_COMMAND		2
/* Executes next command if the previous one fails */
#define OR_COMMAND		1
/* Used for other types of command chaining */
#define CHAINED_COMMAND	3

/* File name for storing command shellHistory */
#define FILE_HISTORY	".simple_shell_history"
/* Maximum number of entries in the command shellHistory */
#define MAX_ENTRIES_HISTORY	4096

/* Size of the read buffer for input */
#define INPUT_BUFFER_SIZE 1024
/* Size of the write buffer for output */
#define OUTPUT_BUFFER_SIZE 1024
/* Special value to indicate buffer flush */
#define FLUSH_BUFFER -1

/* External Environment Variable Declaration */
extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct userInfo - holds pseudo-arguments for function passing,
 * allowing a consistent prototype for a function pointer struct
 * @cmdArgs: string created from getline with command arguments
 * @cmdArgv: array of strings derived from cmdArgs
 * @cmdBufferType: Type of command chaining (CMD_type: ||, &&, ;)
 * @cmdArgc: count of arguments
 * @cmdCounter: count of errors
 * @cmdCounterFlag: indicator to count this line of input
 * @cmdBuffer: address of the pointer to cmdBuffer, on if chaining
 * @filePath: string representing the current command's file path
 * @errValue: error code for exit()
 * @fileName: filename of the program
 * @env: linked list representing a local copy of the environment
 * @environ: custom-modified copy of the environment from the linked list env
 * @shellHistory: node representing shell history
 * @alias: node for storing aliases
 * @diffEnv: indicator if the environment was changed
 * @shellState: return shell state from the last executed command
 * @getFileDes: file descriptor from which to read line input
 * @historyVal: line number count for shell history
 */

typedef struct userInfo
{
	char *cmdArgs;
	char **cmdArgv;
	int cmdArgc;
	char **cmdBuffer;
	int cmdBufferType;
	int cmdCounterFlag;
	unsigned int cmdCounter;
	char *filePath;
	int errValue;
	char *fileName;
	list_t *env;
	list_t *shellHistory;
	list_t *alias;
	char **environ;
	int diffEnv;
	int shellState;
	int getFileDes;
	int historyVal;
} dataX;

/* Initializer for the userInfo struct */
#define DATA_INIT \
{ \
    NULL,          /* cmdArgs */ \
    NULL,          /* cmdArgv */ \
    0,             /* cmdArgc */ \
    NULL,          /* cmdBuffer */ \
    0,             /* cmdBufferType */ \
    0,             /* cmdCounterFlag */ \
    0,             /* cmdCounter */ \
    NULL,          /* filePath */ \
    0,             /* errValue */ \
    NULL,          /* fileName */ \
    NULL,          /* env */ \
    NULL,          /* shellHistory */ \
    NULL,          /* alias */ \
    NULL,          /* environ */ \
    0,             /* diffEnv */ \
    0,             /* shellState */ \
    0,             /* getFileDes */ \
    0              /* historyVal */ \
}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(dataX *);
} builtin_table;


/* Function prototype(s) for loop.c */
int hsh(dataX *, char **);
int builtIn(dataX *);
void cmd_g(dataX *);
void cmd_f(dataX *);

/* Function prototype(s) for parser.c */
int cmdRun(dataX *, char *);
char *genChar(char *, int, int);
char *varPath(dataX *, char *, char *);

/* Function prototype(s) for loophsh.c */
int loophsh(char **);

/* Function prototype(s) for errors.c */
void putsIN(char *);
int putcharIN(char);
int _putFileDes(char c, int fd);
int _putsFileDes(char *str, int fd);

/* Function prototype(s) for string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *beginT(const char *, const char *);
char *_strcat(char *, char *);

/* Function prototype(s) for string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Function prototype(s) for exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Function prototype(s) for tokenizer.c */
char **strtow(char *, char *);
char **strtowTwo(char *, char);

/* Function prototype(s) for realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Function prototype(s) for memory.c */
int getFree(void **);

/* Function prototype(s) for convert.c */
int iMode(dataX *);
int checkDelim(char, char *);
int checkAlpha(int);
int convert(char *);

/* Function prototype(s) for shellErrors2.c */
int convertError(char *);
void printError(dataX *, char *);
int printData(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Function prototype(s) for shellBuiltins1.c */
int exitDone(dataX *);
int cdDone(dataX *);
int helpDone(dataX *);

/* Function prototype(s) for shellBuiltins2.c */
int historyDone(dataX *);
int aliasDone(dataX *);

/* Function prototype(s) for getline.c */
ssize_t takeInput(dataX *);
int _getLine(dataX *, char **, size_t *);
void intHandle(int);

/* Function prototype(s) for getinfo.c */
void clrData(dataX *);
void defData(dataX *, char **);
void freeData(dataX *, int);

/* Function prototype(s) for environ.c */
char *defEnv(dataX *, const char *);
int envDone(dataX *);
int setEnvDone(dataX *);
int unsetEnvDone(dataX *);
int fillEnvList(dataX *);

/* Function prototype(s) for setEnvironment.c */
char **envGet(dataX *);
int envUnset(dataX *, char *);
int envSet(dataX *, char *, char *);

/* Function prototype(s) for history.c */
char *getFileHistory(dataX *info);
int historyWrite(dataX *info);
int hRead(dataX *info);
int hBuild(dataX *info, char *buf, int linecount);
int hNum(dataX *info);

/* Function prototype(s) for linkedLists1.c */
list_t *newNode(list_t **, const char *, int);
size_t strPrint(const list_t *);
int delNode(list_t **, unsigned int);
void noList(list_t **);

/* Function prototype(s) for linkedLists2.c */
size_t lengthT(const list_t *);
char **lengthS(list_t *);
size_t listPrint(const list_t *);
list_t *beginNode(list_t *, char *, char);
ssize_t nodeIndex(list_t *, list_t *);

/* Function prototype(s) for vars.c */
int chainDelim(dataX *, char *, size_t *);
void chainChecks(dataX *, char *, size_t *, size_t, size_t);
int aliasChange(dataX *);
int variableChange(dataX *);
int stringChange(char **, char *);

#endif
