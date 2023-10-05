/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:29:22 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/05 22:48:08 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define S_FLAGS "#0- +"
# define S_CONVERSIONS "csdiupxX"
# define S_BASE_U "0123456789"
# define S_BASE_HEX "0123456789abcdef"
# define S_BASE_HEXL "0123456789ABCDEF"

enum e_flags
{
	F_HASH = 1,
	F_ZERO = 2,
	F_MINUS = 4,
	F_SPACE = 8,
	F_PLUS = 16,
	F_PRECISION = 32,
	F_MIN_WIDTH = 64
};

typedef struct s_format
{
	int		flags;
	size_t	width;
	int		prec;
	char	type;
}			t_format;

int		ft_printf(const char *format, ...);
int		ft_printf_fd(int fd, const char *format, va_list args);
int		output_percent(int fd, const char **format);
int		output_conversion(int fd, t_format conf, va_list args);
int		output_c(int fd, t_format conf, va_list args);
int		output_regular(int fd, const char **format);
int		set_config(const char **format, t_format *conf);
char	*convert_diuxxp(char conv, va_list args);
char	*manipulate_s(char	*s, t_format conf);
char	*add_prefix(char *s, char *pre);
char	*pad_negative(char *s, char cpad, size_t width, int to_free);

#endif
