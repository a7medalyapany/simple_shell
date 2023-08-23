#include "shell.h"

/**
 * myGetLine - read one line from the prompt.
 * @data: struct for the program's data
 *
 * Return: reading counting bytes.
 */
int myGetLine(progData *data)
{
    char buff[BUFFER_SIZE] = {'\0'};
    static char *arrCmd[10] = {NULL};
    static char arrOPs[10] = {'\0'};
    ssize_t bytesRead, i = 0;

    /* check if doesnot exist more commands in the array */
    /* and checks the logical operators */
    if (!arrCmd[0] || (arrOPs[0] == '&' && errno != 0) ||
        (arrOPs[0] == '|' && errno == 0))
    {
        /*free the memory allocated in the array if it exists */
        for (i = 0; arrCmd[i]; i++)
        {
            free(arrCmd[i]);
            arrCmd[i] = NULL;
        }

        /* read from the file descriptor int to buff */
        bytesRead = read(data->FD, &buff, BUFFER_SIZE - 1);
        if (bytesRead == 0)
            return (-1);

        /* split lines for \n or ; */
        i = 0;
        do
        {
            arrCmd[i] = myStrDup(myStrTok(i ? NULL : buff, "\n;"));
            /*checks and split for && and || operators*/
            i = chkOps(arrCmd, i, arrOPs);
        } while (arrCmd[i++]);
    }

    /*obtains the next command (command 0) and remove it for the array*/
    data->inLine = arrCmd[0];
    for (i = 0; arrCmd[i]; i++)
    {
        arrCmd[i] = arrCmd[i + 1];
        arrOPs[i] = arrOPs[i + 1];
    }

    return (myStrLen(data->inLine));
}

/**
 * chkOps - checks and split for && and || operators
 * @arrCmd: array of the commands.
 * @i: index in the arrCmd to be checked
 * @arrOPs: array of the logical operators for each previous command
 *
 * Return: index of the last command in the arrCmd.
 */
int chkOps(char *arrCmd[], int i, char arrOPs[])
{
    char *temp = NULL;
    int j;

    /* checks for the & char in the command line*/
    for (j = 0; arrCmd[i] != NULL && arrCmd[i][j]; j++)
    {
        if (arrCmd[i][j] == '&' && arrCmd[i][j + 1] == '&')
        {
            /* split the line when chars && was found */
            temp = arrCmd[i];
            arrCmd[i][j] = '\0';
            arrCmd[i] = myStrDup(arrCmd[i]);
            arrCmd[i + 1] = myStrDup(temp + j + 2);
            i++;
            arrOPs[i] = '&';
            free(temp);
            j = 0;
        }
        if (arrCmd[i][j] == '|' && arrCmd[i][j + 1] == '|')
        {
            /* split the line when chars || was found */
            temp = arrCmd[i];
            arrCmd[i][j] = '\0';
            arrCmd[i] = myStrDup(arrCmd[i]);
            arrCmd[i + 1] = myStrDup(temp + j + 2);
            i++;
            arrOPs[i] = '|';
            free(temp);
            j = 0;
        }
    }
    return (i);
}