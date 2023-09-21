#include "../include/ft_printf.h"
#include "../libft/libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	arguments;

	va_start(arguments, format);
	//int	i;
	//i = va_arg(arguments, int);
	while (*format)
	{
		if (*format == '%')


	}
	va_end(arguments);

	printf("a: %d\n",a);
	printf("c: %c\n",c);
	printf("s: %s\n",s);
	printf("p: %p\n",p);
	// TK:
	// handle variadic parameters...
	//iterate format string and output simple characters, or call conversion functions for every % encountered....
	// use ft_putchar_fd and ft_putstr_fd with fd=1 for output

}

int	main(void)
{
	enum e_flags	fflags;
	t_format	d_format;

	d_format.flags = 0;
	if ('#' == '#')
		d_format.flags += F_HASH;
	if ('0' == '0')
		d_format.flags += F_ZERO;
	if ('-' == '-')
		d_format.flags += F_MINUS;
	if (' ' == 'X')
		d_format.flags += F_SPACE;
	if ('.' == '.')
		d_format.flags += F_DOT;

	if (d_format.flags & F_HASH)
		printf("flags has Hash\n");
	if (d_format.flags & F_MINUS)
		printf("flags has Minus\n");
	if (d_format.flags & F_SPACE)
		printf("flags has Space\n");
	if (d_format.flags & F_DOT)
		printf("flags has Dot\n");


	ft_putstr_fd("ft_putstr_test\n\n\n", 1);

	char	*str = "abc";
	ft_printf("test var_arg: ", 15, 'A', str, &str);
	return (0);
}
