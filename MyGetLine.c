#include "shell.h"

/**
 * myGetLine - read one line from the prompt.
 * @dt: struct for the program's dt
 *
 * Return: reading counting bytes.
 */
int myGetLine(progdt *dt)
{
    char buff[BUFFER_SIZE] = {'\0'};
    static char *arrCmd[10] = {NULL};
    static char arrOp[10] = {'\0'};
    ssize_t bytesRead, i = 0;

    if (!arrCmd[0] || (arrOp[0] == '&' && NoOfErr != 0) ||
        (arrOp[0] == '|' && NoOfErr == 0))
    {
        for (i = 0; arrCmd[i]; i++)
        {
            free(arrCmd[i]);
            arrCmd[i] = NULL;
        }

        bytesRead = read(dt->FD, &buff, BUFFER_SIZE - 1);
        if (bytesRead == 0)
            return (-1);

        i = 0;
        do
        {
            arrCmd[i] = myStrDup(myStrTok(i ? NULL : buff, "\n;"));
            i = check_logic_ops(arrCmd, i, arrOp);
        } while (arrCmd[i++]);
    }

    dt->inLine = arrCmd[0];
    for (i = 0; arrCmd[i]; i++)
    {
        arrCmd[i] = arrCmd[i + 1];
        arrOp[i] = arrOp[i + 1];
    }

    return (myStrLen(dt->inLine));
}

/**
 * check_logic_ops - checks and split for && and || operators
 * @arrCmd: array of the commands.
 * @i: index in the arrCmd to be checked
 * @arrOp: array of the logical operators for each previous command
 *
 * Return: index of the last command in the arrCmd.
 */
int check_logic_ops(char *arrCmd[], int i, char arrOp[])
{
    char *temp = NULL;
    int j;

    for (j = 0; arrCmd[i] != NULL && arrCmd[i][j]; j++)
    {
        if (arrCmd[i][j] == '&' && arrCmd[i][j + 1] == '&')
        {
            temp = arrCmd[i];
            arrCmd[i][j] = '\0';
            arrCmd[i] = myStrDup(arrCmd[i]);
            arrCmd[i + 1] = myStrDup(temp + j + 2);
            i++;
            arrOp[i] = '&';
            free(temp);
            j = 0;
        }
        if (arrCmd[i][j] == '|' && arrCmd[i][j + 1] == '|')
        {
            temp = arrCmd[i];
            arrCmd[i][j] = '\0';
            arrCmd[i] = myStrDup(arrCmd[i]);
            arrCmd[i + 1] = myStrDup(temp + j + 2);
            i++;
            arrOp[i] = '|';
            free(temp);
            j = 0;
        }
    }
    return (i);
}