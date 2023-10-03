#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "include/ft_printf.h"
#include "libft/libft.h"

void test(const char *format, ...)
{
	va_list ap;
	va_list ap_copy;
	va_start(ap, format);
	va_copy(ap_copy, ap);
	ft_putstr_fd(format, 1);
	write(1, "\nft:\n", 5);
	int a = ft_vprintf_fd(1, format, ap);
	write(1, "\nst:\n", 5);
	int b = vprintf(format, ap_copy);
	printf("\nft: %d, st: %d\n\n", a, b);
	va_end(ap);
}

int	main(void)
{
	// test("abc%%");
	// test("%s", "asd");
	// test("%s", NULL);
	// test("%c", 'N');
	// test("%c", '\0');
	// test("%p", "asd");
	// test("%p", NULL);

	// test("abc%d", 123);
	// test("abc%u", 123u);
	// test("abc%x", 1024);
	// test("abc%X", 1024);
	// test("abc%o", 1024);

	// test("%.10x", 1024);  // printf and vprintf behave differently on this one
	// test("%#.10x", 1024);  // printf and vprintf behave differently on this one
	test("%#20.10x", 1024);  // printf and vprintf behave differently on this one

	// defined UB
	test("abc%");  // printf and vprintf behave differently on this one
	// %p apparently works with '+' and ' ' flags, but not with '#', probably impl-defined


	return (0);
}
