/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manipulations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:13:03 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/05 22:52:23 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*apply_precision(char *s, int prec, char type);
static char	*apply_flags(char *s, int flags, char type);
static char	*apply_min_width(char *s, size_t width, int flags, char type);

char	*convert_diuxxp(char conv, va_list args)
{
	char			*result;
	unsigned int	arg_uxx;

	if (ft_strchr("di", conv))
		result = ft_itoa(va_arg(args, int));
	else if (ft_strchr("uxX", conv))
	{
		arg_uxx = va_arg(args, unsigned int);
		if (conv == 'u')
			result = ft_itoa_base_unsigned(arg_uxx, S_BASE_U);
		else if (conv == 'x')
			result = ft_itoa_base_unsigned(arg_uxx, S_BASE_HEX);
		else if (conv == 'X')
			result = ft_itoa_base_unsigned(arg_uxx, S_BASE_HEXL);
	}
	else if (conv == 'p')
	{
		result = va_arg(args, void *);
		if (!result)
			result = ft_strdup("(nil)");
		else
			result = ft_itoa_base_unsigned((size_t)result, S_BASE_HEX);
	}
	return (result);
}

char	*manipulate_s(char	*s, t_format conf)
{
	char	*result;

	result = s;
	if (conf.prec >= 0)
		result = apply_precision(result, conf.prec, conf.type);
	if (result && conf.type == 'p' && ft_strncmp(s, "(nil)", 6))
		result = add_prefix(result, "0x");
	if (result)
		result = apply_flags(result, conf.flags, conf.type);
	if (result && conf.width)
		result = apply_min_width(result, conf.width, conf.flags, conf.type);
	return (result);
}

static char	*apply_precision(char *s, int prec, char type)
{
	char	*result;
	char	*to_free;

	result = s;
	to_free = s;
	if (type == 's')
		result = ft_substr_free(s, 0, prec, 1);
	else if (ft_strchr("diupxX", type))
	{
		if (prec == 0 && *result == '0')
			*result = '\0';
		else if (prec > 0)
		{
			if (ft_strchr("di", type) && *s == '-'
				&& ft_strlen(s) < (size_t)prec + 1)
				result = pad_negative(result, '0', prec + 1, 1);
			else
				result = ft_strlpad_free(result, '0', prec, 1);
		}
	}
	if (!result)
		free(to_free);
	return (result);
}

static char	*apply_flags(char *s, int flags, char type)
{
	char	*result;
	char	*positive;

	result = s;
	if (flags & F_HASH)
	{
		if (ft_strchr("xX", type) && *s != '0')
		{
			if (type == 'x')
				result = add_prefix(result, "0x");
			else
				result = add_prefix(result, "0X");
		}
	}
	if (((flags & F_PLUS) || (flags & F_SPACE))
		&& ft_strchr("di", type) && *result != '-')
	{
		positive = ft_iif_ptr((flags & F_PLUS), "+", " ");
		result = add_prefix(result, positive);
	}
	return (result);
}

static char	*apply_min_width(char *s, size_t width, int flags, char type)
{
	char	*result;
	char	*to_free;

	to_free = s;
	result = s;
	if (flags & F_MINUS)
		result = ft_strrpad_free(result, ' ', width, 1);
	else if (ft_strchr("diupxX", type) && flags & F_ZERO)
	{
		if (ft_strchr("di", type) && *s == '-' && ft_strlen(result) < width)
			result = pad_negative(result, '0', width, 1);
		else
			result = ft_strlpad_free(result, '0', width, 1);
	}
	else
		result = ft_strlpad_free(result, ' ', width, 1);
	if (!result)
		free(to_free);
	return (result);
}
