#include "shell.h"

/**
 * aiPrint - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int aiPrint(char *string)
{
    return (write(STDOUT_FILENO, string, myStrLen(string)));
}
/**
 * aiPrinte - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int aiPrinte(char *string)
{
    return (write(STDERR_FILENO, string, myStrLen(string)));
}

/**
 * aiPrintErr - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int aiPrintErr(int errorcode, progData *data)
{
    char n_as_string[10] = {'\0'};

    longStr((long)data->exeCounter, n_as_string, 10);

    if (errorcode == 2 || errorcode == 3)
    {
        aiPrinte(data->progName);
        aiPrinte(": ");
        aiPrinte(n_as_string);
        aiPrinte(": ");
        aiPrinte(data->tokens[0]);
        if (errorcode == 2)
            aiPrinte(": Illegal number: ");
        else
            aiPrinte(": can't cd to ");
        aiPrinte(data->tokens[1]);
        aiPrinte("\n");
    }
    else if (errorcode == 127)
    {
        aiPrinte(data->progName);
        aiPrinte(": ");
        aiPrinte(n_as_string);
        aiPrinte(": ");
        aiPrinte(data->cmdLine);
        aiPrinte(": not found\n");
    }
    else if (errorcode == 126)
    {
        aiPrinte(data->progName);
        aiPrinte(": ");
        aiPrinte(n_as_string);
        aiPrinte(": ");
        aiPrinte(data->cmdLine);
        aiPrinte(": Permission denied\n");
    }
    return (0);
}