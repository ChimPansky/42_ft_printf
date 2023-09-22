//#include "../include/ft_printf.h"
#include "ft_printf.h"
//#include "../libft/libft.h"

static int	get_conversion(char c, va_list arguments)
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
	return (0);
}

static int	iterate_format(const char *format, va_list arguments)
{
	int	written;
	int		invalid_format;

	written = 0;
	invalid_format = 0;
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
		format++;
	}
	if (invalid_format)
		return (-1);
	return (written);
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int	bytes_written;

	bytes_written = 0;
	va_start(arguments, format);
	bytes_written = iterate_format(format, arguments);
	va_end(arguments);
	return (bytes_written);
}
/*
int	main(void)
{
	int		ft_printed;
	int		printed;
	char	*str = "abc";


	//char *asd = 1;
	ft_printed = ft_printf("testptr1: %p\n", &str);
	printf("\nft_printed: %d", ft_printed);

	printf("\n\n\n\n");

	printed = printf("testptr1: %p\n", &str);
	printf("\nprinted: %d\n\n", printed);

	return (0);
}
*/
