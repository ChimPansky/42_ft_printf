#include "ft_printf_p.h"
#include <stdint.h>

void	ft_write_unsigned_base_fd(int fd, t_ft_printf_nb_description *nb_descr)
{
	const	int bits_in_byte = 8;
	char	buf[sizeof(uintmax_t) * bits_in_byte];
	size_t	ord;
	size_t	idx;
	uintmax_t nb = nb_descr->nb;

	idx = 0;
	ord = 1;
	while (nb / nb_descr->base_len >= ord)
		ord *= nb_descr->base_len;
	while (ord)
	{
		buf[idx++] = nb_descr->base[nb / ord % nb_descr->base_len];
		ord /= nb_descr->base_len;
	}
	accumulate_size(write(fd, buf, nb_descr->nb_len));
}

//	integers: precision determines minimum num of caracters,
//		ignores F_ZERO, override minwidth if greater, no output for zero if prec = 0
void write_unb_with_prefix(int fd, t_ft_printf_nb_description *nb_descr, t_ft_printf_format *f_descr)
{
	const size_t prefix_len = ft_strlen(nb_descr->prefix);
	int padding_len;

	if (f_descr->precision > nb_descr->nb_len)
		padding_len = (int)f_descr->min_width - f_descr->precision - prefix_len;
	else
		padding_len = (int)f_descr->min_width - nb_descr->nb_len - prefix_len;
	padding_len = padding_len * (padding_len > 0);
	if (f_descr->flags & FT_F_MINUS)
	{
		if (prefix_len)
			accumulate_size(write(fd, nb_descr->prefix, prefix_len));
		if (nb_descr->nb_len < f_descr->precision)
			write_padding(fd, f_descr->precision - nb_descr->nb_len, '0');
		if (nb_descr->nb_len)
			ft_write_unsigned_base_fd(fd, nb_descr);
		if (padding_len)
			write_padding(fd, padding_len, ' ');
	}
	else
	{
		if (f_descr->flags & FT_F_ZERO)
		{
			if (prefix_len)
				accumulate_size(write(fd, nb_descr->prefix, prefix_len));
			if (padding_len)
				write_padding(fd, padding_len, '0');
			if (nb_descr->nb_len < f_descr->precision)
				write_padding(fd, f_descr->precision - nb_descr->nb_len, '0');
			ft_write_unsigned_base_fd(fd, nb_descr);
		}
		else
		{
			if (padding_len)
				write_padding(fd, padding_len, ' ');
			if (prefix_len)
				accumulate_size(write(fd, nb_descr->prefix, prefix_len));
			if (nb_descr->nb_len < f_descr->precision)
				write_padding(fd, f_descr->precision - nb_descr->nb_len, '0');
			if (nb_descr->nb_len)
				ft_write_unsigned_base_fd(fd, nb_descr);
		}
	}
}

void write_signed(int fd, t_ft_printf_format *f_descr, intmax_t nb)
{
	t_ft_printf_nb_description nb_descr;

	if (!(f_descr->flags & FT_F_PRESISION))
		f_descr->precision = 1;
	else
		f_descr->flags &= ~FT_F_ZERO;
	nb_descr.prefix = "";
	nb_descr.base = "0123456789";
	nb_descr.base_len = 10;
	if (INTMAX_MIN == nb)
		nb_descr.nb = (uintmax_t)INTMAX_MAX + 1;
	else if (nb < 0)
		nb_descr.nb = -nb;
	else
		nb_descr.nb = nb;
	nb_descr.nb_len = count_unb_len(nb_descr.nb, nb_descr.base_len, f_descr->precision);
	if (nb < 0)
		nb_descr.prefix = "-";
	else if (nb && (f_descr->flags & FT_F_PLUS))
		nb_descr.prefix = "+";
	else if (nb && (f_descr->flags & FT_F_SPACE))
		nb_descr.prefix = " ";
	write_unb_with_prefix(fd, &nb_descr, f_descr);
}

//	F_SPACE, F_PLUS are ignored
//	o:		unsigned int in octal. F_HASH prepends "0" to a nonzero result  // check with leading zeros of prec and F_FT_ZERO
//	u:		Print decimal unsigned int.
//	x, X:	unsigned int in hex. X uses lower-case, X uses upper-case.
//		F_HASH prepends "0x" or "0X" to a nonzero result
void write_unsigned(int fd, t_ft_printf_format *f_descr, uintmax_t nb)
{
	t_ft_printf_nb_description nb_descr;

	if (!(f_descr->flags & FT_F_PRESISION))
		f_descr->precision = 1;
	else
		f_descr->flags &= ~FT_F_ZERO;
	nb_descr.prefix = "";
	if (f_descr->conversion == 'x')
		nb_descr.base = "0123456789abcdef";
	else if (f_descr->conversion == 'X')
		nb_descr.base = "0123456789ABCDEF";
	else if (f_descr->conversion == 'o')
		nb_descr.base = "01234567";
	else if (f_descr->conversion == 'u')
		nb_descr.base = "0123456789";
	nb_descr.nb = nb;
	nb_descr.base_len = ft_strlen(nb_descr.base);
	nb_descr.nb_len = count_unb_len(nb_descr.nb, nb_descr.base_len, f_descr->precision);
	if (nb && (f_descr->flags & FT_F_HASH) && f_descr->conversion == 'x')
		nb_descr.prefix = "0x";
	else if (nb && (f_descr->flags & FT_F_HASH) && f_descr->conversion == 'X')
		nb_descr.prefix = "0X";
	else if (nb && (f_descr->flags & FT_F_HASH) && f_descr->conversion == 'o')
		nb_descr.prefix = "0";
	write_unb_with_prefix(fd, &nb_descr, f_descr);
}
