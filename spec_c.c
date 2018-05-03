/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:39:23 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/21 20:36:23 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		spec_c(t_spec spec, va_list ap)
{
	int		res;
	char	*buf;
	char	*s;
	char	c1[2];

	c1[0] = (char)va_arg(ap, int8_t *);
	c1[1] = '\0';
	s = ft_strncp(c1, -1);
	if ((buf = str_width(s, spec.flags, spec.width - (c1[0] == '\0'))))
	{
		free(s);
		s = buf;
	}
	res = ft_prfout(s, (*c1 == '\0') + (*c1 == '\0' && (spec.flags >> 4) & 1));
	free(s);
	return (res);
}

int		spec_lc(t_spec spec, va_list ap)
{
	int				res;
	char			*str;
	char			*buf;
	unsigned int	wc[2];

	if (MB_CUR_MAX == 1)
		return (spec_c(spec, ap));
	wc[0] = va_arg(ap, unsigned int);
	wc[1] = 0;
	str = w_char_to_str(wc, -1);
	buf = str_width(str, spec.flags, spec.width);
	if (buf)
	{
		free(str);
		str = buf;
	}
	res = ft_prfout(str, (*wc == 0) + (*wc == 0 && (spec.flags >> 4) & 1));
	free(str);
	return (res);
}

int		spec_rest(t_spec spec, char c)
{
	int		res;
	char	*buf;
	char	*s;
	char	c1[2];

	c1[0] = c;
	s = ft_strncp(c1, -1);
	if ((buf = str_width(s, spec.flags, spec.width)))
	{
		free(s);
		s = buf;
	}
	res = ft_prfout(s, 0);
	free(s);
	return (res);
}
