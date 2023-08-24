#include "shell.h"

/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	progData ds = {NULL}, *data = &ds;
	char *prompt = "";

	initData(data, argc, argv, env);

	signal(SIGINT, hCRTLC);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	showPrompt(prompt, data);
	return (0);
}
