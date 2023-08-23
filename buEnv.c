#include "shell.h"

/**
 * myEnv - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int myEnv(progData *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		printEnv(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = myStrDup(envGK(cpname, data));
				if (var_copy != NULL)
					envSK(cpname, data->tokens[1] + i + 1, data);

				printEnv(data);
				if (envGK(cpname, data) == NULL)
				{
					aiPrint(data->tokens[1]);
					aiPrint("\n");
				}
				else
				{
					envSK(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->cmdLine);
		errno = 127;
	}
	return (0);
}
