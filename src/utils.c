/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:37 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/03 23:24:04 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

int	accumulate_size(ssize_t bytes_written)
{
	static ssize_t	sz = 0;
	const ssize_t	ret = sz;

	if (bytes_written == FT_PRINTF_WRITE_ERROR)
		sz = FT_PRINTF_WRITE_ERROR;
	else if (bytes_written == FT_PRINTF_AS_GET_SIZE_AND_RESET)
	{
		sz = 0;
		return (ret);
	}
	else if (bytes_written == FT_PRINTF_AS_GET_SIZE)
		return (ret);
	else if (sz >= 0)
		sz += bytes_written;
	return (sz);
}

void	write_padding(int fd, int sz, char c)
{
	char	buf[BUFFER_SIZE];

	ft_memset(buf, c, BUFFER_SIZE);
	while (sz >= BUFFER_SIZE)
	{
		accumulate_size(write(fd, buf, BUFFER_SIZE));
		sz -= BUFFER_SIZE;
	}
	if (sz)
		accumulate_size(write(fd, buf, sz));
}

intmax_t	get_signed(enum e_ft_printf_length_modifier len, va_list ap)
{
	if (len == FT_L_h)
		return ((short)va_arg(ap, int));
	if (len == FT_L_hh)
		return ((char)va_arg(ap, int));
	if (len == FT_L_l)
		return (va_arg(ap, long));
	if (len == FT_L_ll)
		return (va_arg(ap, long long));
	if (len == FT_L_z)
		return (va_arg(ap, size_t));
	if (len == FT_L_j)
		return (va_arg(ap, intmax_t));
	if (len == FT_L_t)
		return (va_arg(ap, ptrdiff_t));
	return (va_arg(ap, int));
}

// if (len == FT_L_NULL)
uintmax_t	get_unsigned(enum e_ft_printf_length_modifier len, va_list ap)
{
	if (len == FT_L_h)
		return ((unsigned short)va_arg(ap, unsigned int));
	if (len == FT_L_hh)
		return ((unsigned char)va_arg(ap, unsigned int));
	if (len == FT_L_l)
		return ((unsigned long)va_arg(ap, unsigned long));
	if (len == FT_L_ll)
		return ((unsigned long long)va_arg(ap, unsigned long long));
	if (len == FT_L_z)
		return ((size_t)va_arg(ap, size_t));
	if (len == FT_L_j)
		return (va_arg(ap, uintmax_t));
	if (len == FT_L_t)
		return (va_arg(ap, ptrdiff_t));
	return ((unsigned)va_arg(ap, unsigned));
}

int	count_unb_len(uintmax_t nb, int base_len, int precision)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (precision != 0);
	while (nb)
	{
		nb /= base_len;
		len++;
	}
	return (len);
}
