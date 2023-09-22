//#include "../include/ft_printf.h"
#include "ft_printf.h"
ssize_t	ft_putunsigned_base_fd(int fd, unsigned int nbr, char* base_str)
{
	ssize_t	sz;
    const   size_t base = ft_strlen(base_str);
    size_t ord;

    sz = 0;
    ord = 1;
    while (nbr / base >= ord)
        ord *= base;
    while (ord)
    {
        sz += write(fd, base_str + (nbr / ord % base), 1);
        ord /= base;
    }
	return (sz);
}

ssize_t	ft_putsizet_base_fd(int fd, size_t nbr, char* base_str)
{
	ssize_t	sz;
    const   size_t base = ft_strlen(base_str);
    size_t ord;

    sz = 0;
    ord = 1;
    while (nbr / base >= ord)
        ord *= base;
    while (ord)
    {
        sz += write(fd, base_str + (nbr / ord % base), 1);
        ord /= base;
    }
	return (sz);
}

ssize_t	ft_putnbr_base_fd(int fd, int nbr, char* base_str)
{
	if (nbr >= 0)
		return (ft_putunsigned_base_fd(fd, nbr, base_str));
	return (write(fd, "-", 1) + ft_putunsigned_base_fd(fd, -1l * nbr, base_str));
}

#ifdef TEST_putnbr_base
#include <stdlib.h>
int main(int ac, char *av[ac])
{
    ft_putnbr_base_fd(1, atoi(av[1]), "0123456789abcdef");
}
#endif
