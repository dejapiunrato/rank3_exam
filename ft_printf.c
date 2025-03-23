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

#include <stdlib.h>	// malloc y free
#include <unistd.h>	// write
#include <stdarg.h>	// va_start, va_arg, va_copy y va_end

int	ft_printf(const char *str, ...);


int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_print_str(char *s)
{
	int	i;

	if (!s)
		return(ft_printf("(null)"));
	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_print_num(long n, int base, char var)
{
	char	*chars;
	int		i;

	if (var == 'd')
		chars = "0123456789";
	if (var == 'x')
		chars = "0123456789abcdf";
	if (n < 0)
		return (write(1, "-", 1) + ft_print_num(-n, base, var));
	else if (n < base)
		return (write(1, &chars[n], 1));
	else
	{
		i = ft_print_num(n / base, base, var);
		return (i + ft_print_num(n % base, base, var));
	}
}

int	ft_printf_parse(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == 'd')
		i += ft_print_num((long)va_arg(args, int), 10, c);
	else if (c == 'x')
		i += ft_print_num((long)va_arg(args, unsigned int), 16, c);
	else if (c == 's')
		i += ft_print_str(va_arg(args, char *));
	else
		i += write(1, &c, 1);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;

	va_start(args, str);
	i = 0;
	while (*str)
	{
		if (*str == '%')
			i += ft_printf_parse(*(++str), args);
		else
			i += write(1, str, 1);
		++str;
	}
	va_end(args);
	return (0);
}

int	main(void)
{
	ft_printf("%s\n", "toto");
	ft_printf("Magic %s is %d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	return (0);
}
