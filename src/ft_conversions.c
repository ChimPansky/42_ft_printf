#include "../include/ft_printf.h"

int	convert_c(int c, char *format);
int	convert_s(char *s, char *format);
int	convert_p(void *p, char *format);
int	convert_d(int	i, char *format);
int	convert_i(int	i, char *format);
int	convert_d(int	i, char *format);
int	convert_u(unsigned int i, char *format);
int	convert_x(unsigned int i, char *format);
int	convert_X(unsigned int i, char *format);


// all the convert_ functions write to standard output and return number of bytes written to the caller function ft_printf...

// use ft_putchar_fd and ft_putstr_fd
