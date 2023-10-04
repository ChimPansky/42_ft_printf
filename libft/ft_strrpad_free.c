/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrpad_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:56:52 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/04 19:59:17 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Right Pad a String <s> with a character <cpad> to reach a certain
	size <target_size> and afterwards free the original string*/
char	*ft_strrpad_free(char *s, char cpad, size_t target_size, int to_free)
{
	char	*result;

	result = ft_strrpad((const char *)s, cpad, target_size);
	if (!result)
		return (NULL);
	if (to_free)
		free(s);
	return (result);
}
