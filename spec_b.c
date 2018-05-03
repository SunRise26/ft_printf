/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:50:38 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/22 20:37:53 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_bin_size(uintmax_t num, int prec, unsigned int flags)
{
	int			ct;
	uintmax_t	n;

	if (num == 0 && prec == 0)
		return (0);
	ct = 0;
	n = num;
	while (++ct && n / 2 != 0)
		n /= 2;
	if ((flags >> 2) & 1)
	{
		if (ct < 9)
			ct += 8 - ct;
		else if (ct < 17)
			ct += 17 - ct;
		else if (ct < 33)
			ct += 35 - ct;
		else if (ct < 65)
			ct += 72 - ct;
	}
	return (ct);
}

char		*ft_itoa_bin(uintmax_t n, int ct, unsigned int flags)
{
	char		*ret;
	int			sp;

	ret = (char *)malloc(sizeof(char) * (ct + 1));
	ret[ct] = '\0';
	sp = 1;
	while (--ct != -1)
	{
		sp++;
		if (((flags >> 2) & 1) && (sp % 9) == 1)
		{
			ret[ct] = ' ';
			sp = 1;
		}
		else
		{
			ret[ct] = 48 + (n % 2);
			n /= 2;
		}
	}
	return (ret);
}

int			spec_b(t_spec spec, va_list ap)
{
	int			ct;
	char		*str;
	char		*buf;
	uintmax_t	num;

	ct = 0;
	num = va_arg(ap, uintmax_t);
	if ((ct = ft_bin_size(num, spec.prec, spec.flags)) < spec.prec)
		ct = spec.prec;
	else if ((spec.flags >> 4) & 1)
		;
	else if (ct < spec.width && spec.prec == -1 && (spec.flags & 1))
		ct = spec.width;
	str = ft_itoa_bin(num, ct, spec.flags);
	spec.flags = (spec.flags >> 3) << 3;
	buf = str_width(str, spec.flags, spec.width);
	if (buf)
	{
		free(str);
		str = buf;
	}
	ct = ft_prfout(str, 0);
	free(str);
	return (ct);
}
