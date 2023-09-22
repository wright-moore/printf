#include "main.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

/**
 * _printf - gives output according to a format
 * @format: formats strings which haas characters and the specifiers
 * Description: this function will call the get_print() function that
 * determineswhich printing function to call depending on the conversion
 * specifiers contained into fmt
 * Return: length of the formatted output string
 */
int _printf(const char *format, ...)
{
	int (*pfunc)(va_list, flags_t *);
	const char *p;
	va_list argument;
	flags_t flags = {0, 0, 0};

	register int counter = 0;

	va_start(argument, format);
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (*p == '%')
			{
				counter += _putchar('%');
				continue;
			}
			while (get_flag(*p, &flags))
				p++;
			pfunc = get_print(*p);
			counter += (pfunc)
						   ? pfunc(argument, &flags)
						   : _printf("%%%c", *p);
		}
		else
			counter += _putchar(*p);
	}
	_putchar(-1);
	va_end(argument);
	return (counter);
}
