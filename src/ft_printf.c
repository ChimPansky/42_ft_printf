#include "ft_printf.h"

int get_settings(const char **format, t_format *settings)
{
	index = ft_strchr(s_flags, *form);////////////////////////
	while (index && *form)
	{
		form++;
		printf("%s\n", index);
		index = ft_strchr(s_flags, *form);
	}
}

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
	if (**format == 'd')
	{
		s = ft_itoa(va_arg(args, int));
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
	t_format settings;

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
		{
			if (get_settings(format, &settings))
				*printed += print_conversion(fd, format, settings, args);
		}
	}
	else
		*printed += print_regular(fd, format);
}

int	ft_printf_fd(int fd, const char *format, va_list args)
{
	int	printed;

	printed = 0;

	while (*format)
		write_part(fd, &printed, &format, args);
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	int printed;
	va_list args;

	va_start(args, format);
	printed = ft_printf_fd(1, format, args);
	va_end(args);
	return (printed);
}
