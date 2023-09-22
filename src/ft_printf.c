#include "../include/ft_printf.h"
#include "../libft/libft.h"
/*
int	convert_c(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}
int	convert_s(char *s)
{
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}
*/
int	get_conversion(char c, va_list arguments)
{
	if (c == 'c')
		return (convert_c(va_arg(arguments, int)));
	if (c == 's')
		return (convert_s(va_arg(arguments, char *)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int	written;
	int	invalid_format;
	char	prev;

	invalid_format = 0;
	written = 0;
	prev = '\0';
	va_start(arguments, format);
	//int	i;
	//i = va_arg(arguments, int);
	while (*format)
	{
		if (*format == '%')
		{
			if (*(format + 1) == '%')
			{
				ft_putchar_fd('%', 1);
				written++;
				format++;
			}
			else if (*(format + 1) == '\0' )
				invalid_format = 1;
			else if (ft_strchr("cspdiuxX", *format))
				written += get_conversion(*format, arguments);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			written++;
		}
		prev = *format;
		format++;
	}
	va_end(arguments);
	if (invalid_format)
		return (-1);
	return (written);
/*
	printf("a: %d\n",a);
	printf("c: %c\n",c);
	printf("s: %s\n",s);
	printf("p: %p\n",p);
	*/
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


	ft_putstr_fd("ft_putstr_test\n#############################\n\n", 1);

	char	*str = "%%%bcdef";
	char	*str1 = "!!!!!!";
	int		ft_printed;
	int		printed;

	ft_printed = ft_printf(str);
	printf("\nft_printed: %d", ft_printed);

	printf("\n\n\n\n");

	printed = printf(str);
	printf("\nprinted: %d", printed);


	return (0);
}
