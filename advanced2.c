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

    if (data->input_line == NULL)
        return;

    buffer_add(line, data->input_line);

    for (i = 0; line[i]; i++)
    {
        for (j = 0; line[i + j] && line[i + j] != ' '; j++)
            expansion[j] = line[i + j];
        expansion[j] = '\0';

        temp = get_alias(data, expansion);
        if (temp)
        {
            expansion[0] = '\0';
            buffer_add(expansion, line + i + j);
            line[i] = '\0';
            buffer_add(line, temp);
            line[str_length(line)] = '\0';
            buffer_add(line, expansion);
            was_expanded = 1;
        }
        break;
    }
    if (was_expanded)
    {
        free(data->input_line);
        data->input_line = str_duplicate(line);
    }
}
