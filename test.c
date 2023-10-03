/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:09:57 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/04 01:17:34 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static void	test(const char *format, ...)
{
	va_list	ap;
	va_list	ap_copy;
	int		a;
	int		b;

	va_start(ap, format);
	va_copy(ap_copy, ap);
	ft_putstr_fd((char *)format, 1);
	write(1, "\nft:\n", 5);
	a = ft_vprintf_fd(1, format, ap);
	write(1, "\nst:\n", 5);
	b = vprintf(format, ap_copy);
	printf("\nft: %d, st: %d\n\n", a, b);
	va_end(ap);
}

static void	simple_tests_scp(void)
{
	test("abc%%");
	test("%s", "asd");
	test("%s", NULL);
	test("%c", 'N');
	test("%c", '\0');
	test("%p", "asd");
	test("%p", NULL);
}

static void	simple_tests_id(void)
{
	test("%d", 123);
	test("%d", -123);
	test("%d", 0);
	test("%d", INT_MAX);
	test("%d", INT_MIN);
	test("%i", 123);
	test("%i", -123);
	test("%i", 0);
	test("%i", INT_MAX);
	test("%i", INT_MIN);
}

static void	simple_tests_uxo(void)
{
	test("%u", 123);
	test("%u", -123);
	test("%u", 0);
	test("%u", INT_MAX);
	test("%u", INT_MIN);
	test("%u", UINT_MAX);

	test("%x", 123);
	test("%x", -123);
	test("%x", 0);
	test("%x", INT_MAX);
	test("%x", INT_MIN);
	test("%x", UINT_MAX);

	test("%X", 123);
	test("%X", -123);
	test("%X", 0);
	test("%X", INT_MAX);
	test("%X", INT_MIN);
	test("%X", UINT_MAX);

	test("%o", 123);
	test("%o", -123);
	test("%o", 0);
	test("%o", INT_MAX);
	test("%o", INT_MIN);
	test("%o", UINT_MAX);
}

int	main(void)
{
	simple_tests_scp();
	simple_tests_id();
	simple_tests_uxo();

	test("%.10x", 1024);  // printf and vprintf behave differently on this one
	test("%#.10x", 1024);  // printf and vprintf behave differently on this one
	test("%#20.10x", 1024);  // printf and vprintf behave differently on this one

	// defined UB
	test("abc%");  // printf and vprintf behave differently on this one
	// %p apparently works with '+' and ' ' flags, but not with '#', probably impl-defined


	return (0);
}
