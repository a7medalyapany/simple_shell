#include "shell.h"

/**
 * myEnv - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myEnv(progData *data)
{
    int i;
    char cpname[50] = {'\0'};
    char *var_copy = NULL;

    /* if not arguments */
    if (data->tokens[1] == NULL)
        printEnv(data);
    else
    {
        for (i = 0; data->tokens[1][i]; i++)
        { /* checks if exists a char = */
            if (data->tokens[1][i] == '=')
            { /* checks if exists a var with the same name and change its value*/
                /* temporally */
                var_copy = myStrDup(envGK(cpname, data));
                if (var_copy != NULL)
                    envSK(cpname, data->tokens[1] + i + 1, data);

                /* print the environ */
                printEnv(data);
                if (envGK(cpname, data) == NULL)
                { /* print the variable if it does not exist in the environ */
                    aiPrint(data->tokens[1]);
                    aiPrint("\n");
                }
                else
                { /* returns the old value of the var*/
                    envSK(cpname, var_copy, data);
                    free(var_copy);
                }
                return (0);
            }
            cpname[i] = data->tokens[1][i];
        }
        errno = 2;
        perror(data->cmdLine);
        errno = 127;
    }
    return (0);
}

/**
 * mySetEnv - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int mySetEnv(progData *data)
{
    /* validate args */
    if (data->tokens[1] == NULL || data->tokens[2] == NULL)
        return (0);
    if (data->tokens[3] != NULL)
    {
        errno = E2BIG;
        perror(data->cmdLine);
        return (5);
    }

    envSK(data->tokens[1], data->tokens[2], data);

    return (0);
}

/**
 * myUnSetEnv - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int myUnSetEnv(progData *data)
{
    /* validate args */
    if (data->tokens[1] == NULL)
        return (0);
    if (data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->cmdLine);
        return (5);
    }
    envRK(data->tokens[1], data);

    return (0);
}