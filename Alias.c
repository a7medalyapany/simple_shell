#include "shell.h"

/**
 * printAlias - add, remove or show aliases
 * @dt: struct for the program's dt
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int printAlias(progdt *dt, char *alias)
{
    int i, j, alias_length;
    char buffer[250] = {'\0'};

    if (dt->aliasList)
    {
        alias_length = myStrLen(alias);
        for (i = 0; dt->aliasList[i]; i++)
        {
            if (!alias || (myStrCmp(dt->aliasList[i], alias, alias_length) && dt->aliasList[i][alias_length] == '='))
            {
                for (j = 0; dt->aliasList[i][j]; j++)
                {
                    buffer[j] = dt->aliasList[i][j];
                    if (dt->aliasList[i][j] == '=')
                        break;
                }
                buffer[j + 1] = '\0';
                buffer_add(buffer, "'");
                buffer_add(buffer, dt->aliasList[i] + j + 1);
                buffer_add(buffer, "'\n");
                aiPrint(buffer);
            }
        }
    }

    return (0);
}

/**
 * getAlias - add, remove or show aliases
 * @dt: struct for the program's dt
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *getAlias(progdt *dt, char *name)
{
    int i, alias_length;

    if (name == NULL || dt->aliasList == NULL)
        return (NULL);

    alias_length = myStrLen(name);

    for (i = 0; dt->aliasList[i]; i++)
    {
        if (myStrCmp(name, dt->aliasList[i], alias_length) &&
            dt->aliasList[i][alias_length] == '=')
        {
            return (dt->aliasList[i] + alias_length + 1);
        }
    }

    return (NULL);
}

/**
 * setAlias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @dt: struct for the program's dt
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int setAlias(char *alias_string, progdt *dt)
{
    int i, j;
    char buffer[250] = {'0'}, *temp = NULL;

    if (alias_string == NULL || dt->aliasList == NULL)
        return (1);

    for (i = 0; alias_string[i]; i++)
    {
        if (alias_string[i] != '=')
            buffer[i] = alias_string[i];
        else
        {
            temp = getAlias(dt, alias_string + i + 1);
            break;
        }
    }

    for (j = 0; dt->aliasList[j]; j++)
    {
        if (myStrCmp(buffer, dt->aliasList[j], i) &&
            dt->aliasList[j][i] == '=')
        {
            free(dt->aliasList[j]);
            break;
        }
    }

    if (temp)
    {
        buffer_add(buffer, "=");
        buffer_add(buffer, temp);
        dt->aliasList[j] = myStrDup(buffer);
    }
    else
    {
        dt->aliasList[j] = myStrDup(alias_string);
    }

    return (0);
}