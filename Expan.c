#include "shell.h"

/**
 * expand_variables - expand variables
 * @dt: a pointer to a struct of the program's dt
 *
 * Return: nothing, but sets NoOfErr.
 */
void expand_variables(progdt *dt)
{
    int i, j;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (dt->inLine == NULL)
        return;
    buffer_add(line, dt->inLine);
    for (i = 0; line[i]; i++)
        if (line[i] == '#')
            line[i--] = '\0';
        else if (line[i] == '$' && line[i + 1] == '?')
        {
            line[i] = '\0';
            LongStr(NoOfErr, expansion, 10);
            buffer_add(line, expansion);
            buffer_add(line, dt->inLine + i + 2);
        }
        else if (line[i] == '$' && line[i + 1] == '$')
        {
            line[i] = '\0';
            LongStr(getpid(), expansion, 10);
            buffer_add(line, expansion);
            buffer_add(line, dt->inLine + i + 2);
        }
        else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
            continue;
        else if (line[i] == '$')
        {
            for (j = 1; line[i + j] && line[i + j] != ' '; j++)
                expansion[j - 1] = line[i + j];
            temp = env_get_key(expansion, dt);
            line[i] = '\0', expansion[0] = '\0';
            buffer_add(expansion, line + i + j);
            temp ? buffer_add(line, temp) : 1;
            buffer_add(line, expansion);
        }
    if (!myStrCmp(dt->inLine, line, 0))
    {
        free(dt->inLine);
        dt->inLine = myStrDup(line);
    }
}

/**
 * expand_alias - expans aliases
 * @dt: a pointer to a struct of the program's dt
 *
 * Return: nothing, but sets NoOfErr.
 */
void expand_alias(progdt *dt)
{
    int i, j, was_expanded = 0;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (dt->inLine == NULL)
        return;

    buffer_add(line, dt->inLine);

    for (i = 0; line[i]; i++)
    {
        for (j = 0; line[i + j] && line[i + j] != ' '; j++)
            expansion[j] = line[i + j];
        expansion[j] = '\0';

        temp = getAlias(dt, expansion);
        if (temp)
        {
            expansion[0] = '\0';
            buffer_add(expansion, line + i + j);
            line[i] = '\0';
            buffer_add(line, temp);
            line[myStrLen(line)] = '\0';
            buffer_add(line, expansion);
            was_expanded = 1;
        }
        break;
    }
    if (was_expanded)
    {
        free(dt->inLine);
        dt->inLine = myStrDup(line);
    }
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets NoOfErr.
 */
int buffer_add(char *buffer, char *str_to_add)
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