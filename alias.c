#include "shell.h"

/**
 * printAlias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int printAlias(progData *data, char *alias)
{
	int i, j, aliasLen;
	char buffer[250] = {'\0'};

	if (data->aliasList)
	{
		aliasLen = myStrLen(alias);
		for (i = 0; data->aliasList[i]; i++)
		{
			if (!alias || (myStrCmp(data->aliasList[i], alias, aliasLen) && data->aliasList[i][aliasLen] == '='))
			{
				for (j = 0; data->aliasList[i][j]; j++)
				{
					buffer[j] = data->aliasList[i][j];
					if (data->aliasList[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffAdd(buffer, "'");
				buffAdd(buffer, data->aliasList[i] + j + 1);
				buffAdd(buffer, "'\n");
				aiPrint(buffer);
			}
		}
	}

	return (0);
}
