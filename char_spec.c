/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:36:58 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/21 19:58:19 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strncp(char *s, int prec)
{
	int		i;
	char	*res;

	if (!s)
		return (ft_strncp("(null)", prec));
	i = 0;
	while (s[i] && i != prec)
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (s[++i] && i != prec)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

void	str_width_end(char *res, char *str, int j, char sp)
{
	int		i;
	int		i1;

	i = -1;
	i1 = -1;
	while (++i < j)
		res[i] = sp;
	while (str[++i1])
		res[i++] = str[i1];
	res[i] = '\0';
}

char	*str_width(char *str, int flags, int width)
{
	char	*res;
	char	sp;
	int		i;

	i = 0;
	sp = ' ';
	if (flags & 1)
		sp = '0';
	while (str[i])
		i++;
	if (i > width)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (width + 1));
	if (!((flags >> 4) & 1))
		str_width_end(res, str, width - i, sp);
	else
	{
		i = -1;
		while (str[++i])
			res[i] = str[i];
		while (i < width)
			res[i++] = 32;
		res[i] = '\0';
	}
	return (res);
}

int		spec_s(t_spec spec, va_list ap)
{
	int		res;
	char	*buf;
	char	*s;

	s = ft_strncp(va_arg(ap, char *), spec.prec);
	buf = str_width(s, spec.flags, spec.width);
	if (buf)
	{
		free(s);
		s = buf;
	}
	res = 0;
	while (s[res])
		write(1, &s[res++], 1);
	free(s);
	return (res);
}
