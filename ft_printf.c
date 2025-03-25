/* Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_print_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_print_str("(null)"));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_print_num(long n, int base)
{
	int		i;
	char	*chars;

	if (base == 10)
		chars = "0123456789";
	if (base == 16)
		chars = "0123456789abcdef";
	i = 0;
	if (n < 0)
		return (write(1, "-", 1) + ft_print_num(-n, base));
	if (n < base)
		return (write(1, &chars[n], 1));
	else
	{
		i += ft_print_num(n / base, base);
		return  (i + ft_print_num(n % base, base));
	}
	return (i);
}

int	parse_printf(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == 'd')
		i += ft_print_num((long)va_arg(args, int), 10);
	else if (c == 'x')
		i += ft_print_num((long)va_arg(args, unsigned int), 16);
	else if (c == 's')
		i += ft_print_str(va_arg(args, char *));
	else
		i += write(1, &c, 1);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;

	va_start(args, s);
	i = 0;
	while (*s)
	{
		if (*s == '%')
			i += parse_printf(*(++s), args);
		else
			i += write(1, s, 1);
		++s;
	}
	va_end(args);
	return (i);
}

int	main(void)
{
	int	i;

	i =	ft_printf("%s\n", NULL);
	printf("%d\n", i);
	i = printf("%s\n", NULL);
	printf("%d\n", i);

	i = ft_printf("Magic %s is %d\n", "number", 42);
	printf("%d\n", i);
	i = printf("Magic %s is %d\n", "number", 42);
	printf("%d\n", i);

	i = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("%d\n", i);
	i = printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("%d\n", i);

	return (0);
}