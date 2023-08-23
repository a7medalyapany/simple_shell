#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @dt: struct of the program's dt
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, progdt *dt)
{
    int i, key_length = 0;

    if (key == NULL || dt->env == NULL)
        return (NULL);

    key_length = myStrLen(key);

    for (i = 0; dt->env[i]; i++)
    {
        if (myStrCmp(key, dt->env[i], key_length) &&
            dt->env[i][key_length] == '=')
        { /* returns the value of the key NAME=  when find it*/
            return (dt->env[i] + key_length + 1);
        }
    }
    return (NULL);
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @dt: struct of the program's dt
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_set_key(char *key, char *value, progdt *dt)
{
    int i, key_length = 0, is_new_key = 1;

    if (key == NULL || value == NULL || dt->env == NULL)
        return (1);

    key_length = myStrLen(key);

    for (i = 0; dt->env[i]; i++)
    {
        if (myStrCmp(key, dt->env[i], key_length) &&
            dt->env[i][key_length] == '=')
        {
            is_new_key = 0;
            free(dt->env[i]);
            break;
        }
    }
    dt->env[i] = myStrCon(myStrDup(key), "=");
    dt->env[i] = myStrCon(dt->env[i], value);

    if (is_new_key)
    {
        dt->env[i + 1] = NULL;
    }
    return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @dt: the sructure of the program's dt
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, progdt *dt)
{
    int i, key_length = 0;

    if (key == NULL || dt->env == NULL)
        return (0);

    key_length = myStrLen(key);

    for (i = 0; dt->env[i]; i++)
    {
        if (myStrCmp(key, dt->env[i], key_length) &&
            dt->env[i][key_length] == '=')
        {
            free(dt->env[i]);

            i++;
            for (; dt->env[i]; i++)
            {
                dt->env[i - 1] = dt->env[i];
            }
            dt->env[i - 1] = NULL;
            return (1);
        }
    }
    return (0);
}

/**
 * printEnv - prints the current environ
 * @dt: struct for the program's dt
 * Return: nothing
 */
void printEnv(progdt *dt)
{
    int j;

    for (j = 0; dt->env[j]; j++)
    {
        aiPrint(dt->env[j]);
        aiPrint("\n");
    }
}