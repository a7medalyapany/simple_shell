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
    {              /* We are in the terminal, interactive mode */
        errno = 2; /*???????*/
        prompt = PROMPT_MSG;
    }
    errno = 0;
    showPrompt(prompt, data);
    return (0);
}

/**
 * hCRTLC - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void hCRTLC(int opr UNUSED)
{
    aiPrint("\n");
    aiPrint(PROMPT_MSG);
}

/**
 * initData - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void initData(progData *data, int argc, char *argv[], char **env)
{
    int i = 0;

    data->progName = argv[0];
    data->inLine = NULL;
    data->cmdLine = NULL;
    data->exeCounter = 0;
    /* define the file descriptor to be readed*/
    if (argc == 1)
        data->FD = STDIN_FILENO;
    else
    {
        data->FD = open(argv[1], O_RDONLY);
        if (data->FD == -1)
        {
            aiPrinte(data->progName);
            aiPrinte(": 0: Can't open ");
            aiPrinte(argv[1]);
            aiPrinte("\n");
            exit(127);
        }
    }
    data->tokens = NULL;
    data->env = malloc(sizeof(char *) * 50);
    if (env)
    {
        for (; env[i]; i++)
        {
            data->env[i] = myStrDup(env[i]);
        }
    }
    data->env[i] = NULL;
    env = data->env;

    data->aliasList = malloc(sizeof(char *) * 20);
    for (i = 0; i < 20; i++)
    {
        data->aliasList[i] = NULL;
    }
}
/**
 * showPrompt - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void showPrompt(char *prompt, progData *data)
{
    int errCode = 0, string_len = 0;

    while (++(data->exeCounter))
    {
        aiPrint(prompt);
        errCode = string_len = myGetLine(data);

        if (errCode == EOF)
        {
            freeAD(data);
            exit(errno); /* if EOF is the fisrt Char of string, exit*/
        }
        if (string_len >= 1)
        {
            expAlias(data);
            expVars(data);
            tokenize(data);
            if (data->tokens[0])
            { /* if a text is given to prompt, execute */
                errCode = execute(data);
                if (errCode != 0)
                    aiPrintErr(errCode, data);
            }
            freeCD(data);
        }
    }
}