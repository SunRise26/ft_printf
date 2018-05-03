/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_oux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 12:12:59 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/25 21:23:56 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	umod_spec(int mod, va_list ap)
{
	uintmax_t	res;

	if (mod == 0)
		res = va_arg(ap, unsigned int);
	else if ((mod >> 6) & 1)
		res = va_arg(ap, size_t);
	else if ((mod >> 5) & 1)
		res = va_arg(ap, uintmax_t);
	else if ((mod >> 4) & 1)
		res = va_arg(ap, unsigned long long int);
	else if ((mod >> 3) & 1)
		res = va_arg(ap, unsigned long int);
	else if ((mod >> 2) & 1)
		res = (unsigned char)va_arg(ap, uintmax_t);
	else if ((mod >> 1) & 1)
		res = (unsigned short)va_arg(ap, int);
	else if ((mod >> 7) & 1)
		res = va_arg(ap, ptrdiff_t);
	else
		res = va_arg(ap, unsigned int);
	return (res);
}

int			ft_u_s(uintmax_t num, int oux, t_spec *spec)
{
	int				ct;
	uintmax_t		n;

	ct = 0;
	n = num;
	while (++ct && n / oux != 0)
		n /= oux;
	if (oux == 8 && (((*spec).flags >> 1) & 1) && num != 0)
		ct += 1;
	else if (oux == 16 && num != 0 && (((*spec).flags >> 1) & 1))
	{
		if ((*spec).prec > ct)
			(*spec).prec += 2;
		else
			ct += 2;
	}
	if (num == 0 && (*spec).prec == 0)
		ct = 0;
	if (oux == 10 && MB_CUR_MAX == 4 && ((spec->flags >> 5) & 1) && !(ct % 3))
		ct += (ct / 3) - 1;
	else if (oux == 10 && MB_CUR_MAX == 4 && ((spec->flags >> 5) & 1) && ct % 3)
		ct += (ct / 3);
	return (ct);
}

char		*ft_base_8(uintmax_t n, int flags, int ct)
{
	char		*ret;

	ret = (char *)malloc(sizeof(char) * (ct + 1));
	ret[ct] = '\0';
	while (--ct != -1)
	{
		ret[ct] = '0' + (n % 8);
		n /= 8;
	}
	if ((flags >> 1) & 1)
		ret[0] = '0';
	return (ret);
}

int			spec_oux(t_spec spec, va_list ap)
{
	char		*buf;
	char		*str;
	uintmax_t	num;
	int			ct;

	num = umod_spec(spec.mod, ap);
	if ((ct = ft_u_s(num, 8, &spec)) < spec.prec)
		ct = spec.prec;
	else if ((spec.flags >> 4) & 1)
		;
	else if (ct < spec.width && spec.flags & 1 && spec.prec == -1)
		ct = spec.width;
	str = ft_base_8(num, spec.flags, ct);
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
