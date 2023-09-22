#include "../include/ft_printf.h"



int	convert_c(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}
int	convert_s(char *s)
{
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}
int	convert_base(char c, int nbr)
{
	if (c == 'i' || c == 'd')
		return (ft_putnbr_base_fd(1, nbr, "0123456789"));
	if (c == 'x')
		return (ft_putnbr_base_fd(1, nbr, "0123456789abcdef"));
	if (c == 'X')
		return (ft_putnbr_base_fd(1, nbr, "0123456789ABCDEF"));
	return(0);
}
int	convert_unsigned_base(char c, size_t nbr)
{
	if (c == 'u')
		return (ft_putunsigned_base_fd(1, nbr, "0123456789"));
	return(0);
}
int	convert_p(void *ptr)
{
	return (ft_putunsigned_base_fd(1, (size_t)ptr, "0123456789abcdef"));
	//ft_putstr_fd(s, 1);
	//return (ft_strlen(s));
}


/*
char	*convert_c(int c);
char	*convert_s(char *s);
char	*convert_p(void *p);
char	*convert_d(int	i);

int	convert_i(int	i, char *format);
int	convert_d(int	i, char *format);
int	convert_u(unsigned int i, char *format);
int	convert_x(unsigned int i, char *format);
int	convert_X(unsigned int i, char *format);
*/

// all the convert_ functions return to caller function, where format will be adjusted through other functions and s_format as well as e_flags structures (see header)...
