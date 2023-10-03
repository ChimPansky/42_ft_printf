#include "ft_printf_p.h"

// minwidth and precision only, the rest is ignored, precision determine maxlen
void write_string(int fd, t_ft_printf_format *f_descr, char *str)
{
	size_t precision;
	size_t len;
	if (!str && !(f_descr->flags & FT_F_PRESISION))
		str = "(null)";
	else if (!str && (f_descr->flags & FT_F_PRESISION))
		str = "";
	if (!(f_descr->flags & FT_F_PRESISION))
		f_descr->precision = INT_MAX;
	else
		precision = f_descr->precision;
	len = ft_strlen_max(str, precision);
	if ((f_descr->flags & FT_F_MIN_WIDTH) && f_descr->min_width > len)
	{
		if (f_descr->flags & FT_F_MINUS)
		{
			accumulate_size(write(fd, str, len));
			write_padding(fd, f_descr->min_width - len, ' ');
		}
		else
		{
			write_padding(fd, f_descr->min_width - len, ' ');
			accumulate_size(write(fd, str, len));
		}
	}
	else
		accumulate_size(write(fd, str, len));
}

// minwidth only, the rest is ignored
void write_char(int fd, t_ft_printf_format *f_descr, char c)
{
	f_descr->flags |= FT_F_PRESISION;
	f_descr->precision = 1;
	write_string(fd, f_descr, &c);
}
