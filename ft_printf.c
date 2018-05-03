/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 20:07:24 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/24 16:02:54 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	flags_search(const char *str, int *i, char *fl)
{
	unsigned int		flags;

	flags = 0;
	if (str[*i] == '0')
		flags = 1;
	else if (str[*i] == '#')
		flags = 2;
	else if (str[*i] == ' ')
		flags = 4;
	else if (str[*i] == '+')
		flags = 8;
	else if (str[*i] == '-')
		flags = 16;
	else if (str[*i] == '\'')
		flags = 32;
	if (flags)
		*fl = 1;
	return (flags);
}

unsigned int	mod_search(const char *str, int *i, char *fl)
{
	int		flags;

	flags = 0;
	if (str[*i] == 'L')
		flags = 1;
	else if (str[*i] == 'h' && str[*i + 1] != 'h')
		flags = 2;
	else if (str[*i] == 'h' && str[*i + 1] == 'h' && ++(*i))
		flags = 4;
	else if (str[*i] == 'l' && str[*i + 1] != 'l')
		flags = 8;
	else if (str[*i] == 'l' && str[*i + 1] == 'l' && ++(*i))
		flags = 16;
	else if (str[*i] == 'j')
		flags = 32;
	else if (str[*i] == 'z')
		flags = 64;
	else if (str[*i] == 't')
		flags = 128;
	if (flags)
		*fl = 1;
	return (flags);
}

int				var_par(const char *str, int *i, t_spec *spec, va_list ap)
{
	int		res;

	if (str[*i] == '*' && ++((*spec).fl))
	{
		if (numndol(str, i, &(*spec).dw))
			return (0);
		spec->width = ft_bonus_star2(ap, &((*spec).flags));
		return (0);
	}
	res = 0;
	while (str[*i] == '.' && --res)
		if (str[++(*i)] == '*' && ++((*spec).fl))
		{
			if (numndol(str, i, &(*spec).dp))
				return (0);
			res = 0;
			spec->prec = (ft_bonus_star1(ap));
		}
	if (res < 0 && --(*i) && ++((*spec).fl))
		spec->prec = 0;
	return (0);
}

t_spec			var_format(const char *str, int *i, va_list ap, int strlen)
{
	t_spec			spec;

	spec_nul(&spec, strlen);
	while (spec.fl > 0 && str[++(*i)])
	{
		spec.fl = 0;
		spec.flags |= flags_search(str, i, &spec.fl);
		if (spec.fl == 0)
			var_par_ct(str, i, &spec);
		var_par(str, i, &spec, ap);
		spec.mod |= mod_search(str, i, &spec.fl);
	}
	if (!str[*i])
		return (spec);
	if (str[*i] == 'D' || str[*i] == 'O' || str[*i] == 'U')
		spec.mod |= 8;
	return (spec);
}

int				ft_printf(const char *str, ...)
{
	va_list	ap;
	t_spec	spec;
	int		res;
	int		i;

	res = 0;
	i = 0;
	va_start(ap, str);
	while (str[i])
		if (str[i] != '%')
			res += ar1_out(&i, str);
		else if (str[i])
		{
			spec = var_format(str, &i, ap, res);
			while (spec.dol || spec.dw || spec.dp)
			{
				va_end(ap);
				va_start(ap, str);
				arg_dol(ap, &spec);
			}
			if (str[i])
				res += spec_ch(str[i], ap, &spec, &i);
		}
	va_end(ap);
	return (res);
}
