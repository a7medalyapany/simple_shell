#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>  /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <NoOfErr.h>   /* for NoOfErr and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h>  /* for wait */
#include <sys/stat.h>  /* for use of stat function */
#include <signal.h>    /* for signal management */
#include <fcntl.h>     /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's dt
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
} progdt;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
    char *builtin;
    int (*function)(progdt *dt);
} builtins;

/************* MAIN FUNCTIONS *************/

/*========  shell.c  ========*/

void initdt(progdt *dt, int arc, char *argv[], char **env);
void showProp(char *prompt, progdt *dt);
void hCRTLC(int opr UNUSED);

/*========  myGetLine.c  ========*/

int myGetLine(progdt *dt);
int check_logic_ops(char *arrCmd[], int i, char arrOp[]);

/*======== expansions.c ========*/

void expand_variables(progdt *dt);
void expand_alias(progdt *dt);
int buffer_add(char *buffer, char *str_to_add);

/*======== str_tok.c ========*/

void tokenize(progdt *dt);
char *myStrTok(char *line, char *delim);

/*======== execute.c ========*/

int execute(progdt *dt);

/*======== myBuList.c ========*/

int myBuList(progdt *dt);

/*======== find_in_path.c ========*/

char **tokenizePath(progdt *dt);

int findProg(progdt *dt);

/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======== helpers_free.c ========*/

void freeArr(char **directories);
void freeCD(progdt *dt);
void freeAD(progdt *dt);

/************** BUILTINS **************/

/*======== builtins_more.c ========*/

int myExit(progdt *dt);
int myCD(progdt *dt);
int setWD(progdt *dt, char *newDir);
int BuHelp(progdt *dt);
int BuAlias(progdt *dt);

/*======== builtins_env.c ========*/
int myEnv(progdt *dt);
int mySetEnv(progdt *dt);
int myUnSetEnv(progdt *dt);

/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/

/*======== env_management.c ========*/

char *env_get_key(char *name, progdt *dt);
int env_set_key(char *key, char *value, progdt *dt);
int env_remove_key(char *key, progdt *dt);
void printEnv(progdt *dt);

/************** HELPERS FOR PRINTING **************/

int aiPrint(char *string);
int aiPrinte(char *string);
int aiPrintError(int errorcode, progdt *dt);

/************** HELPERS FOR STRINGS MANAGEMENT **************/

/*======== helpers_string.c ========*/

int myStrLen(char *string);
char *myStrDup(char *string);
int myStrCmp(char *string1, char *string2, int number);
char *myStrCon(char *string1, char *string2);
void myStrRev(char *string);

/*======== helpers_numbers.c ========*/

void LongStr(long number, char *string, int base);
int myAtoi(char *s);
int countChars(char *string, char *character);

/*======== alias_management.c ========*/

int printAlias(progdt *dt, char *alias);
char *getAlias(progdt *dt, char *alias);
int setAlias(char *alias_string, progdt *dt);

#endif