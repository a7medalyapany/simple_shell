#include "shell.h"

/**
 * getAlias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *getAlias(progData *data, char *name)
{
    int i, aliasLen;

    if (name == NULL || data->aliasList == NULL)
        return (NULL);

    aliasLen = myStrLen(name);

    for (i = 0; data->aliasList[i]; i++)
    {
        if (myStrCmp(name, data->aliasList[i], aliasLen) &&
            data->aliasList[i][aliasLen] == '=')
        {
            return (data->aliasList[i] + aliasLen + 1);
        }
    }
    return (NULL);
}

/**
 * setAlias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int setAlias(char *alias_string, progData *data)
{
    int i, j;
    char buffer[250] = {'0'}, *temp = NULL;

    if (alias_string == NULL || data->aliasList == NULL)
        return (1);
    for (i = 0; alias_string[i]; i++)
        if (alias_string[i] != '=')
            buffer[i] = alias_string[i];
        else
        {
            temp = getAlias(data, alias_string + i + 1);
            break;
        }

    for (j = 0; data->aliasList[j]; j++)
        if (myStrCmp(buffer, data->aliasList[j], i) &&
            data->aliasList[j][i] == '=')
        {
            free(data->aliasList[j]);
            break;
        }

    if (temp)
    {
        buffAdd(buffer, "=");
        buffAdd(buffer, temp);
        data->aliasList[j] = myStrDup(buffer);
    }
    else
        data->aliasList[j] = myStrDup(alias_string);
    return (0);
}