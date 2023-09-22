#include "../include/ft_printf.h"
#include "../libft/libft.h"

int	get_conversion(char c, va_list arguments)
{
	if (c == 'c')
		return (convert_c(va_arg(arguments, int)));
	if (c == 's')
		return (convert_s(va_arg(arguments, char *)));
	if (ft_strchr("dixX", c))
		return (convert_base(c, va_arg(arguments, int)));
	if (ft_strchr("u", c))
		return (convert_unsigned_base(c, va_arg(arguments, size_t)));
	if (c == 'p')
		return (convert_p(va_arg(arguments, void *)));

	/*if (c == 'u')
		return (convert_u(va_arg(arguments, char *)));
	if (c == 'p')
		return (convert_p(va_arg(arguments, char *)));
	*/
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
			else if (ft_strchr("cspdiuxX", *(format + 1)))
			{
				written += get_conversion(*(format + 1), arguments);
				format++;
			}
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


	char	*str1 = "!!!!!!";
	int		testnr;
	size_t	testu;
	int		testx;
	int		ft_printed;
	int		printed;
	char	*str = "testptr: %p\n";

	testnr = 5324;
	testu = 2147483648;
	testx = 235325;

	char *asd = 1;

	ft_printed = ft_printf(str, &str);
	printf("\nft_printed: %d", ft_printed);

	printf("\n\n\n\n");

	printed = printf(str, &str);
	printf("\nprinted: %d\n\n", printed);

	//ft_putnbr_base_fd(1, 45, "0123456789abcdef");

	return (0);
}
