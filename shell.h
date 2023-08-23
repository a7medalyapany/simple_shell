#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>  /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h>     /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h>  /* for wait */
#include <sys/stat.h>  /* for use of stat function */
#include <signal.h>    /* for signal management */
#include <fcntl.h>     /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @progName: the name of the executable
 * @inLine: pointer to the input read for myGetLine
 * @cmdLine: pointer to the first command typed by the user
 * @exeCounter: number of excecuted comands
 * @FD: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @aliasList: array of pointers with aliases.
 */
typedef struct info
{
    char *progName;
    char *inLine;
    char *cmdLine;
    int exeCounter;
    int FD;
    char **tokens;
    char **env;
    char **aliasList;
} progData;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
    char *builtin;
    int (*function)(progData *data);
} builtins;

/************* MAIN FUNCTIONS *************/

/*========  shell.c  ========*/

void initData(progData *data, int arc, char *argv[], char **env);
void showPrompt(char *prompt, progData *data);
void hCRTLC(int opr UNUSED);

/*========  myGetLine.c  ========*/
int myGetLine(progData *data);
int chkOps(char *arrCmd[], int i, char arrOPs[]);

/*======== expansions.c ========*/

/* expand variables */
void expVars(progData *data);
void expAlias(progData *data);
int buffAdd(char *buffer, char *str_to_add);

/*======== str_tok.c ========*/

void tokenize(progData *data);
char *myStrTok(char *line, char *delim);

/*======== execute.c ========*/

int execute(progData *data);

/*======== buList.c ========*/

int buList(progData *data);

/*======== find_in_path.c ========*/

char **tokenizePath(progData *data);
int findProg(progData *data);

/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======== helpers_free.c ========*/

void freeArr(char **directories);
void freeCD(progData *data);
void freeAD(progData *data);

/************** BUILTINS **************/

/*======== builtins_more.c ========*/

int myExit(progData *data);
int myCD(progData *data);
int setWD(progData *data, char *newDir);
int myHelp(progData *data);
int myAlias(progData *data);

/*======== builtins_env.c ========*/

int myEnv(progData *data);
int mySetEnv(progData *data);
int myUnSetEnv(progData *data);

/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/

/*======== env_management.c ========*/

char *envGK(char *name, progData *data);
int envSK(char *key, char *value, progData *data);
int envRK(char *key, progData *data);
void printEnv(progData *data);

/************** HELPERS FOR PRINTING **************/

/*======== helpersaiPrint.c ========*/

int aiPrint(char *string);
int aiPrinte(char *string);
int aiPrintErr(int errorcode, progData *data);

/************** HELPERS FOR STRINGS MANAGEMENT **************/

/*======== helpers_string.c ========*/

int myStrLen(char *string);
char *myStrDup(char *string);
int myStrCmp(char *string1, char *string2, int number);
char *myStrCon(char *string1, char *string2);
void myStrRev(char *string);

/*======== helpers_numbers.c ========*/

void longStr(long number, char *string, int base);
int myAtoi(char *s);
int countChars(char *string, char *character);

/*======== alias_management.c ========*/

int printAlias(progData *data, char *alias);
char *getAlias(progData *data, char *alias);
int setAlias(char *alias_string, progData *data);

#endif