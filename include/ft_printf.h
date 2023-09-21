#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft/libft.h"
# include <stdio.h>		// remove this before Evaluations...

typedef struct s_format
{
	int	flags;
	int	min_width;
	int precision;
} 			t_format;

enum e_flags
{
	F_HASH = 1,
	F_ZERO = 2,
	F_MINUS = 4,
	F_SPACE = 8,
	F_PLUS = 16,
	F_DOT = 32
};

//int	ft_printf(const char *, ...);
char	*convert_c(int c);
char	*convert_s(char *s);
char	*convert_p(void *p);
char	*convert_d(int	i);
int	convert_i(int	i, char *format);
int	convert_u(unsigned int i, char *format);
int	convert_x(unsigned int i, char *format);
int	convert_X(unsigned int i, char *format);

#endif
