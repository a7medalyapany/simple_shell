#include "shell.h"

/**
 * mySetEnv - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int mySetEnv(progData *data)
{
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