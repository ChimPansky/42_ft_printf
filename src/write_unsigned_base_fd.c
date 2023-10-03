/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_unsigned_base_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:30:10 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/04 00:32:09 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

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
