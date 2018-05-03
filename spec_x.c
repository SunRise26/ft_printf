/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:29:37 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/25 21:26:33 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_base_16(uintmax_t num, int flags, int ct, char c)
{
	char		*ret;
	char		x;
	int			oux;
	uintmax_t	n;

	oux = 16;
	n = num;
	if ((x = 'a') && c == 'X')
		x = 'A';
	ret = (char *)malloc(sizeof(char) * (ct + 1));
	ret[ct] = '\0';
	while (--ct != -1)
	{
		if (oux == 16 && (n % oux) > 9)
			ret[ct] = x + (n % oux) - 10;
		else
			ret[ct] = '0' + (n % oux);
		n /= oux;
	}
	if (num != 0 && ((flags >> 1) & 1) && (c == 'x' || c == 'X'))
	{
		ret[0] = '0';
		ret[1] = c;
	}
	return (ret);
}

int			spec_x(t_spec spec, va_list ap, char c)
{
	char		*buf;
	char		*str;
	uintmax_t	num;
	int			ct;

	num = umod_spec(spec.mod, ap);
	if ((ct = ft_u_s(num, 16, &spec)) < spec.prec + ((spec.flags >> 1) & 1) * 2)
		ct = spec.prec;
	else if ((spec.flags >> 4) & 1)
		;
	else if (ct < spec.width && spec.flags & 1 && spec.prec == -1)
		ct = spec.width;
	str = ft_base_16(num, spec.flags, ct, c);
	spec.flags = (spec.flags >> 3) << 3;
	if ((buf = str_width(str, spec.flags, spec.width)))
	{
		free(str);
		str = buf;
	}
	ct = ft_prfout(str, 0);
	free(str);
	return (ct);
}
