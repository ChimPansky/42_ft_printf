/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:25 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/07 11:12:28 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_P_H
# define FT_PRINTF_P_H

# include <unistd.h>
# include <stdint.h>
# include <stddef.h>
# include <stdarg.h>
# include "libft.h"

// accumulate_size_defines
# define FT_PRINTF_AS_GET_SIZE_AND_RESET -3
# define FT_PRINTF_AS_GET_SIZE -2
# define FT_PRINTF_WRITE_ERROR -1

# define FT_PRINTF_BUFFER_SIZE 64

# define FT_PRINTF_FLAGS_STRING "#0- +"

enum e_ft_printf_flags
{
	FT_PRINTF_HASH		= 1 << 0,
	FT_PRINTF_ZERO		= 1 << 1,
	FT_PRINTF_MINUS		= 1 << 2,
	FT_PRINTF_SPACE		= 1 << 3,
	FT_PRINTF_PLUS		= 1 << 4,
	FT_PRINTF_PRESISION	= 1 << 5,
	FT_PRINTF_MIN_WIDTH	= 1 << 6,
};

// default size for integer tipes is int
// default size for floating point types is double
// hh	Integers, expects an int-sized integer argument, promoted from a char.
// h	Integers, expects an int-sized integer argument, promoted from a short.
// ll	Integers, expects a long long-sized integer argument.
// l	Integers, expects a long-sized integer argument.
// z	Integers, expects a size_t-sized integer argument.
// j	Integers, expects a intmax_t-sized integer argument.
// t	Integers, expects a ptrdiff_t-sized integer argument.
// L	Floating-point types, expects a long double argument.
enum e_ft_printf_length_modifier
{
	FT_PRINTF_NULL = 0,
	FT_PRINTF_h,
	FT_PRINTF_hh,
	FT_PRINTF_l,
	FT_PRINTF_ll,
	FT_PRINTF_z,
	FT_PRINTF_j,
	FT_PRINTF_t,
	FT_PRINTF_L,
};

typedef struct s_ft_printf_format
{
	unsigned int						flags;
	unsigned int						min_width;
	int									precision;
	int									format_incorrect;
	char								conversion;
	enum e_ft_printf_length_modifier	length_modifier;
}		t_ft_printf_format;

typedef struct s_ft_printf_nb_description
{
	uintmax_t		nb;
	const char		*base;
	int				base_len;
	int				nb_len;
	const char		*prefix;
	const char		*hash;
}		t_ft_printf_nb_description;

typedef struct s_ft_printf_output_order_options
{
	int	padding;
	int	leading_zeros;
	int	prefix;
}		t_ft_printf_output_order_options;

// static finctions in headers ?
int			accumulate_size(ssize_t bytes_written);
void		write_padding(int fd, int sz, char c);

intmax_t	get_signed(enum e_ft_printf_length_modifier len, va_list ap);
uintmax_t	get_unsigned(enum e_ft_printf_length_modifier len, va_list ap);
int			count_unb_len(uintmax_t nb, int base_len, int precision);
void		ft_write_unsigned_base_fd(
				int fd,
				const t_ft_printf_nb_description *nb_descr);

void		write_unb_in_order(
				int fd,
				const t_ft_printf_nb_description *nb_descr,
				const t_ft_printf_format *f_descr);

void		write_string(int fd, t_ft_printf_format *f_descr, const char *str);
void		write_char(int fd, t_ft_printf_format *f_descr, char c);
void		write_signed(int fd, t_ft_printf_format *f_descr, intmax_t nb);
void		write_unsigned(int fd, t_ft_printf_format *f_descr, uintmax_t nb);
void		write_ptr(int fd, t_ft_printf_format *f_descr, const void *ptr);

void		parse_min_width(
				const char **format,
				t_ft_printf_format *f_descr,
				va_list ap);
void		parse_flags(
				const char **format,
				t_ft_printf_format *f_descr);
void		parse_precision(
				const char **format,
				t_ft_printf_format *f_descr,
				va_list ap);
void		parse_lenghth_modifier(
				const char **format,
				t_ft_printf_format *f_descr);
void		parse_format_and_write(
				int fd,
				const char **format,
				t_ft_printf_format *f_descr,
				va_list ap);

/*
void		write_double(int fd, t_ft_printf_format *f_descr, long double nb);
long double	get_double(enum e_ft_printf_length_modifier len, va_list ap);
*/

#endif  // FT_PRINTF_P_H
