#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(progData *data)
{
	int returnVal = 0, stts;
	pid_t pidd;

	returnVal = buList(data);
	if (returnVal != -1)
		return (returnVal);

	returnVal = findProg(data);
	if (returnVal)
	{
		return (returnVal);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->cmdLine);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			returnVal = execve(data->tokens[0], data->tokens, data->env);
			if (returnVal == -1)
				perror(data->cmdLine), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&stts);
			if (WIFEXITED(stts))
				errno = WEXITSTATUS(stts);
			else if (WIFSIGNALED(stts))
				errno = 128 + WTERMSIG(stts);
		}
	}
	return (0);
}