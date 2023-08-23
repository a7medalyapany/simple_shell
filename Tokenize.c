#include "shell.h"
/**
 * tokenize - this function separate the string using a designed delimiter
 * @dt: a pointer to the program's dt
 * Return: an array of the different parts of the string
 */
void tokenize(progdt *dt)
{
    char *delimiter = " \t";
    int i, j, counter = 2, length;

    length = myStrLen(dt->inLine);
    if (length)
    {
        if (dt->inLine[length - 1] == '\n')
            dt->inLine[length - 1] = '\0';
    }

    for (i = 0; dt->inLine[i]; i++)
    {
        for (j = 0; delimiter[j]; j++)
        {
            if (dt->inLine[i] == delimiter[j])
                counter++;
        }
    }

    dt->tokens = malloc(counter * sizeof(char *));
    if (dt->tokens == NULL)
    {
        perror(dt->progName);
        exit(NoOfErr);
    }
    i = 0;
    dt->tokens[i] = myStrDup(myStrTok(dt->inLine, delimiter));
    dt->cmdLine = myStrDup(dt->tokens[0]);
    while (dt->tokens[i++])
    {
        dt->tokens[i] = myStrDup(myStrTok(NULL, delimiter));
    }
}