/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlpad_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:07:43 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/04 20:01:50 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Left Pad a String <s> with a character <cpad> to reach a certain
	size <target_size> and afterwards free the original string*/
char	*ft_strlpad_free(char *s, char cpad, size_t target_size, int to_free)
{
	char	*result;

	result = ft_strlpad((const char *)s, cpad, target_size);
	if (!result)
		return (NULL);
	if (to_free)
		free(s);
	return (result);
}
