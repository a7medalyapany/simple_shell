#include "shell.h"

int check_file(char *full_path);

/**
 * findProg - find a program in path
 * @dt: a pointer to the program's dt
 * Return: 0 if success, errcode otherwise
 */

int findProg(progdt *dt)
{
    int i = 0, ret_code = 0;
    char **directories;

    if (!dt->cmdLine)
        return (2);

    if (dt->cmdLine[0] == '/' || dt->cmdLine[0] == '.')
        return (check_file(dt->cmdLine));

    free(dt->tokens[0]);
    dt->tokens[0] = myStrCon(myStrDup("/"), dt->cmdLine);
    if (!dt->tokens[0])
        return (2);

    directories = tokenizePath(dt);

    if (!directories || !directories[0])
    {
        NoOfErr = 127;
        return (127);
    }
    for (i = 0; directories[i]; i++)
    {
        directories[i] = myStrCon(directories[i], dt->tokens[0]);
        ret_code = check_file(directories[i]);
        if (ret_code == 0 || ret_code == 126)
        {
            NoOfErr = 0;
            free(dt->tokens[0]);
            dt->tokens[0] = myStrDup(directories[i]);
            freeArr(directories);
            return (ret_code);
        }
    }
    free(dt->tokens[0]);
    dt->tokens[0] = NULL;
    freeArr(directories);
    return (ret_code);
}

/**
 * tokenizePath - tokenize the path in directories
 * @dt: a pointer to the program's dt
 * Return: array of path directories
 */

char **tokenizePath(progdt *dt)
{
    int i = 0;
    int counter_directories = 2;
    char **tokens = NULL;
    char *PATH;

    PATH = env_get_key("PATH", dt);
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
            NoOfErr = 126;
            return (126);
        }
        return (0);
    }
    NoOfErr = 127;
    return (127);
}