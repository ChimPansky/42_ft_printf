/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlpad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:07:43 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/05 11:27:50 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Left Pad a String <s> with a character <cpad> to reach a certain
	size <target_size>*/
char	*ft_strlpad(const char *s, char cpad, size_t target_size)
{
	size_t	s_len;
	char	*result;
	char	*spad;

	s_len = ft_strlen(s);
	if (s_len >= target_size)
		return (ft_strdup(s));
	spad = ft_strreplicate(cpad, target_size - s_len);
	if (!spad)
		return (NULL);
	result = ft_strjoin(spad, s);
	free(spad);
	return (result);
}
