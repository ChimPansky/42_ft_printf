/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:33 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/04 20:05:51 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*result;

	result = ft_strjoin((const char *)s1, (const char *)s2);
	if (!result)
		return (NULL);
	if (to_free & 1)
		free(s1);
	if (to_free & 2)
		free(s2);
	return (result);
}
