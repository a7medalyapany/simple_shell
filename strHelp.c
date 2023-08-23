#include "shell.h"

/**
 * myStrLen - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int myStrLen(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * myStrDup - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *myStrDup(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = myStrLen(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * myStrCmp - Compare two strings
 * @string1: String one, or the shorter
 * @string2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int myStrCmp(char *string1, char *string2, int number)
{
	int itrtor;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (myStrLen(string1) != myStrLen(string2))
			return (0);
		for (itrtor = 0; string1[itrtor]; itrtor++)
		{
			if (string1[itrtor] != string2[itrtor])
				return (0);
		}
		return (1);
	}
	else
	{
		for (itrtor = 0; itrtor < number; itrtor++)
		{
			if (string1[itrtor] != string2[itrtor])
				return (0);
		}
		return (1);
	}
}

/**
 * myStrCon - concatenates two strings.
 * @string1: String to be concatenated
 * @string2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *myStrCon(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = myStrLen(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = myStrLen(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);

	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}

/**
 * myStrRev - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void myStrRev(char *string)
{

	int i = 0, length = myStrLen(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}