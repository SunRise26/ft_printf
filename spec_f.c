/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:09:26 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/26 16:43:15 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_f_itoa_intmax(intmax_t n, int ct, unsigned int flags, char *ret)
{
	int			min;
	int			apos;

	apos = -1;
	min = 1;
	if (n < 0)
		min = -1;
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

int			spec_f_out(t_spec spec, intmax_t num, int *ct, char *fnum)
{
	char	*str;
	char	*buf;
	int		nct;

	nct = ct[0] + ct[1];
	if (num < 0 || ((spec.flags >> 3) & 1) || ((spec.flags >> 2) & 1))
		ct[0] += 1;
	str = (char *)malloc(sizeof(char) * (nct + 1));
	str = ft_f_itoa_intmax(num, ct[0], spec.flags, str);
	str = new_fs(str, fnum, &spec.prec, spec.flags);
	if ((buf = str_width(str, spec.flags, spec.width + spec.prec + 1)))
	{
		free(str);
		str = buf;
	}
	ct[1] = 0;
	while (fnum[(ct[1])])
		(ct[1])++;
	if (fnum[(ct[1]) - 1] == '.')
		fnum[(ct[1]) - 1] = '\0';
	ct[0] = ft_prfout(str, 0);
	free(str);
	free(fnum);
	return (ct[0]);
}

void		fnum_round(char *ret, int j, intmax_t *num, int z)
{
	int		sw;
	int		n;

	n = j - 1;
	sw = 0;
	while (--j > 0)
	{
		if (sw || (ret[j] > '4' && ret[j] <= '9'))
		{
			sw = 0;
			if (ret[j - 1] == '9' && ++sw)
				ret[j - 1] = '0';
			else if (ret[j - 1] >= '0' && ret[j - 1] < '9')
			{
				ret[j - 1]++;
				break ;
			}
		}
		if (sw > 0 && j == 2)
			*num += 1;
	}
	while (--z > -2)
		ret[n - (z + 1)] = '\0';
}

char		*ft_fnum(double n, intmax_t *num, int ct)
{
	intmax_t	i;
	char		*ret;
	int			j;
	int			z;
	int			min;

	if ((min = 1) && n < 0)
		min = -1;
	z = 0;
	if (ct == 1 && ++z)
		ct++;
	ret = (char *)malloc(sizeof(char) * (++ct + 1));
	j = 0;
	n = n - (double)(*num);
	ret[0] = '.';
	ret[ct] = '\0';
	while (--ct)
	{
		n *= 10;
		i = (int)n;
		ret[++j] = i * min + 48;
		n = n - (double)i;
	}
	fnum_round(ret, j + 1, num, z);
	return (ret);
}

int			spec_f(t_spec spec, va_list ap)
{
	int			ct[2];
	double		n;
	intmax_t	num;
	char		*fnum;

	ct[1] = 7;
	n = va_arg(ap, double);
	num = (intmax_t)n;
	if (spec.prec != -1)
		ct[1] = spec.prec + 1;
	else
		spec.prec = 7;
	fnum = ft_fnum(n, &num, ct[1]);
	ct[0] = ft_num_size(num, spec.prec, spec.flags);
	if (spec.prec > 0)
		spec.width -= (spec.prec + 1);
	else if (spec.prec == 0)
		;
	else
		spec.width -= 7;
	if ((spec.flags >> 4) & 1)
		;
	else if (ct[0] < spec.width && (spec.flags & 1))
		ct[0] = spec.width - flags_ch0(spec.flags, num);
	return (spec_f_out(spec, num, ct, fnum));
}
