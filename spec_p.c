/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:01:17 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/21 20:35:42 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_abase_16(uintmax_t num, int flags, int ct, char c)
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
	if (((flags >> 1) & 1) && (c == 'x' || c == 'X'))
	{
		ret[0] = '0';
		ret[1] = c;
	}
	return (ret);
}

int		spec_p(t_spec spec, va_list ap)
{
	char		*buf;
	char		*str;
	uintmax_t	num;
	int			ct;

	num = (uintmax_t)va_arg(ap, void *);
	if ((ct = ft_u_s(num, 16, &spec)) < spec.prec + ((spec.flags >> 1) & 1) * 2)
		ct = spec.prec;
	else if ((spec.flags >> 4) & 1)
		;
	else if (ct < spec.width && spec.flags & 1 && spec.prec == -1)
		ct = spec.width - ((num == 0) * 2);
	str = ft_abase_16(num, spec.flags, ct + ((num == 0) * 2), 'x');
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
