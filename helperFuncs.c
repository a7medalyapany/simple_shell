#include "shell.h"

/**
 * freeCD - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void freeCD(progData *data)
{
	if (data->tokens)
		freeArr(data->tokens);
	if (data->inLine)
		free(data->inLine);
	if (data->cmdLine)
		free(data->cmdLine);

	data->inLine = NULL;
	data->cmdLine = NULL;
	data->tokens = NULL;
}

/**
 * freeAD - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void freeAD(progData *data)
{
	if (data->FD != 0)
	{
		if (close(data->FD))
			perror(data->progName);
	}
	freeCD(data);
	freeArr(data->env);
	freeArr(data->aliasList);
}

/**
 * freeArr - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void freeArr(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}