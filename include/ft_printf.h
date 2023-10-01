#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
//# include <stdint.h>
//# include <stddef.h>
# include <stdio.h>  // REMOVE THIS



// accumulate_size_defines
//# define GET_SIZE_AND_RESET -2
//# define WRITE_ERROR -1


# define S_FLAGS "#0- +"
enum e_flags
{
	F_HASH = 1,
	F_ZERO = 2,
	F_MINUS = 4,
	F_SPACE = 8,
	F_PLUS = 16,
	F_PRECISION = 32,
	F_MIN_WIDTH = 64,
};

typedef struct s_format
{
	int	flags;
	int	min_width;
	int precision;
} 			t_format;


int	ft_printf(const char *, ...);

#endif  // FT_PRINTF_H


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
