/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:40 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/04 01:03:35 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

// minwidth and precision only, the rest is ignored, precision determine maxlen
// conversion check to output '\0'
void	write_string(int fd, t_ft_printf_format *f_descr, const char *str)
{
	size_t	len;

	if (!str && !(f_descr->flags & FT_F_PRESISION))
		str = "(null)";
	else if (!str && (f_descr->flags & FT_F_PRESISION))
		str = "";
	if (!(f_descr->flags & FT_F_PRESISION))
		f_descr->precision = INT_MAX;
	len = ft_strlen_max(str, f_descr->precision);
	if (f_descr->conversion == 'c')
		len = 1;
	if ((f_descr->flags & FT_F_MIN_WIDTH) && f_descr->min_width > len)
	{
		if (f_descr->flags & FT_F_MINUS)
			accumulate_size(write(fd, str, len));
		write_padding(fd, f_descr->min_width - len, ' ');
		if (!(f_descr->flags & FT_F_MINUS))
			accumulate_size(write(fd, str, len));
	}
	else
		accumulate_size(write(fd, str, len));
}

// minwidth only, the rest is ignored
void	write_char(int fd, t_ft_printf_format *f_descr, char c)
{
	f_descr->flags |= FT_F_PRESISION;
	f_descr->precision = 1;
	write_string(fd, f_descr, &c);
}
