#include "../include/ft_printf.h"

int accumulate_size(ssize_t bytes_written)
{
	static int sz = 0;

	if (bytes_written == ERROR_ACCUMULATED_SIZE)
		sz = -1;
	else if (bytes_written == RESET_ACCUMULATED_SIZE)
		sz = 0;
	else if (bytes_written == GET_ACCUMULATED_SIZE)
		return (sz);
	else if (sz >= 0)
		sz += bytes_written;
	return sz;
}

void	parse_flags(const char **format, t_format *format_description, va_list arguments)
{
	const char* flags_string = FLAGS_STRING;
	const char* next = ft_strchr(flags_string, **format);

	while (next)
	{
		format_description->flags |= (1 >> (next - flags_string));
		*format += 1;
		next = ft_strchr(flags_string, **format);
	}
	if ((format_description->flags & F_ZERO) && (format_description->flags & F_MINUS))
		format_description->flags &= ~F_ZERO;
	if ((format_description->flags & F_SPACE) && (format_description->flags & F_PLUS))
		format_description->flags &= ~F_SPACE;
	format_description->min_width = ft_atoi_shift(format);
	if (!format_description->min_width && **format == '*')
	{
		format_description->min_width = va_arg(arguments, int);
		*format += 1;
	}
	if (format_description->min_width)
		format_description->flags |= F_MIN_WIDTH;
}

void	parse_precision(const char **format, t_format *format_description, va_list arguments)
{
	if (**format != '.')
		return ;
	*format += 1;
	// behaviour for "%.d" ?
	if (!ft_strchr("0123456789*", **format))
		return ;
	if (**format == '*')
	{
		format_description->precision = va_arg(arguments, int);
		*format += 1;
	}
	else
		format_description->precision = ft_atoi_shift(format);
	format_description->flags |= F_PRESISION;
}


