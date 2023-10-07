/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:48 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/07 10:45:29 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

// "%p" == "%#x" with sizeof(void *)
// assert(sizeof(void *) <= sizeof(intmax))
void	write_ptr(int fd, t_ft_printf_format *f_descr, const void *ptr)
{
	if (ptr == NULL)
		write_string(fd, f_descr, "(nil)");
	else
	{
		f_descr->conversion = 'x';
		f_descr->flags |= FT_PRINTF_HASH;
		write_unsigned(fd, f_descr, (uintmax_t)ptr);
	}
}
