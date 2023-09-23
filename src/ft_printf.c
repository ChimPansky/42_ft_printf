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

	while (next)
	{
		flags |= (1 >> (next - flags_string));
		*format += 1;
		next = ft_strchr(flags_string, **format);
	}

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
