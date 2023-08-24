#include "shell.h"

/**
 * myExit - exit of the program with the stts
 * @data: struct for the program's data
 * Return: zero if sucess, or other number
 */
int myExit(progData *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' ||
				 data->tokens[1][i] > '9') &&
				data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = myAtoi(data->tokens[1]);
	}
	freeAD(data);
	exit(errno);
}

/**
 * myHelp - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number
 */
int myHelp(progData *data)
{
	int i, len = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		aiPrint(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmdLine);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		len = myStrLen(data->tokens[1]);
		if (myStrCmp(data->tokens[1], mensajes[i], len))
		{
			aiPrint(mensajes[i] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->cmdLine);
	return (0);
}
