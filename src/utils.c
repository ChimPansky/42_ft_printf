/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:37 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/07 15:15:01 by vvilensk         ###   ########.fr       */
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
	{
		if ((ssize_t)INT_MAX - sz - bytes_written < 0)
			sz = FT_PRINTF_WRITE_ERROR;
		else
			sz += bytes_written;
	}
	return (sz);
}

void	write_padding(int fd, int sz, char c)
{
	char	buf[FT_PRINTF_BUFFER_SIZE];

	ft_memset(buf, c, FT_PRINTF_BUFFER_SIZE);
	while (sz >= FT_PRINTF_BUFFER_SIZE)
	{
		accumulate_size(write(fd, buf, FT_PRINTF_BUFFER_SIZE));
		sz -= FT_PRINTF_BUFFER_SIZE;
	}
	if (sz)
		accumulate_size(write(fd, buf, sz));
}
