#include "libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <stdint.h>

int accumulate_size(ssize_t bytes_written)
{
	static ssize_t sz = 0;
	const ssize_t ret = sz;

	if (bytes_written == WRITE_ERROR)
		sz = WRITE_ERROR;
	else if (bytes_written == GET_SIZE_AND_RESET)
	{
		sz = 0;
		return (ret);
	}
	else if (bytes_written == GET_SIZE)
		return (ret);
	else if (sz >= 0)
		sz += bytes_written;
	return sz;
}

void	parse_min_width(const char **format, t_format *f_descr, va_list ap)
{
	int variadic_min_width;

	f_descr->min_width = ft_atoi_shift(format);
	if (!f_descr->min_width && **format == '*')
	{
		variadic_min_width = va_arg(ap, int);
		if (f_descr->min_width < 0)
		{
			f_descr->flags |= F_MINUS;
			if (variadic_min_width == INT_MIN)
				f_descr->min_width = (unsigned)INT_MAX + 1;
			else
				f_descr->min_width = -variadic_min_width;
		}
		else
			f_descr->min_width = variadic_min_width;
		*format += 1;
	}
	if (f_descr->min_width)
		f_descr->flags |= F_MIN_WIDTH;
}

void	parse_flags(const char **format, t_format *f_descr)
{
	const char* flags_string = FLAGS_STRING;
	const char* next = ft_strchr_no_eol(flags_string, **format);

	while (next)
	{
		f_descr->flags |= (1 >> (next - flags_string));
		*format += 1;
		next = ft_strchr_no_eol(flags_string, **format);
	}
	if ((f_descr->flags & F_ZERO) && (f_descr->flags & F_MINUS))
		f_descr->flags &= ~F_ZERO;
	if ((f_descr->flags & F_SPACE) && (f_descr->flags & F_PLUS))
		f_descr->flags &= ~F_SPACE;
}

void	parse_precision(const char **format, t_format *f_descr, va_list ap)
{
	if (**format != '.')
		return ;
	*format += 1;
	f_descr->flags |= F_PRESISION;
	// minus not allowed even for floating point
	if (!ft_strchr_no_eol("0123456789*", **format))
		f_descr->precision = 0;
	else if (**format == '*')
	{
		f_descr->precision = va_arg(ap, int);
		if (f_descr->precision < 0)
			f_descr->flags &= ~F_PRESISION;
		*format += 1;
	}
	else
		f_descr->precision = ft_atoi_shift(format);
}

void	parse_lenghth_modifier(const char **format, t_format *f_descr)
{
	if (ft_strncmp(*format, "hh", 2) == 0)
		f_descr->length_modifier = L_hh;
	else if (ft_strncmp(*format, "ll", 2) == 0)
		f_descr->length_modifier = L_ll;
	else if (ft_strncmp(*format, "h", 1) == 0)
		f_descr->length_modifier = L_h;
	else if (ft_strncmp(*format, "l", 1) == 0)
		f_descr->length_modifier = L_l;
	else if (ft_strncmp(*format, "z", 1) == 0)
		f_descr->length_modifier = L_z;
	else if (ft_strncmp(*format, "j", 1) == 0)
		f_descr->length_modifier = L_j;
	else if (ft_strncmp(*format, "t", 1) == 0)
		f_descr->length_modifier = L_t;
	else if (ft_strncmp(*format, "L", 1) == 0)
		f_descr->length_modifier = L_L;
	if (ft_strncmp(*format, "hh", 2) == 0 || ft_strncmp(*format, "ll", 2) == 0)
		*format += 2;
	if (ft_strchr_no_eol("hlzjtL", **format))
		*format += 1;
}

void write_padding(int fd, int sz, char c)
{
	char buf[BUFFER_SIZE];

	ft_memset(buf, c, BUFFER_SIZE);
	while (sz >= BUFFER_SIZE)
	{
		accumulate_size(write(fd, buf, BUFFER_SIZE));
		sz -= BUFFER_SIZE;
	}
	if (sz)
		accumulate_size(write(fd, buf, sz));
}

intmax_t get_signed(enum e_length_modifier len, va_list ap)
{
	if (len == L_h)
		return (short)va_arg(ap, int);
	if (len == L_hh)
		return (char)va_arg(ap, int);
	if (len == L_l)
		return va_arg(ap, long);
	if (len == L_ll)
		return va_arg(ap, long long);
	if (len == L_z)
		return va_arg(ap, size_t);
	if (len == L_j)
		return va_arg(ap, intmax_t);
	if (len == L_t)
		return va_arg(ap, ptrdiff_t);
	// if (len == L_NULL)
	return va_arg(ap, int);
}

uintmax_t get_unsigned(enum e_length_modifier len, va_list ap)
{
	if (len == L_h)
		return (unsigned short)va_arg(ap, unsigned int);
	if (len == L_hh)
		return (unsigned char)va_arg(ap, unsigned int);
	if (len == L_l)
		return (unsigned long)va_arg(ap, unsigned long);
	if (len == L_ll)
		return (unsigned long long)va_arg(ap, unsigned long long);
	if (len == L_z)
		return (size_t)va_arg(ap, size_t);
	if (len == L_j)
		return va_arg(ap, uintmax_t);
	if (len == L_t)
		return va_arg(ap, ptrdiff_t);
	// if (len == L_NULL)
	return (unsigned)va_arg(ap, unsigned);
}

