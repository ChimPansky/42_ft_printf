#include "../include/ft_printf.h"

char	*convert_c(int c);
char	*convert_s(char *s);
char	*convert_p(void *p);
char	*convert_d(int	i);
/*
int	convert_i(int	i, char *format);
int	convert_d(int	i, char *format);
int	convert_u(unsigned int i, char *format);
int	convert_x(unsigned int i, char *format);
int	convert_X(unsigned int i, char *format);
*/

// all the convert_ functions return to caller function, where format will be adjusted through other functions and s_format as well as e_flags structures (see header)...


