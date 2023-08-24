#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

#include "macros.h"

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


void initData(progData *data, int arc, char *argv[], char **env);
void showPrompt(char *prompt, progData *data);
void hCRTLC(int opr UNUSED);

int execute(progData *data);

void tokenize(progData *data);
char *myStrTok(char *line, char *delim);

int myGetLine(progData *data);
int chkOps(char *arrCmd[], int i, char arrOPs[]);

void expVars(progData *data);
void expAlias(progData *data);
int buffAdd(char *buffer, char *str_to_add);

char **tokenizePath(progData *data);
int findProg(progData *data);

int buList(progData *data);

int myStrLen(char *string);
char *myStrCon(char *string1, char *string2);
char *myStrDup(char *string);
int myStrCmp(char *string1, char *string2, int number);
void myStrRev(char *string);

int myEnv(progData *data);
int mySetEnv(progData *data);
int myUnSetEnv(progData *data);

int aiPrinte(char *string);
int aiPrintErr(int errorcode, progData *data);
int aiPrint(char *string);

int myCD(progData *data);
int setWD(progData *data, char *newDir);
int myAlias(progData *data);
int myHelp(progData *data);
int myExit(progData *data);

void freeArr(char **directories);
void freeCD(progData *data);
void freeAD(progData *data);

void printEnv(progData *data);
int envRK(char *key, progData *data);
char *envGK(char *name, progData *data);
int envSK(char *key, char *value, progData *data);

void longStr(long number, char *string, int base);
int myAtoi(char *s);
int countChars(char *string, char *character);

char *getAlias(progData *data, char *alias);
int setAlias(char *alias_string, progData *data);
int printAlias(progData *data, char *alias);

#endif
