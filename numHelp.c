#include "shell.h"

/**
 * longStr - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 *
 * Return: Nothing.
 */
void longStr(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long idk = number;
	char letters[] = {"0123456789abcdef"};

	if (idk == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (idk)
	{
		if (idk < 0)
			string[index++] = letters[-(idk % base)];
		else
			string[index++] = letters[idk % base];
		idk /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	myStrRev(string);
}

/**
 * myAtoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or 0.
 */
int myAtoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * countChars - count the coincidences of character in string.
 *
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */
int countChars(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
