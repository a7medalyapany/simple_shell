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

    /* check for program in built ins */
    returnVal = buList(data);
    if (returnVal != -1) /* if program was found in built ins */
        return (returnVal);

    /* check for program file system */
    returnVal = findProg(data);
    if (returnVal)
    { /* if program not found */
        return (returnVal);
    }
    else
    {                  /* if program was found */
        pidd = fork(); /* create a child process */
        if (pidd == -1)
        { /* if the fork call failed */
            perror(data->cmdLine);
            exit(EXIT_FAILURE);
        }
        if (pidd == 0)
        { /* I am the child process, I execute the program*/
            returnVal = execve(data->tokens[0], data->tokens, data->env);
            if (returnVal == -1) /* if error when execve*/
                perror(data->cmdLine), exit(EXIT_FAILURE);
        }
        else
        { /* I am the father, I wait and check the exit stts of the child */
            wait(&stts);
            if (WIFEXITED(stts))
                errno = WEXITstts(stts);
            else if (WIFSIGNALED(stts))
                errno = 128 + WTERMSIG(stts);
        }
    }
    return (0);
}