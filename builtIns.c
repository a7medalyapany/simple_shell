#include "shell.h"

/**
 * myExit - exit of the program with the stts
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myExit(progData *data)
{
    int i;

    if (data->tokens[1] != NULL)
    {
        for (i = 0; data->tokens[1][i]; i++)
            if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9') && data->tokens[1][i] != '+')
            {
                errno = 2;
                return (2);
            }
        errno = myAtoi(data->tokens[1]);
    }
    freeAD(data);
    exit(errno);
}

/**
 * myCD - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myCD(progData *data)
{
    char *dirHome = envGK("HOME", data), *dirOld = NULL;
    char oldDir[128] = {0};
    int errCode = 0;

    if (data->tokens[1])
    {
        if (myStrCmp(data->tokens[1], "-", 0))
        {
            dirOld = envGK("OLDPWD", data);
            if (dirOld)
                errCode = setWD(data, dirOld);
            aiPrint(envGK("PWD", data));
            aiPrint("\n");

            return (errCode);
        }
        else
        {
            return (setWD(data, data->tokens[1]));
        }
    }
    else
    {
        if (!dirHome)
            dirHome = getcwd(oldDir, 128);

        return (setWD(data, dirHome));
    }
    return (0);
}

/**
 * setWD - set the work directory
 * @data: struct for the program's data
 * @newDir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int setWD(progData *data, char *newDir)
{
    char oldDir[128] = {0};
    int err_code = 0;

    getcwd(oldDir, 128);

    if (!myStrCmp(oldDir, newDir, 0))
    {
        err_code = chdir(newDir);
        if (err_code == -1)
        {
            errno = 2;
            return (3);
        }
        envSK("PWD", newDir, data);
    }
    envSK("OLDPWD", oldDir, data);
    return (0);
}

/**
 * myHelp - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myHelp(progData *data)
{
    int i, len = 0;
    char *mensajes[6] = {NULL};

    mensajes[0] = HELP_MSG;

    if (data->tokens[1] == NULL)
    {
        aiPrint(mensajes[0] + 6);
        return (1);
    }
    if (data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->cmdLine);
        return (5);
    }
    mensajes[1] = HELP_EXIT_MSG;
    mensajes[2] = HELP_ENV_MSG;
    mensajes[3] = HELP_SETENV_MSG;
    mensajes[4] = HELP_UNSETENV_MSG;
    mensajes[5] = HELP_CD_MSG;

    for (i = 0; mensajes[i]; i++)
    {
        len = myStrLen(data->tokens[1]);
        if (myStrCmp(data->tokens[1], mensajes[i], len))
        {
            aiPrint(mensajes[i] + len + 1);
            return (1);
        }
    }
    errno = EINVAL;
    perror(data->cmdLine);
    return (0);
}

/**
 * myAlias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myAlias(progData *data)
{
    int i = 0;

    if (data->tokens[1] == NULL)
        return (printAlias(data, NULL));

    while (data->tokens[++i])
    {
        if (countChars(data->tokens[i], "="))
            setAlias(data->tokens[i], data);
        else
            printAlias(data, data->tokens[i]);
    }

    return (0);
}