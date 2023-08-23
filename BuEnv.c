#include "shell.h"

/**
 * myEnv - shows the environment where the shell runs
 * @dt: struct for the program's dt
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myEnv(progdt *dt)
{
    int i;
    char cpname[50] = {'\0'};
    char *var_copy = NULL;

    if (dt->tokens[1] == NULL)
        printEnv(dt);
    else
    {
        for (i = 0; dt->tokens[1][i]; i++)
        {
            if (dt->tokens[1][i] == '=')
            {
                var_copy = myStrDup(env_get_key(cpname, dt));
                if (var_copy != NULL)
                    env_set_key(cpname, dt->tokens[1] + i + 1, dt);

                printEnv(dt);
                if (env_get_key(cpname, dt) == NULL)
                {
                    aiPrint(dt->tokens[1]);
                    aiPrint("\n");
                }
                else
                {
                    env_set_key(cpname, var_copy, dt);
                    free(var_copy);
                }
                return (0);
            }
            cpname[i] = dt->tokens[1][i];
        }
        NoOfErr = 2;
        perror(dt->cmdLine);
        NoOfErr = 127;
    }
    return (0);
}

/**
 * mySetEnv - ..
 * @dt: struct for the program's dt
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int mySetEnv(progdt *dt)
{
    if (dt->tokens[1] == NULL || dt->tokens[2] == NULL)
        return (0);
    if (dt->tokens[3] != NULL)
    {
        NoOfErr = E2BIG;
        perror(dt->cmdLine);
        return (5);
    }

    env_set_key(dt->tokens[1], dt->tokens[2], dt);

    return (0);
}

/**
 * myUnSetEnv - ..
 * @dt: struct for the program's dt'
 * Return: ..
 */
int myUnSetEnv(progdt *dt)
{
    if (dt->tokens[1] == NULL)
        return (0);
    if (dt->tokens[2] != NULL)
    {
        NoOfErr = E2BIG;
        perror(dt->cmdLine);
        return (5);
    }
    env_remove_key(dt->tokens[1], dt);

    return (0);
}
return (5);
}
env_remove_key(dt->tokens[1], dt);

return (0);
}