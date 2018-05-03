/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 21:43:37 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/24 20:48:33 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		spec_ch1(const char c, va_list ap, t_spec *spec, int *i)
{
	if (c == 'n' && ++(*i))
		return (spec_n(*spec, ap));
	else if ((c == 'f' || c == 'F') && ++(*i))
		return (spec_f(*spec, ap));
	else if (++(*i))
		return (spec_rest(*spec, c));
	return (0);
}

int		spec_ch(const char c, va_list ap, t_spec *spec, int *i)
{
	if ((((((*spec).mod >> 3) & 1) && c == 'c') || c == 'C') && ++(*i))
		return (spec_lc(*spec, ap));
	else if (c == 'c' && ++(*i))
		return (spec_c(*spec, ap));
	else if ((((((*spec).mod >> 3) & 1) && c == 's') || c == 'S') && ++(*i))
		return (spec_ls(*spec, ap));
	else if (c == 's' && ++(*i))
		return (spec_s(*spec, ap));
	else if ((c == 'd' || c == 'i' || c == 'D') && ++(*i))
		return (spec_di(*spec, ap));
	else if ((c == 'u' || c == 'U') && ++(*i))
		return (spec_u(*spec, ap));
	else if ((c == 'o' || c == 'O') && ++(*i))
		return (spec_oux(*spec, ap));
	else if ((c == 'x' || c == 'X') && ++(*i))
		return (spec_x(*spec, ap, c));
	else if (c == 'p' && ++(*i))
	{
		(*spec).flags |= 2;
		return (spec_p(*spec, ap));
	}
	else if (c == 'b' && ++(*i))
		return (spec_b(*spec, ap));
	return (spec_ch1(c, ap, spec, i));
}
