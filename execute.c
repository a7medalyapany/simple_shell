#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @dt: a pointer to the program's dt
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(progdt *dt)
{
    int returnVal = 0, stts;
    pid_t pidd;

    returnVal = myBuList(dt);
    if (returnVal != -1)
        return (returnVal);

    returnVal = findProg(dt);
    if (returnVal)
    {
        return (returnVal);
    }
    else
    {
        pidd = fork();
        if (pidd == -1)
        {
            perror(dt->cmdLine);
            exit(EXIT_FAILURE);
        }
        if (pidd == 0)
        {
            returnVal = execve(dt->tokens[0], dt->tokens, dt->env);
            if (returnVal == -1)
                perror(dt->cmdLine), exit(EXIT_FAILURE);
        }
        else
        {
            wait(&stts);
            if (WIFEXITED(stts))
                NoOfErr = WEXITstts(stts);
            else if (WIFSIGNALED(stts))
                NoOfErr = 128 + WTERMSIG(stts);
        }
    }
    return (0);
}