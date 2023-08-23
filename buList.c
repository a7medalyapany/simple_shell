#include "shell.h"

/**
 * buList - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int buList(progData *data)
{
	int itrtor;
	builtins options[] = {
		{"exit", myExit},
		{"help", myHelp},
		{"cd", myCD},
		{"alias", myAlias},
		{"env", myEnv},
		{"setenv", mySetEnv},
		{"unsetenv", myUnSetEnv},
		{NULL, NULL}};

	for (itrtor = 0; options[itrtor].builtin != NULL; itrtor++)
	{
		if (myStrCmp(options[itrtor].builtin, data->cmdLine, 0))
		{
			return (options[itrtor].function(data));
		}
	}
	return (-1);
}