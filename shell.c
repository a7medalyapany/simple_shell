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
    progdt ds = {NULL}, *dt = &ds;
    char *prompt = "";

    initdt(dt, argc, argv, env);

    signal(SIGINT, hCRTLC);

    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
    {                /* We are in the terminal, interactive mode */
        NoOfErr = 2; /*???????*/
        prompt = PROMPT_MSG;
    }
    NoOfErr = 0;
    showProp(prompt, dt);
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
 * initdt - inicialize the struct with the info of the program
 * @dt: pointer to the structure of dt
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void initdt(progdt *dt, int argc, char *argv[], char **env)
{
    int i = 0;

    dt->progName = argv[0];
    dt->inLine = NULL;
    dt->cmdLine = NULL;
    dt->exeCounter = 0;
    /* define the file descriptor to be readed*/
    if (argc == 1)
        dt->FD = STDIN_FILENO;
    else
    {
        dt->FD = open(argv[1], O_RDONLY);
        if (dt->FD == -1)
        {
            aiPrinte(dt->progName);
            aiPrinte(": 0: Can't open ");
            aiPrinte(argv[1]);
            aiPrinte("\n");
            exit(127);
        }
    }
    dt->tokens = NULL;
    dt->env = malloc(sizeof(char *) * 50);
    if (env)
    {
        for (; env[i]; i++)
        {
            dt->env[i] = myStrDup(env[i]);
        }
    }
    dt->env[i] = NULL;
    env = dt->env;

    dt->aliasList = malloc(sizeof(char *) * 20);
    for (i = 0; i < 20; i++)
    {
        dt->aliasList[i] = NULL;
    }
}
/**
 * showProp - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @dt: its a infinite loop that shows the prompt
 */
void showProp(char *prompt, progdt *dt)
{
    int error_code = 0, string_len = 0;

    while (++(dt->exeCounter))
    {
        aiPrint(prompt);
        error_code = string_len = myGetLine(dt);

        if (error_code == EOF)
        {
            freeAD(dt);
            exit(NoOfErr); /* if EOF is the fisrt Char of string, exit*/
        }
        if (string_len >= 1)
        {
            expand_alias(dt);
            expand_variables(dt);
            tokenize(dt);
            if (dt->tokens[0])
            { /* if a text is given to prompt, execute */
                error_code = execute(dt);
                if (error_code != 0)
                    aiPrintError(error_code, dt);
            }
            freeCD(dt);
        }
    }
}