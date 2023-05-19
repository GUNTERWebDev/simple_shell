#include  "main.h"
/**
 * main - print _putchar
 * is written by mbah
 * Return: On sucess 1
 * on error -1
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
