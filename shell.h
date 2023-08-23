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

/* Inicialize the struct with the info of the program */
void initData(progData *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void showPrompt(char *prompt, progData *data);

/* Print the prompt in a new line */
void hCRTLC(int opr UNUSED);

/*========  myGetLine.c  ========*/

/* Read one line of the standar input*/
int myGetLine(progData *data);

/* split the each line for the logical operators if it exist */
int chkOps(char *arrCmd[], int i, char arrOPs[]);

/*======== expansions.c ========*/

/* expand variables */
void expVars(progData *data);

/* expand aliases */
void expAlias(progData *data);

/* append the string to the end of the buffer*/
int buffAdd(char *buffer, char *str_to_add);

/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(progData *data);

/* Creates a pointer to a part of a string */
char *myStrTok(char *line, char *delim);

/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(progData *data);

/*======== buList.c ========*/

/* If match a builtin, executes it */
int buList(progData *data);

/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenizePath(progData *data);

/* Search for program in path */
int findProg(progData *data);

/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void freeArr(char **directories);

/* Free the fields needed each loop */
void freeCD(progData *data);

/* Free all field of the data */
void freeAD(progData *data);

/************** BUILTINS **************/

/*======== builtins_more.c ========*/

/* Close the shell */
int myExit(progData *data);

/* Change the current directory */
int myCD(progData *data);

/* set the work directory */
int setWD(progData *data, char *newDir);

/* show help information */
int myHelp(progData *data);

/* set, unset and show alias */
int myAlias(progData *data);

/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int myEnv(progData *data);

/* create or override a variable of environment */
int mySetEnv(progData *data);

/* delete a variable of environment */
int myUnSetEnv(progData *data);

/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/

/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *envGK(char *name, progData *data);

/* Overwrite the value of the environment variable */
int envSK(char *key, char *value, progData *data);

/* Remove a key from the environment */
int envRK(char *key, progData *data);

/* prints the current environ */
void printEnv(progData *data);

/************** HELPERS FOR PRINTING **************/

/*======== helpersaiPrint.c ========*/

/* Prints a string in the standar output */
int aiPrint(char *string);

/* Prints a string in the standar error */
int aiPrinte(char *string);

/* Prints a string in the standar error */
int aiPrintErr(int errorcode, progData *data);

/************** HELPERS FOR STRINGS MANAGEMENT **************/

/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int myStrLen(char *string);

/* Duplicates an string */
char *myStrDup(char *string);

/* Compares two strings */
int myStrCmp(char *string1, char *string2, int number);

/* Concatenates two strings */
char *myStrCon(char *string1, char *string2);

/* Reverse a string */
void myStrRev(char *string);

/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void longStr(long number, char *string, int base);

/* convert an string in to a number */
int myAtoi(char *s);

/* count the coincidences of character in string */
int countChars(char *string, char *character);

/*======== alias_management.c ========*/

/* print the list of alias */
int printAlias(progData *data, char *alias);

/* get the alias name */
char *getAlias(progData *data, char *alias);

/* set the alias name */
int setAlias(char *alias_string, progData *data);

#endif /* SHELL_H */