//#include "../include/ft_printf.h"
#include "ft_printf.h"
int	convert_c(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}
int	convert_s(char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}
int	convert_base(char c, int nbr)
{
	if (c == 'i' || c == 'd')
		return (ft_putnbr_base_fd(1, nbr, "0123456789"));
	if (c == 'x')
		return (ft_putunsigned_base_fd(1, nbr, "0123456789abcdef"));
	if (c == 'X')
		return (ft_putunsigned_base_fd(1, nbr, "0123456789ABCDEF"));
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
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	return (2 + ft_putsizet_base_fd(1, (size_t)ptr, "0123456789abcdef"));
}
