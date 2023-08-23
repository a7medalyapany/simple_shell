#include "shell.h"

/**
 * myExit - exit of the program with the stts
 * @dt: struct for the program's dt
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myExit(progdt *dt)
{
    int i;

    if (dt->tokens[1] != NULL)
    {
        for (i = 0; dt->tokens[1][i]; i++)
            if ((dt->tokens[1][i] < '0' || dt->tokens[1][i] > '9') && dt->tokens[1][i] != '+')
            {
                NoOfErr = 2;
                return (2);
            }
        NoOfErr = myAtoi(dt->tokens[1]);
    }
    freeAD(dt);
    exit(NoOfErr);
}

/**
 * myCD - change the current directory
 * @dt: struct for the program's dt
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myCD(progdt *dt)
{
    char *dir_home = env_get_key("HOME", dt), *dir_old = NULL;
    char oldDir[128] = {0};
    int error_code = 0;

    if (dt->tokens[1])
    {
        if (myStrCmp(dt->tokens[1], "-", 0))
        {
            dir_old = env_get_key("OLDPWD", dt);
            if (dir_old)
                error_code = setWD(dt, dir_old);
            aiPrint(env_get_key("PWD", dt));
            aiPrint("\n");

            return (error_code);
        }
        else
        {
            return (setWD(dt, dt->tokens[1]));
        }
    }
    else
    {
        if (!dir_home)
            dir_home = getcwd(oldDir, 128);

        return (setWD(dt, dir_home));
    }
    return (0);
}

/**
 * setWD - set the work directory
 * @dt: struct for the program's dt
 * @newDir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int setWD(progdt *dt, char *newDir)
{
    char oldDir[128] = {0};
    int errCode = 0;

    getcwd(oldDir, 128);

    if (!myStrCmp(oldDir, newDir, 0))
    {
        errCode = chdir(newDir);
        if (errCode == -1)
        {
            NoOfErr = 2;
            return (3);
        }
        env_set_key("PWD", newDir, dt);
    }
    env_set_key("OLDPWD", oldDir, dt);
    return (0);
}

/**
 * BuHelp - shows the environment where the shell runs
 * @dt: struct for the program's dt
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int BuHelp(progdt *dt)
{
    int i, length = 0;
    char *idk[6] = {NULL};

    idk[0] = HELP_MSG;

    if (dt->tokens[1] == NULL)
    {
        aiPrint(idk[0] + 6);
        return (1);
    }
    if (dt->tokens[2] != NULL)
    {
        NoOfErr = E2BIG;
        perror(dt->cmdLine);
        return (5);
    }
    idk[1] = HELP_EXIT_MSG;
    idk[2] = HELP_ENV_MSG;
    idk[3] = HELP_SETENV_MSG;
    idk[4] = HELP_UNSETENV_MSG;
    idk[5] = HELP_CD_MSG;

    for (i = 0; idk[i]; i++)
    {
        length = myStrLen(dt->tokens[1]);
        if (myStrCmp(dt->tokens[1], idk[i], length))
        {
            aiPrint(idk[i] + length + 1);
            return (1);
        }
    }
    NoOfErr = EINVAL;
    perror(dt->cmdLine);
    return (0);
}

/**
 * BuAlias - add, remove or show aliases
 * @dt: struct for the program's dt
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int BuAlias(progdt *dt)
{
    int i = 0;

    if (dt->tokens[1] == NULL)
        return (printAlias(dt, NULL));

    while (dt->tokens[++i])
    {
        if (countChars(dt->tokens[i], "="))
            setAlias(dt->tokens[i], dt);
        else
            printAlias(dt, dt->tokens[i]);
    }

    return (0);
}