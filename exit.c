#include "shell.h"
/**
 * _strncat - a function that concatenates two strings
 * @dest: pointer to dest
 * @src: pointer to src
 * @n: numbers
 * Return: pointer to result
 */
char *_strncat(char *dest, char *src, int n)
{
	int st1, st2;
	char *st = dest;

	st1 = 0;
	st2 = 0;
	while (dest[st1] != '\0')
		st1++;
	while (src[st2] != '\0' && st2 < n)
	{
		dest[st1] = src[st2];
		st1++;
		st2++;
	}
	if (st2 < n)
		dest[st1] = '\0';
	return (st);
}
/**
 * *_strncpy -  copies the string pointed to by src
 * @dest: type string
 * @src: type string
 * @n: numbers
 * Return: pointer to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *st = dest;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (st);
}
/**
 * *_strchr - function that locates a character in a string
 * @c: char
 * @s: string
 * Return: nothing
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
