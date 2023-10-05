/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:09:22 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/05 23:02:48 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	chose_output(int fd, int *prted, const char **fmt, va_list args);

int	ft_printf(const char *format, ...)
{
	int		printed;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	printed = ft_printf_fd(1, format, args);
	va_end(args);
	return (printed);
}

int	ft_printf_fd(int fd, const char *format, va_list args)
{
	int	printed;

	printed = 0;
	while (*format)
		chose_output(fd, &printed, &format, args);
	return (printed);
}

static void	chose_output(int fd, int *prted, const char **fmt,	va_list args)
{
	t_format	conf;

	if (**fmt == '%')
	{
		(*fmt)++;
		if (!(**fmt))
		{
			*prted = -1;
			return ;
		}
		if (**fmt == '%')
			*prted += output_percent(fd, fmt);
		else
		{
			if (set_config(fmt, &conf))
				*prted += output_conversion(fd, conf, args);
			else
				*prted += output_percent(fd, fmt);
		}
	}
	else
		*prted += output_regular(fd, fmt);
}

/*
#include <stdio.h>
#include <limits.h>
int	main()
{
	int ret;
	char *format;


	format = "%c %c %c";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, '0', 0, '0');
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, '0', 0, '0');
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = "%c";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, '0' - 256);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, '0' - 256);
	printf("\nExpected Return Val: %d\n\n\n", ret);


	format = " %p %p ";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, LONG_MIN, LONG_MAX);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, LONG_MIN, LONG_MAX);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = " %p %p ";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, INT_MIN, INT_MAX);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, INT_MIN, INT_MAX);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = " %p %p ";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, ULONG_MAX, -ULONG_MAX);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, ULONG_MAX, -ULONG_MAX);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = " %p %p ";

	ft_putendl_fd(format, 1);
	ret = ft_printf(format, 1, 0);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, 1, 0);
	printf("\nExpected Return Val: %d\n\n\n", ret);

/*
	format = "%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%";

	ft_putendl_fd(format, 1);
	//ret = ft_printf(format, 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	//printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	printf("\nExpected Return Val: %d\n\n\n", ret);




	ret = ft_printf("%c", 0);
	printf("%d\n\n\n\n", ret);

	ret = ft_printf("%10c|\n");
	ret = ft_printf("%-10c|\n", 'A');

	ret = printf("%10c|\n", 'A');
	ret = printf("%-10c|\n", 'A');

	ret = printf("%s|\n", "abc");
	ret = ft_printf("%s|\n", "abc");



	ret = printf("%+d|\n", 1);
	ret = ft_printf("%+d|\n", 1);

	char *input = "nadslfn";

	//ret = printf(input);
	//printf("\nxp_ret: %d\n", ret);
	ret = ft_printf(input);
	printf("\nft_ret: %d\n", ret);


    return 0;
}
*/
