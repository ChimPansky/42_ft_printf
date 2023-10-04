/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ints_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:09:17 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/04 12:33:38 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

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

// sizeof(uintmax_t) * CHAR_BIT is a max size of a num-string (for base 2)
void	ft_write_unsigned_base_fd(
			int fd,
			const t_ft_printf_nb_description *nb_descr)
{
	char		buf[sizeof(uintmax_t) * CHAR_BIT];
	size_t		ord;
	size_t		idx;

	idx = 0;
	ord = 1;
	while (nb_descr->nb / nb_descr->base_len >= ord)
		ord *= nb_descr->base_len;
	while (ord)
	{
		buf[idx++] = nb_descr->base[nb_descr->nb / ord % nb_descr->base_len];
		ord /= nb_descr->base_len;
	}
	accumulate_size(write(fd, buf, nb_descr->nb_len));
}
