#include "../include/ft_printf.h"

int check_buf()

static int	get_conversion(char c, va_list arguments)
{
	if (c == 'c')
		return (ft_putchar_fd(c, 1));
	if (c == 's')
		return (convert_s(va_arg(arguments, char *)));
	if (c == 'i' || c == 'd')
		return (ft_putnbr_base_fd(1, va_arg(arguments, int), "0123456789"));
	if (c == 'X')
		return (ft_putnbr_base_fd(1, va_arg(arguments, unsigned), "0123456789ABCDEF"));
	if (c == 'x')
		return (ft_putnbr_base_fd(1, va_arg(arguments, unsigned), "0123456789abcdef"));
	if (c == 'b')
		return (ft_putnbr_base_fd(1, va_arg(arguments, unsigned), "01"));
	if (c == 'o')
		return (ft_putnbr_base_fd(1, va_arg(arguments, unsigned), "01234567"));
	if (c == 'u')
		return (ft_putunsigned_base_fd(1, va_arg(arguments, unsigned), "0123456789"));
	if (c == 'p')
		return (convert_p(va_arg(arguments, void *)));
	return (0);
}

int accumulate_size(ssize_t bytes_written)
{
	static int sz = 0;

	if (bytes_written < 0)
		sz = -1;
	if (sz >= 0)
		sz += bytes_written;
	return sz;
}

void	parse_lenghth_modifier(const char **format, t_format *format_description)
{
	// For floating-point types, this is ignored. float arguments are always promoted to double when used in a varargs call.[4]
	// 	hh	For integer types, causes printf to expect an int-sized integer argument which was promoted from a char.
	if (ft_strncmp(*format, "hh", 2) == 0)
	{
		*format += 2;
		format_description->length_modifier = L_hh;
	}
	// h	For integer types, causes printf to expect an int-sized integer argument which was promoted from a short.
	else if (ft_strncmp(*format, "h", 1) == 0)
	{
		*format += 1;
		format_description->length_modifier = L_h;
	}
	// ll	For integer types, causes printf to expect a long long-sized integer argument.
	else if (ft_strncmp(*format, "ll", 2) == 0)
	{
		*format += 2;
		format_description->length_modifier = L_ll;
	}
	// l	For integer types, causes printf to expect a long-sized integer argument.
	else if (ft_strncmp(*format, "l", 1) == 0)
	{
		*format += 1;
		format_description->length_modifier = L_l;
	}
	// z	For integer types, causes printf to expect a size_t-sized integer argument.
	else if (ft_strncmp(*format, "z", 1) == 0)
	{
		*format += 1;
		format_description->length_modifier = L_z;
	}
	// j	For integer types, causes printf to expect a intmax_t-sized integer argument.
	else if (ft_strncmp(*format, "j", 1) == 0)
	{
		*format += 1;
		format_description->length_modifier = L_j;
	}
	// t	For integer types, causes printf to expect a ptrdiff_t-sized integer argument.
	else if (ft_strncmp(*format, "t", 1) == 0)
	{
		*format += 1;
		format_description->length_modifier = L_t;
	}
	// L	For floating-point types, causes printf to expect a long double argument.
}

void	parse_format(const char **format, t_format *format_description)
{


    //    F_ZERO      The value should be zero padded.  For d, i, o, u, x, X the converted value is padded on the  left  with zeros rather than blanks.
	// If the 0 and - flags both appear, the 0 flag is ignored.  If a precision is given with a numeric conversion (d, i, o,
    //           u, x, and X), the 0 flag is ignored.
    //    F_MINUS      The converted value is to be left adjusted on the field boundary.  (The default is right justification.)  The converted value is padded  on  the
    //           right with blanks, rather than on the left with blanks or zeros.  A - overrides a 0 if both are given.
    //    F_SPACE    (a space) A blank should be left before a positive number (or empty string) produced by a signed conversion.
    //    F_PLUS      A  sign (+ or -) should always be placed before a number produced by a signed conversion.  By default, a sign is used only for negative numbers.
    //           A + overrides a space if both are used.

	// %	Prints a literal % character (this type doesn't accept any flags, width, precision, length fields).
	if (**format == '%')
	{
		// all flags and length modifiers are ignored, no error
	}
	// d, i	int as a signed integer. %d and %i are synonymous for output
	else if (**format == 'd' || **format == 'i')
	{
		// F_HASH For o conversions, the first character of the output string is made zero (by prefixing  a 0  if it was not zero already).
	}
	// o	unsigned int in octal.
	else if (**format == 'o')
	{

	}
	// x, X	unsigned int as a hexadecimal number. x uses lower-case letters and X uses upper-case.
	else if (**format == 'x' || **format == 'X')
	{
		// F_HASH For x and X conversions, a nonzero result has the string "0x" (or "0X" for X conversions) prepended to it

	}
	// u	Print decimal unsigned int.
	else if (**format == 'u')
	{

	}
	// c	char (character).
	else if (**format == 'c')
	{
		// minwidth only, the rest is ignored
	}
	// s	null-terminated string.
	else if (**format == 's')
	{
		// minwidth only, the rest is ignored
	}
	// p	void* (pointer to void) in an implementation-defined format.
	else if (**format == 'p')
	{
		// like hex + hash
	}
}

void	write_next(int fd, t_buffer *buf, const char **format, va_list arguments)
{
	const char* next = ft_strchr_or_eol(*format, '%');
	const char* flags_string = FLAGS_STRING;
	t_format	format_description;

	format_description.flags = 0;
	format_description.length_modifier = L_NULL;

	if (next - 1 > *format)
		accumulate_size(write(fd, *format, next - 1 - *format));
	*format = next;
	if (**format == '\0')
		return ;
	*format += 1;
	// flags
	next = ft_strchr(flags_string, **format);
	while (next)
	{
		format_description.flags |= (1 >> (next - flags_string));
		*format += 1;
		next = ft_strchr(flags_string, **format);
	}
	// width
	format_description.min_width = ft_atoi_shift(format);
	if (!format_description.min_width && **format == '*')
	{
		format_description.min_width = va_arg(arguments, int);
		*format += 1;
	}
	if (format_description.min_width)
		format_description.flags |= F_MIN_WIDTH;
	if (**format == '.')
	{
		*format += 1;
		// TODO +- not allowed here
		format_description.precision = ft_atoi_shift(format);
		if (!format_description.precision && **format == '*')
		{
			format_description.precision = va_arg(arguments, int);
			*format += 1;
		}
		format_description.flags |= F_PRESISION;
	}
	parse_lenghth_modifier(format, &format_description);
	parse_format(format, &format_description);

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
