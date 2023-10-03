#include "ft_printf_p.h"

static void	write_next(int fd, const char **format, va_list ap)
{
	const char *percent = ft_strchr_or_eol(*format, '%');
	t_ft_printf_format	f_descr;

	f_descr.flags = 0;
	f_descr.length_modifier = FT_L_NULL;
	// the moment we see incorrect format, set the flag to true and left format pointing at incorrect sym.
	f_descr.format_incorrect = 0;
	if (percent > *format)
		accumulate_size(write(fd, *format, percent - *format));
	*format = percent;
	if (**format == '\0')
		return ;
	*format += 1;
	parse_flags(format, &f_descr);
	parse_min_width(format, &f_descr, ap);
	parse_precision(format, &f_descr, ap);
	parse_lenghth_modifier(format, &f_descr);
	parse_format_and_write(fd, format, &f_descr, ap);
	// if incorrect, write the format line before incorrect symb.
	// incorrect symb will be produced on the next call of write_next
	if (f_descr.format_incorrect)
		accumulate_size(write(fd, percent, *format - percent));
}

// va_list != '...'
// va_start must be called outside of a function with va_list-type param
int ft_vprintf_fd(int fd, const char *format, va_list ap)
{
	while (*format)
		write_next(fd, &format, ap);
	return (accumulate_size(FT_PRINTF_AS_GET_SIZE_AND_RESET));
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int ret;
	va_list	ap;

	va_start(ap, format);
	ret = ft_vprintf_fd(fd, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int ret;
	va_list	ap;

	va_start(ap, format);
	ret = ft_vprintf_fd(1, format, ap);
	va_end(ap);
	return (ret);
}
