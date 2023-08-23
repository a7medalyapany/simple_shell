#include "shell.h"

/**
 * aiPrint - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and NoOfErr is set appropriately.
 */
int aiPrint(char *string)
{
    return (write(STDOUT_FILENO, string, myStrLen(string)));
}
/**
 * aiPrinte - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and NoOfErr is set appropriately.
 */
int aiPrinte(char *string)
{
    return (write(STDERR_FILENO, string, myStrLen(string)));
}

/**
 * aiPrintError - writes a array of chars in the standart error
 * @dt: a pointer to the program's dt'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and NoOfErr is set appropriately.
 */
int aiPrintError(int errorcode, progdt *dt)
{
    char n_as_string[10] = {'\0'};

    LongStr((long)dt->exeCounter, n_as_string, 10);

    if (errorcode == 2 || errorcode == 3)
    {
        aiPrinte(dt->progName);
        aiPrinte(": ");
        aiPrinte(n_as_string);
        aiPrinte(": ");
        aiPrinte(dt->tokens[0]);
        if (errorcode == 2)
            aiPrinte(": Illegal number: ");
        else
            aiPrinte(": can't cd to ");
        aiPrinte(dt->tokens[1]);
        aiPrinte("\n");
    }
    else if (errorcode == 127)
    {
        aiPrinte(dt->progName);
        aiPrinte(": ");
        aiPrinte(n_as_string);
        aiPrinte(": ");
        aiPrinte(dt->cmdLine);
        aiPrinte(": not found\n");
    }
    else if (errorcode == 126)
    {
        aiPrinte(dt->progName);
        aiPrinte(": ");
        aiPrinte(n_as_string);
        aiPrinte(": ");
        aiPrinte(dt->cmdLine);
        aiPrinte(": Permission denied\n");
    }
    return (0);
}