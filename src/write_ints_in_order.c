/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ints_in_order.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:25:41 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/04 00:26:17 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

static void	write_left_adjusted_odred(
		int fd,
		const t_ft_printf_nb_description *nb_descr,
		const t_ft_printf_output_order_options *order_opts)
{
	if (order_opts->prefix)
		accumulate_size(write(fd, nb_descr->prefix, order_opts->prefix));
	if (order_opts->leading_zeros)
		write_padding(fd, order_opts->leading_zeros, '0');
	if (nb_descr->nb_len)
		ft_write_unsigned_base_fd(fd, nb_descr);
	if (order_opts->padding)
		write_padding(fd, order_opts->padding, ' ');
}

static void	write_right_adjusted_with_zeros(
		int fd,
		const t_ft_printf_nb_description *nb_descr,
		const t_ft_printf_output_order_options *order_opts)
{
	if (order_opts->prefix)
		accumulate_size(write(fd, nb_descr->prefix, order_opts->prefix));
	if (order_opts->padding)
		write_padding(fd, order_opts->padding, '0');
	if (order_opts->leading_zeros)
		write_padding(fd, order_opts->leading_zeros, '0');
	if (nb_descr->nb_len)
		ft_write_unsigned_base_fd(fd, nb_descr);
}

static void	write_right_adjusted_with_spaces(
		int fd,
		const t_ft_printf_nb_description *nb_descr,
		const t_ft_printf_output_order_options *order_opts)
{
	if (order_opts->padding)
		write_padding(fd, order_opts->padding, ' ');
	if (order_opts->prefix)
		accumulate_size(write(fd, nb_descr->prefix, order_opts->prefix));
	if (order_opts->leading_zeros)
		write_padding(fd, order_opts->leading_zeros, '0');
	if (nb_descr->nb_len)
		ft_write_unsigned_base_fd(fd, nb_descr);
}

//	integers: precision determines minimum num of caracters,
//		ignores F_ZERO
//		override minwidth if greater
//		no output for zero if prec = 0
void	write_unb_in_order(
	int fd,
	const t_ft_printf_nb_description *nb_descr,
	const t_ft_printf_format *f_descr)
{
	t_ft_printf_output_order_options	order_opts;

	order_opts.prefix = ft_strlen(nb_descr->prefix);
	order_opts.leading_zeros = (f_descr->precision - nb_descr->nb_len);
	order_opts.leading_zeros *= (order_opts.leading_zeros > 0);
	order_opts.padding = (int)f_descr->min_width - order_opts.prefix;
	order_opts.padding
		-= ((f_descr->precision > nb_descr->nb_len) * f_descr->precision
			+ (f_descr->precision <= nb_descr->nb_len) * nb_descr->nb_len);
	order_opts.padding *= (order_opts.padding > 0);
	if (f_descr->flags & FT_F_MINUS)
		write_left_adjusted_odred(fd, nb_descr, &order_opts);
	else
	{
		if (f_descr->flags & FT_F_ZERO)
			write_right_adjusted_with_zeros(fd, nb_descr, &order_opts);
		else
			write_right_adjusted_with_spaces(fd, nb_descr, &order_opts);
	}
}
