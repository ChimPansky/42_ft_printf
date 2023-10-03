/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:14 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/03 23:01:15 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_printf_fd(int fd, const char *format, ...);
int	ft_vprintf_fd(int fd, const char *format, va_list ap);

#endif  // FT_PRINTF_H
