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

# define FT_PRINTF_FLAGS_STRING "#0- +"
enum e_ft_printf_flags
{
	FT_F_HASH = 1,
	FT_F_ZERO = 2,
	FT_F_MINUS = 4,
	FT_F_SPACE = 8,
	FT_F_PLUS = 16,
	FT_F_PRESISION = 32,
	FT_F_MIN_WIDTH = 64,
};

// default size for integer tipes is int
// default size for floating point types is double
// hh	For integer types, causes printf to expect an int-sized integer argument which was promoted from a char.
// h	For integer types, causes printf to expect an int-sized integer argument which was promoted from a short.
// ll	For integer types, causes printf to expect a long long-sized integer argument.
// l	For integer types, causes printf to expect a long-sized integer argument.
// z	For integer types, causes printf to expect a size_t-sized integer argument.
// j	For integer types, causes printf to expect a intmax_t-sized integer argument.
// t	For integer types, causes printf to expect a ptrdiff_t-sized integer argument.
// L	For floating-point types, causes printf to expect a long double argument.
enum e_ft_printf_length_modifier
{
	FT_L_NULL = 0,
	FT_L_h,
	FT_L_hh,
	FT_L_l,
	FT_L_ll,
	FT_L_z,
	FT_L_j,
	FT_L_t,
	FT_L_L,
};

typedef struct s_ft_printf_format
{
	int									flags;
	unsigned							min_width;
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
}		t_ft_printf_nb_description;

int		accumulate_size(ssize_t bytes_written);
void	write_padding(int fd, int sz, char c);
intmax_t	get_signed(enum e_ft_printf_length_modifier len, va_list ap);
uintmax_t   get_unsigned(enum e_ft_printf_length_modifier len, va_list ap);
int		count_unb_len(uintmax_t nb, int base_len, int precision);

void	write_string(int fd, t_ft_printf_format *f_descr, char *str);
void	write_char(int fd, t_ft_printf_format *f_descr, char c);
void	write_signed(int fd, t_ft_printf_format *f_descr, intmax_t nb);
void	write_unsigned(int fd, t_ft_printf_format *f_descr, uintmax_t nb);
void	write_ptr(int fd, t_ft_printf_format *f_descr, void *ptr);

void	parse_min_width(const char **format, t_ft_printf_format *f_descr, va_list ap);
void	parse_flags(const char **format, t_ft_printf_format *f_descr);
void	parse_precision(const char **format, t_ft_printf_format *f_descr, va_list ap);
void	parse_lenghth_modifier(const char **format, t_ft_printf_format *f_descr);
void	parse_format_and_write(int fd, const char **format, t_ft_printf_format *f_descr, va_list ap);


#endif  // FT_PRINTF_P_H
