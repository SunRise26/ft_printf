/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:07:07 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/26 16:38:33 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	mod_spec(int mod, va_list ap)
{
	intmax_t	res;

	if (mod == 0)
		res = va_arg(ap, int);
	else if ((mod >> 6) & 1)
		res = va_arg(ap, size_t);
	else if ((mod >> 5) & 1)
		res = va_arg(ap, intmax_t);
	else if ((mod >> 4) & 1)
		res = va_arg(ap, long long int);
	else if ((mod >> 3) & 1)
		res = va_arg(ap, long int);
	else if ((mod >> 2) & 1)
		res = (char)va_arg(ap, intmax_t);
	else if ((mod >> 1) & 1)
		res = (short)va_arg(ap, int);
	else if ((mod >> 7) & 1)
		res = va_arg(ap, ptrdiff_t);
	else
		res = va_arg(ap, int);
	return (res);
}

int			ft_num_size(intmax_t num, int prec, unsigned int flags)
{
	int			ct;
	intmax_t	n;

	if (num == 0 && prec == 0)
		return (0);
	ct = 0;
	n = num;
	while (++ct && n / 10 != 0)
		n /= 10;
	if (MB_CUR_MAX == 4 && ((flags >> 5) & 1))
	{
		if (ct % 3)
			ct += (ct / 3);
		else
			ct += (ct / 3) - 1;
	}
	return (ct);
}

char		*ft_itoa_intmax(intmax_t n, int ct, unsigned int flags)
{
	char		*ret;
	int			min;
	int			apos;

	apos = -1;
	min = 1;
	if (n < 0)
		min = -1;
	if (n < 0 || ((flags >> 3) & 1) || ((flags >> 2) & 1))
		ct += 1;
	ret = (char *)malloc(sizeof(char) * (ct + 1));
	ret[ct--] = '\0';
	while (ct != -1)
	{
		apos++;
		if (MB_CUR_MAX == 4 && n != 0 && ((flags >> 5) & 1) && apos == 3)
		{
			apos = 0;
			ret[ct--] = ',';
		}
		ret[ct] = '0' + min * (n % 10);
		n /= 10;
		ct--;
	}
	return (ft_int_flagch(ret, flags, min));
}

int			flags_ch0(unsigned int flags, intmax_t num)
{
	return (((flags >> 3) & 1) || ((flags >> 2) & 1) || num <= -1);
}

int			spec_di(t_spec spec, va_list ap)
{
	char		*str;
	char		*buf;
	intmax_t	num;
	int			ct;

	num = mod_spec(spec.mod, ap);
	if ((ct = ft_num_size(num, spec.prec, spec.flags)) < spec.prec)
		ct = spec.prec;
	else if ((spec.flags >> 4) & 1)
		;
	else if (ct < spec.width && spec.prec == -1 && (spec.flags & 1))
		ct = spec.width - flags_ch0(spec.flags, num);
	str = ft_itoa_intmax(num, ct, spec.flags);
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
