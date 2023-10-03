/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:44 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/04 01:22:48 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"
#include "libft.h"
#include <stdint.h>

// string literals are not local variables and are avaliable out of scope
// sick!
static void	fill_base(t_ft_printf_nb_description *nb_descr, char conv)
{
	if (conv == 'x')
	{
		nb_descr->base = "0123456789abcdef";
		nb_descr->hash = "0x";
	}
	else if (conv == 'X')
	{
		nb_descr->base = "0123456789ABCDEF";
		nb_descr->hash = "0X";
	}
	else if (conv == 'o')
	{
		nb_descr->base = "01234567";
		nb_descr->hash = "0";
	}
	else if (conv == 'u' || conv == 'd' || conv == 'i')
	{
		nb_descr->base = "0123456789";
		nb_descr->hash = "";
	}
	nb_descr->base_len = ft_strlen(nb_descr->base);
}

void	write_signed(int fd, t_ft_printf_format *f_descr, intmax_t nb)
{
	t_ft_printf_nb_description	nb_descr;

	if (!(f_descr->flags & FT_F_PRESISION))
		f_descr->precision = 1;
	else
		f_descr->flags &= ~FT_F_ZERO;
	nb_descr.prefix = "";
	fill_base(&nb_descr, f_descr->conversion);
	if (INTMAX_MIN == nb)
		nb_descr.nb = (uintmax_t)INTMAX_MAX + 1;
	else if (nb < 0)
		nb_descr.nb = -nb;
	else
		nb_descr.nb = nb;
	nb_descr.nb_len = count_unb_len(
			nb_descr.nb, nb_descr.base_len, f_descr->precision);
	if (nb < 0)
		nb_descr.prefix = "-";
	else if (nb && (f_descr->flags & FT_F_PLUS))
		nb_descr.prefix = "+";
	else if (nb && (f_descr->flags & FT_F_SPACE))
		nb_descr.prefix = " ";
	write_unb_in_order(fd, &nb_descr, f_descr);
}

//	F_SPACE, F_PLUS are ignored
//	o:		unsigned int in octal. F_HASH prepends "0" to a nonzero result
// 		!!!!!!!!!! check with leading zeros of prec and F_FT_ZERO !!!!!!!!!!
//	u:		Print decimal unsigned int.
//	x, X:	unsigned int in hex. X uses lower-case, X uses upper-case.
//		F_HASH prepends "0x" or "0X" to a nonzero result
void	write_unsigned(int fd, t_ft_printf_format *f_descr, uintmax_t nb)
{
	t_ft_printf_nb_description	nb_descr;

	if (!(f_descr->flags & FT_F_PRESISION))
		f_descr->precision = 1;
	else
		f_descr->flags &= ~FT_F_ZERO;
	nb_descr.prefix = "";
	fill_base(&nb_descr, f_descr->conversion);
	nb_descr.nb = nb;
	nb_descr.nb_len = count_unb_len(
			nb_descr.nb, nb_descr.base_len, f_descr->precision);
	if (nb && (f_descr->flags & FT_F_HASH))
		nb_descr.prefix = nb_descr.hash;
	write_unb_in_order(fd, &nb_descr, f_descr);
}
