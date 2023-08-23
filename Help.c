#include "shell.h"

/**
 * freeCD - free the fields needed each loop
 * @dt: struct of the program's dt
 * Return: Nothing
 */
void freeCD(progdt *dt)
{
    if (dt->tokens)
        freeArr(dt->tokens);
    if (dt->inLine)
        free(dt->inLine);
    if (dt->cmdLine)
        free(dt->cmdLine);

    dt->inLine = NULL;
    dt->cmdLine = NULL;
    dt->tokens = NULL;
}

/**
 * freeAD - free all field of the dt
 * @dt: struct of the program's dt
 * Return: Nothing
 */
void freeAD(progdt *dt)
{
    if (dt->FD != 0)
    {
        if (close(dt->FD))
            perror(dt->progName);
    }
    freeCD(dt);
    freeArr(dt->env);
    freeArr(dt->aliasList);
}

/**
 * freeArr - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void freeArr(char **array)
{
    int i;

    if (array != NULL)
    {
        for (i = 0; array[i]; i++)
            free(array[i]);

        free(array);
        array = NULL;
    }
}