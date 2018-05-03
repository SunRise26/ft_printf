/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 21:55:52 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/21 20:35:35 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		wchar_len(unsigned int num)
{
	int				active_bits;

	active_bits = 0;
	if (num < 128)
		return (1);
	while (num && ++active_bits)
		num /= 2;
	if (active_bits < 12)
		return (2);
	else if (active_bits > 11 && active_bits < 17)
		return (3);
	else
		return (4);
	return (0);
}

void	unicode_msk(unsigned char *res, int *i, unsigned int s, int size)
{
	unsigned char	bits;

	bits = ((s >> (6 * size)) << (26 + size)) >> (26 + size);
	if (size == 3)
		res[(*i)++] = 240 | bits;
	else if (size == 2)
		res[(*i)++] = 224 | bits;
	else if (size == 1)
		res[(*i)++] = 192 | bits;
	while (--size != -1)
	{
		bits = ((s >> (6 * size)) << 26) >> 26;
		res[(*i)++] = 128 | bits;
	}
	(*i)--;
}

char	*chr_create(unsigned int *s, int len)
{
	char	*res;
	int		size;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * (len + 1));
	i = -1;
	j = -1;
	while (++i < len)
	{
		size = wchar_len(s[++j]);
		if (size == 1)
			res[i] = (char)s[j];
		else if (size > 1)
			unicode_msk((unsigned char *)res, &i, s[j], size - 1);
	}
	res[len] = '\0';
	return (res);
}

char	*w_char_to_str(unsigned int *s, int prec)
{
	char	*res;
	int		i;
	int		len;
	int		j;

	if (!s)
		return (ft_strncp("(null)", prec));
	i = -1;
	len = 0;
	while (s[++i])
	{
		j = wchar_len(s[i]);
		if (len + j <= prec || prec == -1)
			len += j;
		else
			break ;
	}
	res = chr_create(s, len);
	return (res);
}

int		spec_ls(t_spec spec, va_list ap)
{
	int				res;
	char			*str;
	char			*buf;

	str = w_char_to_str(va_arg(ap, unsigned int *), spec.prec);
	buf = str_width(str, spec.flags, spec.width);
	if (buf)
	{
		free(str);
		str = buf;
	}
	res = ft_prfout(str, 0);
	free(str);
	return (res);
}
