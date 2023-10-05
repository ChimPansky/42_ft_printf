/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:13:44 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/05 14:08:07 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_prefix(char *s, char *pre)
{
	char	*result;

	result = ft_strjoin_free(pre, s, 2);
	if (!result)
		return (s);
	return (result);
}

char	*pad_negative(char *s, char cpad, size_t width, int to_free)
{
	char	*result;

	result = s;
	*result = '0';
	result = ft_strlpad_free(result, cpad, width, to_free);
	if (result)
		*result = '-';
	return (result);
}
