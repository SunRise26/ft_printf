/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:08:10 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/25 21:14:47 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_base_10(uintmax_t n, int ct, unsigned int flags)
{
	char		*ret;
	int			apos;

	apos = -1;
	ret = (char *)malloc(sizeof(char) * (ct + 1));
	ret[ct] = '\0';
	while (--ct != -1)
	{
		apos++;
		if (MB_CUR_MAX == 4 && n != 0 && ((flags >> 5) & 1) && apos == 3)
		{
			apos = 0;
			ret[ct--] = ',';
		}
		ret[ct] = '0' + (n % 10);
		n /= 10;
	}
	return (ret);
}

int			spec_u(t_spec spec, va_list ap)
{
	char		*buf;
	char		*str;
	uintmax_t	num;
	int			ct;

	num = umod_spec(spec.mod, ap);
	ct = ft_u_s(num, 10, &spec);
	if (ct < spec.prec)
		ct = spec.prec;
	else if ((spec.flags >> 4) & 1)
		;
	else if (ct < spec.width && (spec.flags & 1) && spec.prec == -1)
		ct = spec.width;
	str = ft_base_10(num, ct, spec.flags);
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
