#include "ft_printf.h"

void set_format_flags(const char **format, t_format *settings)
{
	while (ft_strchr(S_FLAGS, **format))
	{
		if (**format == '#' && !(settings->flags & F_HASH))
			settings->flags += F_HASH;
		if (**format == '0' && !(settings->flags & F_ZERO))
			settings->flags += F_ZERO;
		if (**format == '-' && !(settings->flags & F_MINUS))
			settings->flags += F_MINUS;
		if (**format == ' ' && !(settings->flags & F_SPACE))
			settings->flags += F_SPACE;
		if (**format == '+' && !(settings->flags & F_PLUS))
			settings->flags += F_PLUS;
		(*format)++;
	}
}
void set_format_length(const char **format, t_format *settings)
{
	while (ft_isdigit(**format))	// set min_width
	{
		settings->min_width *= 10;
		settings->min_width += **format - '0';
		(*format)++;
	}
	if (**format == '.')	// set precision
	{
		settings->precision = 0;
		(*format)++;
		while (**format == '0')
			(*format)++;
		while (ft_isdigit(**format))
		{
			settings->precision *= 10;
			settings->precision += **format - '0';
			(*format)++;
		}
	}
}

int set_format(const char **format, t_format *settings)
{
	const char	*percent_pos;

	percent_pos = *format - 1;
	set_format_flags(format, settings);
	set_format_length(format, settings);
	//set_format_lengt_modifier(format, settings); FOR LATER
	if (!ft_strchr(S_CONVERSIONS, **format))
	{
		settings->conversion = 0;
		*format = percent_pos;
		return (0);
	}
	settings->conversion = **format;
	(*format)++;
	return (1);
}
/////////////////////////////////////////
{
	if (c == 'i' || c == 'd')
		return (ft_putnbr_base_fd(1, nbr, "0123456789"));
	if (c == 'x')
		return (ft_putunsigned_base_fd(1, nbr, "0123456789abcdef"));
	if (c == 'X')
		return (ft_putunsigned_base_fd(1, nbr, "0123456789ABCDEF"));
	return(0);
}
int	convert_unsigned_base(char c, size_t nbr)
{
	if (c == 'u')
		return (ft_putunsigned_base_fd(1, nbr, "0123456789"));
	return(0);
}
int	convert_p(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	return (2 + ft_putsizet_base_fd(1, (size_t)ptr, "0123456789abcdef"));
}
///////////
ssize_t	ft_putunsigned_base_fd(int fd, unsigned int nbr, char* base_str)
{
	ssize_t	sz;
    const   size_t base = ft_strlen(base_str);
    size_t ord;

    sz = 0;
    ord = 1;
    while (nbr / base >= ord)
        ord *= base;
    while (ord)
    {
        sz += write(fd, base_str + (nbr / ord % base), 1);
        ord /= base;
    }
	return (sz);
}

ssize_t	ft_putsizet_base_fd(int fd, size_t nbr, char* base_str)
{
	ssize_t	sz;
    const   size_t base = ft_strlen(base_str);
    size_t ord;

    sz = 0;
    ord = 1;
    while (nbr / base >= ord)
        ord *= base;
    while (ord)
    {
        sz += write(fd, base_str + (nbr / ord % base), 1);
        ord /= base;
    }
	return (sz);
}

ssize_t	ft_putnbr_base_fd(int fd, int nbr, char* base_str)
{
	if (nbr >= 0)
		return (ft_putunsigned_base_fd(fd, nbr, base_str));
	return (write(fd, "-", 1) + ft_putunsigned_base_fd(fd, -1l * nbr, base_str));
}
//////////////////////////////////////////////////////77
int	print_conversion(int fd, t_format settings, va_list args)
{
	size_t 			len;
	int				bytes_written;
	char	c;
	char 			*s;

	if (settings.conversion == 'c')
	{
		c = va_arg(args, int);
		s = &c;
		len = 1;
	}
	else if (settings.conversion == 's')
		s = va_arg(args, char *);
	else if (ft_strchr("di", settings.conversion))
		s = ft_itoa(va_arg(args, int));
	else if (settings.conversion == 'u')
		s = ft_itoa(va_arg(args, unsigned int));
	//else if (settings.conversion == 'x')
	//else if (settings.conversion == 'X')

	// todo:
	//	manipulate s: apply flags, minwidth, precision...
	if (settings.conversion != 'c')
		len = ft_strlen(s);
	bytes_written = write(fd, s, len);

	return (bytes_written);
}
int	print_regular(int fd, const char **format)
{
	size_t	i;
	int		bytes_written;

	i = 0;
	while (*(*format + i) && *(*format + i) != '%')
		i++;
	if (i > 0)
	{
		bytes_written = write(fd, *format, i);
		(*format) += i;
		return (bytes_written);
	}
	(*format)++;
	return (0);
}

int	print_percent(int fd, const char **format)
{
	int	bytes_written;

	bytes_written = write(fd, &"%", 1);
	(*format)++;
	return (bytes_written);
}
void	write_part(int fd, int *printed, const char **format, va_list args)
{
	t_format settings;

	settings.flags = 0;
	settings.min_width = 0;
	settings.precision = -1;
	settings.conversion = 0;
	if (**format == '%')
	{
		(*format)++;
		if (!(**format))
		{
			*printed = -1;
			return ;
		}
		if (**format == '%')
			*printed += print_percent(fd, format);
		else
		{
			if (set_format(format, &settings))
			{
				/*printf("SETTINGS->FLAGS: %d\n", settings.flags);
				printf("SETTINGS->MIN_WIDTH: %d\n", settings.min_width);
				printf("SETTINGS->PRECISION: %d\n", settings.precision);
				printf("SETTINGS->CONVERSION: %c\n", settings.conversion);
			*/
				*printed += print_conversion(fd, settings, args);
			}
			else
				*printed += print_percent(fd, format);
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
