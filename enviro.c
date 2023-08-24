#include "shell.h"

/**
 * envGK - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *envGK(char *key, progData *data)
{
	int i, keyLen = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	keyLen = myStrLen(key);

	for (i = 0; data->env[i]; i++)
	{ /* Iterates through the environ and check for coincidence of the vame */
		if (myStrCmp(key, data->env[i], keyLen) &&
			data->env[i][keyLen] == '=')
		{ /* returns the value of the key NAME=  when find it*/
			return (data->env[i] + keyLen + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * envRK - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int envRK(char *key, progData *data)
{
	int i, keyLen = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	keyLen = myStrLen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (myStrCmp(key, data->env[i], keyLen) &&
			data->env[i][keyLen] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * envSK - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int envSK(char *key, char *value, progData *data)
{
	int i, keyLen = 0, isNewKey = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	keyLen = myStrLen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (myStrCmp(key, data->env[i], keyLen) &&
			data->env[i][keyLen] == '=')
		{
			isNewKey = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = myStrCon(myStrDup(key), "=");
	data->env[i] = myStrCon(data->env[i], value);

	if (isNewKey)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * printEnv - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void printEnv(progData *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		aiPrint(data->env[j]);
		aiPrint("\n");
	}
}
