#include "shell.h"

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
