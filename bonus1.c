/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:31:08 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/23 19:29:22 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_bonus_star1(va_list ap)
{
	int	res;

	res = va_arg(ap, int);
	if (res < 0)
		return (-1);
	return (res);
}

int		ft_bonus_star2(va_list ap, int *flags)
{
	int	res;

	res = va_arg(ap, int);
	if (res < 0)
	{
		res *= -1;
		(*flags) |= 16;
	}
	return (res);
}

int		ft_prfout(char *s, int zero)
{
	int		res;

	res = 0;
	while (s[res])
		res++;
	if (zero == 2)
		write(1, "\0", 1);
	write(1, s, res);
	if (zero == 1)
		write(1, "\0", 1);
	return (res + (zero > 0));
}

int		ar1_out(int *i, const char *str)
{
	int		len;
	int		p;

	len = 0;
	p = *i;
	while (str[*i] && str[*i] != '%')
	{
		(*i)++;
		len++;
	}
	write(1, &str[p], len);
	return (len);
}

void	spec_nul(t_spec *spec, int slen)
{
	spec->flags = 0;
	spec->width = 0;
	spec->prec = -1;
	spec->mod = 0;
	spec->len = 0;
	spec->fl = 1;
	spec->dol = 0;
	spec->dw = 0;
	spec->dp = 0;
	spec->strlen = slen;
}