void	parse_lenghth_modifier(const char **format, t_format *format_description)
{
	if (ft_strncmp(*format, "hh", 2) == 0)
		format_description->length_modifier = L_hh;
	else if (ft_strncmp(*format, "ll", 2) == 0)
		format_description->length_modifier = L_ll;
	else if (ft_strncmp(*format, "h", 1) == 0)
		format_description->length_modifier = L_h;
	else if (ft_strncmp(*format, "l", 1) == 0)
		format_description->length_modifier = L_l;
	else if (ft_strncmp(*format, "z", 1) == 0)
		format_description->length_modifier = L_z;
	else if (ft_strncmp(*format, "j", 1) == 0)
		format_description->length_modifier = L_j;
	else if (ft_strncmp(*format, "t", 1) == 0)
		format_description->length_modifier = L_t;
	if (ft_strncmp(*format, "hh", 2) == 0 || ft_strncmp(*format, "ll", 2) == 0)
		*format += 2;
	if (ft_strchr("hlzjt", **format))
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

intmax_t get_signed(enum e_length_modifier len, va_list arguments)
{
	if (len == L_NULL)
		return va_arg(arguments, int);
	if (len == L_h)
		return (short)va_arg(arguments, int);
	if (len == L_hh)
		return (char)va_arg(arguments, int);
	if (len == L_l)
		return va_arg(arguments, long);
	if (len == L_ll)
		return va_arg(arguments, long long);
	if (len == L_z)
		return va_arg(arguments, size_t);
	if (len == L_j)
		return va_arg(arguments, intmax_t);
	if (len == L_t)
		return va_arg(arguments, ptrdiff_t);
}

uintmax_t get_unsigned(enum e_length_modifier len, va_list arguments)
{
	if (len == L_NULL)
		return (unsigned)va_arg(arguments, unsigned);
	if (len == L_h)
		return (unsigned short)va_arg(arguments, unsigned int);
	if (len == L_hh)
		return (unsigned char)va_arg(arguments, unsigned int);
	if (len == L_l)
		return (unsigned long)va_arg(arguments, unsigned long);
	if (len == L_ll)
		return (unsigned long long)va_arg(arguments, unsigned long long);
	if (len == L_z)
		return (size_t)va_arg(arguments, size_t);
	if (len == L_j)
		return va_arg(arguments, uintmax_t);
	if (len == L_t)
		return va_arg(arguments, ptrdiff_t);
}

void	parse_format_and_write(int fd, const char **format, t_format *format_description, va_list arguments)
{
    //    F_ZERO      The value should be zero padded.  For d, i, o, u, x, X the converted value is padded on the  left  with zeros rather than blanks.
	// If the 0 and - flags both appear, the 0 flag is ignored.  If a precision is given with a numeric conversion (d, i, o, u, x, and X), the 0 flag is ignored.
    //    F_MINUS      The converted value is to be left adjusted on the field boundary.  (The default is right justification.)  The converted value is padded  on  the
    //           right with blanks, rather than on the left with blanks or zeros.  A - overrides a 0 if both are given.
    //    F_SPACE    (a space) A blank should be left before a positive number (or empty string) produced by a signed conversion.
    //    F_PLUS      A  sign (+ or -) should always be placed before a number produced by a signed conversion.  By default, a sign is used only for negative numbers.
    //           A + overrides a space if both are used.

	// %	Prints a literal % character (this type doesn't accept any flags, width, precision, length fields).
	if (**format == '%')
	{
		// all flags and length modifiers are ignored, no error
		accumulate_size(write(fd, *format, 1));
	}
	// c	char (character).
	else if (**format == 'c')
	{
		// minwidth only, the rest is ignored
	}
	// s	null-terminated string (or precision-length string if prec is determined)
	else if (**format == 's')
	{
		// minwidth and precision only, the rest is ignored, precision determine maxlen
	}
	// integers: precision determines minimum num of caracters, ignores F_ZERO, override minwidth if greater, no output for zero if prec = 0
	// d, i	int as a signed integer. %d and %i are synonymous for output
	else if (ft_strchr("di", **format))
	{
		intmax_t a = get_signed(format_description->length_modifier, arguments);
		t_sized_string *str = lltoa_base(a, "0123456789");
		write_withflags(fd, format_description, str);
		free(str);
	}
	// unsigned
	// F_SPACE, F_PLUS are ignored
	// o	unsigned int in octal. F_HASH prepends "0" string to a nonzero result (reduce padding by one)
	// u	Print decimal unsigned int.
	// x, X	unsigned int as a hexadecimal number. x uses lower-case letters and X uses upper-case.
	// F_HASH For x and X conversions, a nonzero result has the string "0x" (or "0X" for X conversions) prepended to it (reduce padding by two)
	// p	pointer. same as %#zx
	else if (ft_strchr("oxXup", **format))
	{
		format_description->flags &= ~(F_SPACE | F_PLUS);
		if (**format == 'p')
		{
			format_description->flags |= F_HASH;
			format_description->length_modifier = L_z;
		}
		const char *base;
		if (**format == 'o')
			base = "01234567";
		else if (**format == 'x' || **format == 'p')
			base = "0123456789abcdef";
		else if (**format == 'X')
			base = "0123456789abcdef";
		uintmax_t b = get_unsigned(format_description->length_modifier, arguments);
		t_sized_string *str = ulltoa_base(b, base);
		write_withflags(fd, format_description, str);
		free(str);
	}
	if (ft_strchr("%pouxXsc", **format))
		*format += 1;
}

void	write_next(int fd, t_buffer *buf, const char **format, va_list arguments)
{
	const char* next = ft_strchr_or_eol(*format, '%');
	t_format	format_description;

	format_description.flags = 0;
	format_description.length_modifier = L_NULL;

	if (next - 1 > *format)
		accumulate_size(write(fd, *format, next - 1 - *format));
	*format = next;
	if (**format == '\0')
		return ;
	*format += 1;
	parse_flags(format, &format_description, arguments);
	parse_precision(format, &format_description, arguments);
	parse_lenghth_modifier(format, &format_description);
	parse_format_and_write(fd, format, &format_description, arguments);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	arguments;
	t_buffer buf;

	buf.str = malloc(BUFFER_SIZE * sizeof(char));
	if (!buf.str)
		return (-1);
	buf.capacity = BUFFER_SIZE;
	buf.sz = 0;
	va_start(arguments, format);
	while (*format)
		write_next(fd, &buf, &format, arguments);
	va_end(arguments);
	return (accumulate_size(0));
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;

	return ft_printf_fd(1, format, arguments);
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
