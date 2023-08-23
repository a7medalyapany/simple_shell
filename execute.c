#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(progData *data)
{
	int retrnVal = 0, stts;
	pid_t pidd;

	retrnVal = buList(data);
	if (retrnVal != -1)
		return (retrnVal);

	retrnVal = findProg(data);
	if (retrnVal)
		return (retrnVal);

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
			retrnVal = execve(data->tokens[0], data->tokens, data->env);
			if (retrnVal == -1)
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

