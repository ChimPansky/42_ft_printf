#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

int	ft_printf(const char *, ...);
int	convert_c(int c, char *format);
int	convert_s(char *s, char *format);
int	convert_p(void *p, char *format);
int	convert_d(int	i, char *format);
int	convert_i(int	i, char *format);
int	convert_d(int	i, char *format);
int	convert_u(unsigned int i, char *format);
int	convert_x(unsigned int i, char *format);
int	convert_X(unsigned int i, char *format);

#endif
