#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

void test(const char *format, ...)
{
	va_list ap;
	va_list ap_copy;
	va_start(ap, format);
	va_copy(ap_copy, ap);
	write(1, "ft:\n", 4);
	int a = ft_vprintf_fd(1, format, ap);
	write(1, "\nst:\n", 5);
	int b = vprintf(format, ap_copy);
	printf("\nft: %d, st: %d\n\n", a, b);
	va_end(ap);
}

int	main(void)
{
	// no flags
	test("abc%s", "asd");
	test("abc%c", 'N');
	test("abc%d", 123);
	test("abc%%", -123);

	// defined UB
	test("abc%");  // printf and vprintf behave differently on this one
	// %p apparently works with '+' and ' ' flags, but not with '#', probably impl-defined
	test("%.20x", "asd");  // printf and vprintf behave differently on this one


	return (0);
}
