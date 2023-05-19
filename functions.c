#include "main.h"

/**
 * _strlen - finds length of a string
 * @s: string given
 * Return: length
 */
int _strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * _strcat - Write a function that concatenates two strings.
 *@src: source
 *@dest: destination
 * Return: Returns a pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: integer less than or equal or greater than 0
 */
int _strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	i++;
	}
	return (0);
}
#include "main.h"
/**
 * _atoi - convert a string to an integer
 * @s: given string
 * Return: integer
 */
int _atoi(char *s)
{
	int i, j, sign;
	unsigned int n, a;

	i = 0;
	sign = 1;
	n = 0;
	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
			sign *= -1;
	i++;
	}
	if (s[i] != '\0')
	{
		j = i;
		while (s[j + 1] != '\0' && (s[j + 1] >= '0' && s[j + 1] <= '9'))
			j++;
		a = 1;
		while (i <= j)
		{
			n = n + (s[j] - '0') * a;
			a *= 10;
			j--;
		}
	}
	n *= sign;
	return (n);
}
