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

void	write_next(int fd, t_buffer *buf, const char **format, va_list arguments)
{
	const char* next = ft_strchr_or_eol(*format, '%');
	const char* flags_string = FLAGS_STRING;
	int flags = 0;
	int width;
	int presision;

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
		flags |= (1 >> (next - flags_string));
		*format += 1;
		next = ft_strchr(flags_string, **format);
	}
	// width
	width = ft_atoi_shift(format);
	if (!width && **format == '*')
	{
		width = va_arg(arguments, int);
		*format += 1;
	}
	if (**format == '.')
	{
		*format += 1;
		presision = ft_atoi_shift(format);
		if (!presision && **format == '*')
		{
			presision = va_arg(arguments, int);
			*format += 1;
		}
	}
// 	hh	For integer types, causes printf to expect an int-sized integer argument which was promoted from a char.
// h	For integer types, causes printf to expect an int-sized integer argument which was promoted from a short.
// l	For integer types, causes printf to expect a long-sized integer argument.
// For floating-point types, this is ignored. float arguments are always promoted to double when used in a varargs call.[4]

// ll	For integer types, causes printf to expect a long long-sized integer argument.
// L	For floating-point types, causes printf to expect a long double argument.
// z	For integer types, causes printf to expect a size_t-sized integer argument.
// j	For integer types, causes printf to expect a intmax_t-sized integer argument.
// t	For integer types, causes printf to expect a ptrdiff_t-sized integer argument.


// %	Prints a literal % character (this type doesn't accept any flags, width, precision, length fields).
// d, i	int as a signed integer. %d and %i are synonymous for output, but are different when used with scanf for input (where using %i will interpret a number as hexadecimal if it's preceded by 0x, and octal if it's preceded by 0.)
// u	Print decimal unsigned int.
// f, F	double in normal (fixed-point) notation. f and F only differs in how the strings for an infinite number or NaN are printed (inf, infinity and nan for f; INF, INFINITY and NAN for F).
// e, E	double value in standard form (d.ddde±dd). An E conversion uses the letter E (rather than e) to introduce the exponent. The exponent always contains at least two digits; if the value is zero, the exponent is 00. In Windows, the exponent contains three digits by default, e.g. 1.5e002, but this can be altered by Microsoft-specific _set_output_format function.
// g, G	double in either normal or exponential notation, whichever is more appropriate for its magnitude. g uses lower-case letters, G uses upper-case letters. This type differs slightly from fixed-point notation in that insignificant zeroes to the right of the decimal point are not included. Also, the decimal point is not included on whole numbers.
// x, X	unsigned int as a hexadecimal number. x uses lower-case letters and X uses upper-case.
// o	unsigned int in octal.
// s	null-terminated string.
// c	char (character).
// p	void* (pointer to void) in an implementation-defined format.
// a, A	double in hexadecimal notation, starting with 0x or 0X. a uses lower-case letters, A uses upper-case letters.[5][6] (C++11 iostreams have a hexfloat that works the same).
// n	Print nothing, but writes the number of characters written so far into an integer pointer parameter.
// In Java this prints a newline.[7]

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
