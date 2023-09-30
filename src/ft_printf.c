#include "ft_printf.h"

int	print_conversion(int fd, const char **format, va_list args)
{
	size_t len;
	char 	*s;

	len = 0;
	if (**format == 's')
	{
		s = va_arg(args, char *);
		len = ft_strlen(s);
		write(fd, s, len);
	}
	(*format)++;
	return (len);
}
int	print_regular(int fd, const char **format)
{
	size_t	i;

	i = 0;
	while (*(*format + i) && *(*format + i) != '%')
		i++;
	//ft_putnbr_fd(1,i);
	if (i > 0)
	{
		write(fd, *format, i);
		(*format) += i;
		return (i);
	}
	(*format)++;
	return (0);
}

void	write_part(int fd, int *printed, const char **format, va_list args)
{
	if (**format == '%')
	{
		(*format)++;
		if (!**format)
			return ;
		if (**format == '%')
		{
			write(fd, &"%", 1);
			(*format)++;
			(*printed)++;
		}
		else
			*printed += print_conversion(fd, format, args);
	}
	else
		*printed += print_regular(fd, format);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int	printed;
	va_list args;

	printed = 0;
	va_start(args, format);
	while (*format)
		write_part(fd, &printed, &format, args);
	va_end(args);
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	return ft_printf_fd(1, format, args);
}
