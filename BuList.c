#include "shell.h"

/**
 * myBuList - search for match and execute the associate builtin
 * @dt: struct for the program's dt
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int myBuList(progdt *dt)
{
    int iterator;
    builtins options[] = {
        {"exit", myExit},
        {"help", BuHelp},
        {"cd", myCD},
        {"alias", BuAlias},
        {"env", myEnv},
        {"setenv", mySetEnv},
        {"unsetenv", myUnSetEnv},
        {NULL, NULL}};

    for (iterator = 0; options[iterator].builtin != NULL; iterator++)
    {
        if (myStrCmp(options[iterator].builtin, dt->cmdLine, 0))
        {
            return (options[iterator].function(dt));
        }
    }
    return (-1);
}