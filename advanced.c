#include "shell.h"

/**
 * expVars - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expVars(progData *data)
{
    int i, j;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->inLine == NULL)
        return;
    buffAdd(line, data->inLine);
    for (i = 0; line[i]; i++)
        if (line[i] == '#')
            line[i--] = '\0';
        else if (line[i] == '$' && line[i + 1] == '?')
        {
            line[i] = '\0';
            longStr(errno, expansion, 10);
            buffAdd(line, expansion);
            buffAdd(line, data->inLine + i + 2);
        }
        else if (line[i] == '$' && line[i + 1] == '$')
        {
            line[i] = '\0';
            longStr(getpid(), expansion, 10);
            buffAdd(line, expansion);
            buffAdd(line, data->inLine + i + 2);
        }
        else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
            continue;
        else if (line[i] == '$')
        {
            for (j = 1; line[i + j] && line[i + j] != ' '; j++)
                expansion[j - 1] = line[i + j];
            temp = envGK(expansion, data);
            line[i] = '\0', expansion[0] = '\0';
            buffAdd(expansion, line + i + j);
            temp ? buffAdd(line, temp) : 1;
            buffAdd(line, expansion);
        }
    if (!myStrCmp(data->inLine, line, 0))
    {
        free(data->inLine);
        data->inLine = myStrDup(line);
    }
}

/**
 * expAlias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expAlias(progData *data)
{
    int i, j, was_expanded = 0;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->inLine == NULL)
        return;

    buffAdd(line, data->inLine);

    for (i = 0; line[i]; i++)
    {
        for (j = 0; line[i + j] && line[i + j] != ' '; j++)
            expansion[j] = line[i + j];
        expansion[j] = '\0';

        temp = getAlias(data, expansion);
        if (temp)
        {
            expansion[0] = '\0';
            buffAdd(expansion, line + i + j);
            line[i] = '\0';
            buffAdd(line, temp);
            line[myStrLen(line)] = '\0';
            buffAdd(line, expansion);
            was_expanded = 1;
        }
        break;
    }
    if (was_expanded)
    {
        free(data->inLine);
        data->inLine = myStrDup(line);
    }
}

/**
 * buffAdd - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffAdd(char *buffer, char *str_to_add)
{
    int length, i;

    length = myStrLen(buffer);
    for (i = 0; str_to_add[i]; i++)
    {
        buffer[length + i] = str_to_add[i];
    }
    buffer[length + i] = '\0';
    return (length + i);
}