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

	settings->flags = 0;
	settings->min_width = 0;
	settings->precision = -1;
	settings->conversion = 0;

	percent_pos = *format - 1;
	set_format_flags(format, settings);
	set_format_length(format, settings);
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
/*
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
*/
char	*add_prefix(char *s, char *pre)
{
	char	*result;

	result = ft_strjoin_free(pre, s, 2);
	if (!result)
		return (s);
	return (result);
}

char	*apply_flags_and_min_width(char *s, t_format settings)
{
	char	*result;
	char	*to_free;
	size_t	s_len;

	to_free = s;
	result = s;
	if (settings.flags & F_HASH)
	{
		if (settings.conversion == 'x' && *s != '0')
			result = add_prefix(result, "0x");
		else if (settings.conversion == 'X' && *s != '0')
			result = add_prefix(result, "0X");
	}
	if (ft_strchr("di", settings.conversion))
	{
		if (settings.flags & F_PLUS && *s != '-')
			result = add_prefix(result, "+");
		else if (settings.flags & F_SPACE  && *s != '-')
			result = add_prefix(result, " ");
	}
	if (settings.min_width)
	{
		s_len = ft_strlen(s);
		if (settings.flags & F_MINUS)
			result = ft_strrpad_free(result, ' ', settings.min_width, 1);
		else if (ft_strchr("diupxX", settings.conversion) && settings.flags & F_ZERO)
		{
			if(ft_strchr("di", settings.conversion) && *s == '-' && s_len < (size_t)settings.min_width)
			{
				*result = '0';
				result = ft_strlpad_free(result, '0', settings.min_width, 1);
				if (result)
					*result = '-';
			}
			result = ft_strlpad_free(result, '0', settings.min_width, 1);
		}
		else
			result = ft_strlpad_free(result, ' ', settings.min_width, 1);
	}
	if (!result)
		free(to_free);
	return (result);
}

char	*apply_precision(char *s, t_format settings)
{
	char	*result;
	char	*to_free;
	size_t	s_len;

	result = s;
	to_free = s;
	s_len = ft_strlen(s);
	if (settings.conversion == 's' && settings.precision >= 0)
		result = ft_substr_free(s, 0, settings.precision, 1);
	else if (ft_strchr("diupxX", settings.conversion))
	{
		if (settings.precision == 0 && *result == '0')
			*result = '\0';
		else if (settings.precision > 0)
		{
			if (ft_strchr("di", settings.conversion) && *s == '-' && s_len < (size_t)settings.precision + 1)
			{
				*result = '0';
				result = ft_strlpad_free(result, '0', settings.precision + 1, 1);
				if (result)
					*result = '-';
			}
			else
				result = ft_strlpad_free(result, '0', settings.precision, 1);
		}
	}
	if (!result)
		free(to_free);
	return (result);
}

int	print_c(int fd, t_format settings, va_list args)
{
	int		c;
	int		bytes_written;
	char	*spad;

	c = va_arg(args, int);
	bytes_written = 0;

	if (settings.min_width)
	{
		spad = ft_strreplicate(' ', settings.min_width - 1);
		if (!spad)
			return (0);
		if (!(settings.flags & F_MINUS))
			bytes_written += write(fd, spad, settings.min_width - 1);
	}
	bytes_written += write(fd, &c, 1);
	if (settings.min_width && (settings.flags & F_MINUS))
		bytes_written += write(fd, spad, settings.min_width - 1);
	if (settings.min_width)
		free(spad);
	return (bytes_written);
}

int	print_conversion(int fd, t_format settings, va_list args)
{
	int		bytes_written;
	char 	*s;		// MALLOCED
	void	*ptr;

	bytes_written = 0;
	s = NULL;
	if (settings.conversion == 'c')
		return (print_c(fd, settings, args));
	else if (settings.conversion == 's')
	{
		s = va_arg(args, char *);
		if (!s)
			s = ft_strdup("(null)");
		else
			s = ft_strdup(s);
	}
	else if (ft_strchr("di", settings.conversion))
		s = ft_itoa(va_arg(args, int));
	else if (settings.conversion == 'u')
		s = ft_itoa_base_unsigned(va_arg(args, unsigned int), "0123456789");
	else if (settings.conversion == 'x')
		s = ft_itoa_base_unsigned(va_arg(args, unsigned int), "0123456789abcdef");
	else if (settings.conversion == 'X')
		s = ft_itoa_base_unsigned(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (settings.conversion == 'p')
	{
		ptr = va_arg(args, void *);
		if (!ptr)
			s = ft_strdup("(nil)");
		else
			s = ft_itoa_base_unsigned((size_t)ptr, "0123456789abcdef");
	}
	if (!s)
		return (0);

	// todo:
	//	manipulate s: apply flags, minwidth, precision...
	s = apply_precision(s, settings);
	if (!s)
		return (0);
	if (settings.conversion == 'p' && ft_strncmp(s, "(nil)", 6))
		s = add_prefix(s, "0x");
	s = apply_flags_and_min_width(s, settings);
	if (!s)
		return (0);
	bytes_written += write(fd, s, ft_strlen(s));

	return (free(s), bytes_written);
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

	bytes_written = write(fd, "%", 1);
	(*format)++;
	return (bytes_written);
}
void	write_part(int fd, int *printed, const char **format, va_list args)
{
	t_format settings;

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
				*printed += print_conversion(fd, settings, args);
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

	if (!format)
		return (-1);
	va_start(args, format);
	printed = ft_printf_fd(1, format, args);
	va_end(args);
	return (printed);
}
