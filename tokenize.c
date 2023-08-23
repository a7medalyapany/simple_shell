#include "shell.h"
/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(progData *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = myStrLen(data->inLine);
	if (length)
	{
		if (data->inLine[length - 1] == '\n')
			data->inLine[length - 1] = '\0';
	}

	for (i = 0; data->inLine[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->inLine[i] == delimiter[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->progName);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = myStrDup(myStrTok(data->inLine, delimiter));
	data->cmdLine = myStrDup(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = myStrDup(myStrTok(NULL, delimiter));
	}
}

