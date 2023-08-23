#include "shell.h"

/**
 * buList - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int buList(progData *data)
{
    int itrtor;
    builtins options[] = {
        {"exit", myExit},
        {"help", myHelp},
        {"cd", myCD},
        {"alias", myAlias},
        {"env", myEnv},
        {"setenv", mySetEnv},
        {"unsetenv", myUnSetEnv},
        {NULL, NULL}};

    /*walk through the structure*/
    for (itrtor = 0; options[itrtor].builtin != NULL; itrtor++)
    {
        /*if there is a match between the given command and a builtin,*/
        if (myStrCmp(options[itrtor].builtin, data->cmdLine, 0))
        {
            /*execute the function, and return the return value of the function*/
            return (options[itrtor].function(data));
        }
        /*if there is no match return -1 */
    }
    return (-1);
}