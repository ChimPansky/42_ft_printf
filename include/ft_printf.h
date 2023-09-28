#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//# include "../libft/libft.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>		// remove this before Evaluations...

#define GET_SIZE_AND_RESET -2
#define WRITE_ERROR -1
#define FLAGS_STRING "#0- +"
enum e_flags
{
	F_HASH = 1,
	F_ZERO = 2,
	F_MINUS = 4,
	F_SPACE = 8,
	F_PLUS = 16,
	F_PRESISION = 32,
	F_MIN_WIDTH = 64,
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
enum e_length_modifier
{
	L_NULL,
	L_h,
	L_hh,
	L_l,
	L_ll,
	L_z,
	L_j,
	L_t,
	L_L,
};

typedef struct s_format
{
	int	flags;
	int	min_width;
	int precision;
	enum e_length_modifier length_modifier;
} 			t_format;

int	ft_printf(const char *, ...);
ssize_t	ft_putnbr_base_fd(int fd, int nbr, char* base_str);
ssize_t	ft_putunsigned_base_fd(int fd, unsigned int nbr, char* base_str);
ssize_t	ft_putsizet_base_fd(int fd, size_t nbr, char* base_str);
int	convert_c(int c);
int	convert_s(char *s);
int	convert_base(char c, int nbr);
int	convert_unsigned_base(char c, size_t nbr);
int	convert_p(void *p);

#endif