// integers: precision determines minimum num of caracters, ignores F_ZERO, override minwidth if greater, no output for zero if prec = 0
int	count_unb_len(uintmax_t nb, int base_len)
{
	int len = 0;

	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= base_len;
		len++;
	}
	return len;
}

void write_signed(int fd, t_format *f_descr, intmax_t nb)
{
	const int base_len = 10;
	int nb_len;
	uintmax_t unb;

	if (INTMAX_MIN == nb)
		unb = (uintmax_t)INTMAX_MAX + 1;
	else
		unb = -1 * nb;
	nb_len = count_unb_len(unb, base_len);
	if ((f_descr->flags & F_PRESISION) && (f_descr->precision > nb_len))
		nb_len = f_descr->precision;
	if ((f_descr->flags & (F_PLUS | F_SPACE)) || nb < 0)
		nb_len += 1;
	if ((f_descr->flags & F_PRESISION) && f_descr->min_width > nb_len)
	{

	}
	// flags, adjust len
	// padding + put_signed_fd(fd, nb, base)
	accumulate_size(ft_putnbr_fd((int)nb, fd));
}

	// F_SPACE, F_PLUS are ignored
	// o	unsigned int in octal. F_HASH prepends "0" string to a nonzero result (reduce padding by one)
	// u	Print decimal unsigned int.
	// x, X	unsigned int as a hexadecimal number. x uses lower-case letters and X uses upper-case.
	// F_HASH For x and X conversions, a nonzero result has the string "0x" (or "0X" for X conversions) prepended to it (reduce padding by two)
	// p	pointer. same as %#zx
void write_unsigned(int fd, t_format *f_descr, uintmax_t nb, char f)
{
	const char *base;
	if (f == 'o')
		base = "01234567";
	else if (f == 'x' || f == 'p')
		base = "0123456789abcdef";
	else if (f == 'X')
		base = "0123456789abcdef";
	count_unb_len(nb, ft_strlen(base));
	// flags, adjust len
	// padding + put_unsigned_fd(fd, nb, base)
	accumulate_size(ft_putnbr_fd((int)nb, fd));
}

// minwidth and precision only, the rest is ignored, precision determine maxlen
void write_string(int fd, t_format *f_descr, char *str)
{
	size_t precision;
	size_t len;

	if (!(f_descr->flags & F_PRESISION))
		f_descr->precision = SIZE_MAX;
	else
		precision = f_descr->precision;
	len = ft_strlen_max(str, precision);
	if ((f_descr->flags & F_MIN_WIDTH) && f_descr->min_width > len)
	{
		if (f_descr->flags & F_MINUS)
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
void write_char(int fd, t_format *f_descr, char c)
{
	f_descr->precision = 1;
	f_descr->flags |= F_PRESISION;
	write_string(fd, f_descr, &c);
}

void	parse_format_and_write(int fd, const char **format, t_format *f_descr, va_list ap)
{
    //    F_ZERO      The value should be zero padded.  For d, i, o, u, x, X the converted value is padded on the  left  with zeros rather than blanks.
	// If the 0 and - flags both appear, the 0 flag is ignored.  If a precision is given with a numeric conversion (d, i, o, u, x, and X), the 0 flag is ignored.
    //    F_MINUS      The converted value is to be left adjusted on the field boundary.  (The default is right justification.)  The converted value is padded  on  the
    //           right with blanks, rather than on the left with blanks or zeros.  A - overrides a 0 if both are given.
    //    F_SPACE    (a space) A blank should be left before a positive number (or empty string) produced by a signed conversion.
    //    F_PLUS      A  sign (+ or -) should always be placed before a number produced by a signed conversion.  By default, a sign is used only for negative numbers.
    //           A + overrides a space if both are used.

	// %	Prints a literal % character (this type doesn't accept any flags, width, precision, length fields).
	// all flags and length modifiers are ignored, no error
	if (**format == '%')
		accumulate_size(write(fd, *format, 1));
	// c	char (character)
	else if (**format == 'c')
		write_char(fd, f_descr, (unsigned char)va_arg(ap, int));
	// s	null-terminated string (or precision-length string if prec is determined)
	else if (**format == 's'){
		char* a = va_arg(ap, char *);
		write_string(fd, f_descr, a);
	}
	// d, i	int as a signed integer. %d and %i are synonymous for output
	else if (ft_strchr_no_eol("di", **format))
		write_signed(fd, f_descr, get_signed(f_descr->length_modifier, ap));
	// unsigned
	else if (ft_strchr_no_eol("oxXup", **format))
	{
		f_descr->flags &= ~(F_SPACE | F_PLUS);
		if (**format == 'p')
		{
			f_descr->flags |= F_HASH;
			f_descr->length_modifier = L_z;
		}
		write_unsigned(fd, f_descr,
		get_unsigned(f_descr->length_modifier, ap), **format);
	}
	// add unimplemented for unsupported flags?
	// eE fF gG n aA m
	if (ft_strchr_no_eol("%scdioxXup", **format))
		*format += 1;
	else
		f_descr->format_incorrect = 1;
}

void	write_next(int fd, const char **format, va_list ap)
{
	const char *percent = ft_strchr_or_eol(*format, '%');
	t_format	f_descr;

	f_descr.flags = 0;
	f_descr.length_modifier = L_NULL;
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

// va_list != ... va_start must be called outside of a function with va_list-type param
int ft_vprintf_fd(int fd, const char *format, va_list ap)
{
	while (*format)
		write_next(1, &format, ap);
	return (accumulate_size(GET_SIZE_AND_RESET));
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
