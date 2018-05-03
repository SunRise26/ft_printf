/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:14:02 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/25 21:11:35 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		var_par_ct(const char *str, int *i, t_spec *spec)
{
	int		res;
	int		sw;

	res = 0;
	sw = 0;
	while (str[*i] == '.' && --res && ++sw)
		(*i)++;
	if (str[*i] > 47 && str[*i] < 58 && ++((*spec).fl))
	{
		res = 0;
		while (str[*i] > 47 && str[*i] < 58)
			res = res * 10 + str[(*i)++] - 48;
		if (str[*i] == '$' && ++(*i))
			spec->dol = res;
		else if (sw > 0)
			spec->prec = res;
		else
			spec->width = res;
		(*i)--;
	}
	if (res < 0 && --(*i) && ++((*spec).fl))
		spec->prec = 0;
	return (res);
}

void	arg_dol(va_list ap, t_spec *spec)
{
	if (spec->dw)
	{
		while (--(spec->dw))
			va_arg(ap, void *);
		spec->width = ft_bonus_star2(ap, &((*spec).flags));
		if (!spec->dol)
			spec->dol = 1;
	}
	else if (spec->dp)
	{
		while (--(spec->dp))
			va_arg(ap, void *);
		spec->prec = (ft_bonus_star1(ap));
		if (!spec->dol)
			spec->dol = 1;
	}
	else if (spec->dol)
		while (--(spec->dol))
			va_arg(ap, void *);
}

int		numndol(const char *str, int *i, int *dol)
{
	int		j;
	int		res;

	res = 0;
	j = *i + 1;
	if (str[j] > 48 && str[j] < 58)
	{
		while (str[j] > 47 && str[j] < 58)
			res = res * 10 + str[j++] - 48;
		if (str[j] == '$')
		{
			(*i) = j;
			(*dol) = res;
			return (1);
		}
	}
	return (0);
}

char	*new_fs(char *s1, char *s2, int *prec, unsigned int flags)
{
	int		i;
	int		i1;
	char	*str;

	i = 0;
	i1 = 0;
	while (s1[i])
		i++;
	while (s2[i1])
		i1++;
	if (!((flags >> 1) & 1) && s2[i1 - 1] == '.' && --i1 == 0)
	{
		*prec = -1;
		s2[0] = '\0';
	}
	str = (char *)malloc(sizeof(char) * (i + i1 + 1));
	i1 = -1;
	while (s1[++i1])
		str[i1] = s1[i1];
	i1 = -1;
	while (s2[++i1])
		str[i++] = s2[i1];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_int_flagch(char *ret, unsigned int flags, int min)
{
	if (min == -1)
		ret[0] = '-';
	else if ((flags >> 3) & 1)
		ret[0] = '+';
	else if ((flags >> 2) & 1)
		ret[0] = ' ';
	return (ret);
}
