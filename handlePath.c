#include "shell.h"

int check_file(char *full_path);

/**
 * findProg - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int findProg(progData *data)
{
	int i = 0, retCode = 0;
	char **directories;

	if (!data->cmdLine)
		return (2);

	if (data->cmdLine[0] == '/' || data->cmdLine[0] == '.')
		return (check_file(data->cmdLine));

	free(data->tokens[0]);
	data->tokens[0] = myStrCon(myStrDup("/"), data->cmdLine);
	if (!data->tokens[0])
		return (2);

	directories = tokenizePath(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		directories[i] = myStrCon(directories[i], data->tokens[0]);
		retCode = check_file(directories[i]);
		if (retCode == 0 || retCode == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = myStrDup(directories[i]);
			freeArr(directories);
			return (retCode);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	freeArr(directories);
	return (retCode);
}

/**
 * tokenizePath - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **tokenizePath(progData *data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = envGK("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = myStrDup(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	tokens = malloc(sizeof(char *) * counter_directories);

	i = 0;
	tokens[i] = myStrDup(myStrTok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = myStrDup(myStrTok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}

