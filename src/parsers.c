/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:01:33 by vvilensk          #+#    #+#             */
/*   Updated: 2023/10/07 10:36:49 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf_p.h"

// negative width activates F_MINUS
void	parse_min_width(
			const char **format,
			t_ft_printf_format *f_descr,
			va_list ap)
{
	int	variadic_min_width;

	if (**format == '*')
	{
		variadic_min_width = va_arg(ap, int);
		if (variadic_min_width < 0)
		{
			f_descr->flags |= FT_PRINTF_MINUS;
			if (variadic_min_width == INT_MIN)
				f_descr->min_width = (unsigned)INT_MAX + 1;
			else
				f_descr->min_width = -variadic_min_width;
		}
		else
			f_descr->min_width = variadic_min_width;
		*format += 1;
	}
	else
		f_descr->min_width = ft_atoi_shift(format);
	if (f_descr->min_width)
		f_descr->flags |= FT_PRINTF_MIN_WIDTH;
}

//	F_ZERO:		For integers
//		The converted value is padded on the left with zeros rather than blanks.
//		If the F_ZERO and F_MINUS flags both appear, the F_ZERO flag is ignored.
//		If a precision is given, the F_ZERO flag is ignored.
//	F_MINUS:
//		The converted value is to be left adjusted on the field boundary.
//		The default is right justification
//		F_MINUS overrides F_ZERO if both are used.
//	F_SPACE:	For signed numbers
//		A space should be left before a positive number (or empty string)
//	F_PLUS:		For signed numbers
//		A  sign (+ or -) should always be placed before a number
//		By default, a sign is used only for negative numbers.
//		F_PLUS overrides F_SPACE if both are used.
//	F_HASH:		For x, X, o conversions of a nonzero nums
//		add "0x", "0X", "0" prefix corresponededly
void	parse_flags(const char **format, t_ft_printf_format *f_descr)
{
	const char	*flags_string = FT_PRINTF_FLAGS_STRING;
	const char	*next = ft_strchr_no_eol(flags_string, **format);

	while (next)
	{
		f_descr->flags |= (1 >> (next - flags_string));
		*format += 1;
		next = ft_strchr_no_eol(flags_string, **format);
	}
	if ((f_descr->flags & FT_PRINTF_ZERO) && (f_descr->flags & FT_PRINTF_MINUS))
		f_descr->flags &= ~FT_PRINTF_ZERO;
	if ((f_descr->flags & FT_PRINTF_SPACE) && (f_descr->flags & FT_PRINTF_PLUS))
		f_descr->flags &= ~FT_PRINTF_SPACE;
}

// Minus not allowed after '.' even for floating point nums
// For ints if precision is zero nothing should be displayed
// For strings determines max length
void	parse_precision(
			const char **format,
			t_ft_printf_format *f_descr,
			va_list ap)
{
	int	variadic_precision;

	if (**format != '.')
		return ;
	*format += 1;
	if (!ft_strchr_no_eol("0123456789*", **format))
		variadic_precision = 0;
	else if (**format == '*')
	{
		variadic_precision = va_arg(ap, int);
		*format += 1;
	}
	else
		variadic_precision = ft_atoi_shift(format);
	if (variadic_precision < 0)
	{
		f_descr->flags &= ~FT_PRINTF_PRESISION;
		return ;
	}
	f_descr->flags |= FT_PRINTF_PRESISION;
	f_descr->precision = variadic_precision;
}

void	parse_lenghth_modifier(const char **format, t_ft_printf_format *f_descr)
{
	if (ft_strncmp(*format, "hh", 2) == 0)
		f_descr->length_modifier = FT_PRINTF_hh;
	else if (ft_strncmp(*format, "ll", 2) == 0)
		f_descr->length_modifier = FT_PRINTF_ll;
	else if (ft_strncmp(*format, "h", 1) == 0)
		f_descr->length_modifier = FT_PRINTF_h;
	else if (ft_strncmp(*format, "l", 1) == 0)
		f_descr->length_modifier = FT_PRINTF_l;
	else if (ft_strncmp(*format, "z", 1) == 0)
		f_descr->length_modifier = FT_PRINTF_z;
	else if (ft_strncmp(*format, "j", 1) == 0)
		f_descr->length_modifier = FT_PRINTF_j;
	else if (ft_strncmp(*format, "t", 1) == 0)
		f_descr->length_modifier = FT_PRINTF_t;
	else if (ft_strncmp(*format, "L", 1) == 0)
		f_descr->length_modifier = FT_PRINTF_L;
	if (ft_strncmp(*format, "hh", 2) == 0 || ft_strncmp(*format, "ll", 2) == 0)
		*format += 2;
	if (ft_strchr_no_eol("hlzjtL", **format))
		*format += 1;
}

// %:		Prints a literal % character. any format modifiers are ignored.
// c:		char (character)
// s:		null-terminated string (or no-more-than-precision-length string)
// di:		int as a signed integer. %d and %i are synonymous for output
// oxXu:	unsigned ints in diff base
// p:		Pointer (%p == %#zx)
// unimplemented flags: eE fF gG aA m n
void	parse_format_and_write(
			int fd,
			const char **format,
			t_ft_printf_format *f_descr,
			va_list ap)
{
	f_descr->conversion = **format;
	if (f_descr->conversion == '%')
		accumulate_size(write(fd, *format, 1));
	else if (f_descr->conversion == 'c')
		write_char(fd, f_descr, (unsigned char)va_arg(ap, int));
	else if (f_descr->conversion == 's')
		write_string(fd, f_descr, va_arg(ap, char *));
	else if (ft_strchr_no_eol("di", f_descr->conversion))
		write_signed(fd, f_descr, get_signed(f_descr->length_modifier, ap));
	else if (ft_strchr_no_eol("oxXu", f_descr->conversion))
		write_unsigned(fd, f_descr, get_unsigned(f_descr->length_modifier, ap));
	else if (f_descr->conversion == 'p')
		write_ptr(fd, f_descr, va_arg(ap, void *));
	if (ft_strchr_no_eol("%scdioxXup", f_descr->conversion))
		*format += 1;
	else
		f_descr->format_incorrect = 1;
}

/*
else if (ft_strchr_no_eol("fFeEgG", f_descr->conversion))
	write_double(fd, f_descr, get_double(f_descr->length_modifier, ap));
else if (f_descr->conversion == 'n')
	write_output_sz(fd, f_descr, va_arg(ap, void *));
*/
