/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:23:29 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/05 14:23:17 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	output_percent(int fd, const char **format)
{
	int	bytes_written;

	bytes_written = write(fd, "%", 1);
	(*format)++;
	return (bytes_written);
}

int	output_conversion(int fd, t_format conf, va_list args)
{
	int		bytes_written;
	char	*s;

	bytes_written = 0;
	s = NULL;
	if (conf.type == 'c')
		return (output_c(fd, conf, args));
	else if (conf.type == 's')
	{
		s = va_arg(args, char *);
		s = ft_iif_ptr_f(s != NULL, ft_strdup, s, "(null)");
	}
	else if (ft_strchr("diuxXp", conf.type))
		s = convert_diuxxp(conf.type, args);
	if (s)
		s = manipulate_s(s, conf);
	if (s)
	{
		bytes_written += write(fd, s, ft_strlen(s));
		free(s);
	}
	return (bytes_written);
}

int	output_c(int fd, t_format conf, va_list args)
{
	int		c;
	int		bytes_written;
	char	*spad;

	c = va_arg(args, int);
	bytes_written = 0;
	if (conf.width)
	{
		spad = ft_strreplicate(' ', conf.width - 1);
		if (!spad)
			return (0);
		if (!(conf.flags & F_MINUS))
			bytes_written += write(fd, spad, conf.width - 1);
	}
	bytes_written += write(fd, &c, 1);
	if (conf.width && (conf.flags & F_MINUS))
		bytes_written += write(fd, spad, conf.width - 1);
	if (conf.width)
		free(spad);
	return (bytes_written);
}

int	output_regular(int fd, const char **format)
{
	size_t	i;
	int		bytes_written;

	i = 0;
	while (*(*format + i) && *(*format + i) != '%')
		i++;
	if (i > 0)
	{
		bytes_written = write(fd, *format, i);
		(*format) += i;
		return (bytes_written);
	}
	(*format)++;
	return (0);
}
