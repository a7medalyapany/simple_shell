#include "shell.h"

/**
 * printAlias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int printAlias(progData *data, char *alias)
{
    int i, j, aliasLen;
    char buffer[250] = {'\0'};

    if (data->aliasList)
    {
        aliasLen = myStrLen(alias);
        for (i = 0; data->aliasList[i]; i++)
        {
            if (!alias || (myStrCmp(data->aliasList[i], alias, aliasLen) && data->aliasList[i][aliasLen] == '='))
            {
                for (j = 0; data->aliasList[i][j]; j++)
                {
                    buffer[j] = data->aliasList[i][j];
                    if (data->aliasList[i][j] == '=')
                        break;
                }
                buffer[j + 1] = '\0';
                buffAdd(buffer, "'");
                buffAdd(buffer, data->aliasList[i] + j + 1);
                buffAdd(buffer, "'\n");
                aiPrint(buffer);
            }
        }
    }

    return (0);
}

/**
 * getAlias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *getAlias(progData *data, char *name)
{
    int i, aliasLen;

    /* validate the arguments */
    if (name == NULL || data->aliasList == NULL)
        return (NULL);

    aliasLen = myStrLen(name);

    for (i = 0; data->aliasList[i]; i++)
    { /* Iterates through the environ and check for coincidence of the varname */
        if (myStrCmp(name, data->aliasList[i], aliasLen) &&
            data->aliasList[i][aliasLen] == '=')
        { /* returns the value of the key NAME=  when find it */
            return (data->aliasList[i] + aliasLen + 1);
        }
    }
    /* returns NULL if did not find it */
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

    /* validate the arguments */
    if (alias_string == NULL || data->aliasList == NULL)
        return (1);
    /* Iterates alias to find = char */
    for (i = 0; alias_string[i]; i++)
        if (alias_string[i] != '=')
            buffer[i] = alias_string[i];
        else
        { /* search if the value of the alias is another alias */
            temp = getAlias(data, alias_string + i + 1);
            break;
        }

    /* Iterates through the alias list and check for coincidence of the varname */
    for (j = 0; data->aliasList[j]; j++)
        if (myStrCmp(buffer, data->aliasList[j], i) &&
            data->aliasList[j][i] == '=')
        { /* if the alias alredy exist */
            free(data->aliasList[j]);
            break;
        }

    /* add the alias */
    if (temp)
    { /* if the alias already exist */
        buffAdd(buffer, "=");
        buffAdd(buffer, temp);
        data->aliasList[j] = myStrDup(buffer);
    }
    else /* if the alias does not exist */
        data->aliasList[j] = myStrDup(alias_string);
    return (0);
}