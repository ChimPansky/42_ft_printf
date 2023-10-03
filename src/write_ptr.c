/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:48 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/04 01:25:55 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

void	write_ptr(int fd, t_ft_printf_format *f_descr, const void *ptr)
{
	if (ptr == NULL)
		write_string(fd, f_descr, "(nil)");
	else
	{
		f_descr->conversion = 'x';
		f_descr->flags |= FT_F_HASH;
		f_descr->length_modifier = FT_L_z;
		write_unsigned(fd, f_descr, (size_t)ptr);
	}
}
