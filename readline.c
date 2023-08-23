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

	if (!arrCmd[0] || (arrOPs[0] == '&' && errno != 0) ||
		(arrOPs[0] == '|' && errno == 0))
	{
		for (i = 0; arrCmd[i]; i++)
		{
			free(arrCmd[i]);
			arrCmd[i] = NULL;
		}

		bytesRead = read(data->FD, &buff, BUFFER_SIZE - 1);
		if (bytesRead == 0)
			return (-1);

		i = 0;
		do {
			arrCmd[i] = myStrDup(myStrTok(i ? NULL : buff, "\n;"));
			i = chkOps(arrCmd, i, arrOPs);
		} while (arrCmd[i++]);
	}

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

	for (j = 0; arrCmd[i] != NULL && arrCmd[i][j]; j++)
	{
		if (arrCmd[i][j] == '&' && arrCmd[i][j + 1] == '&')
		{
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

