/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:30:48 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/23 20:21:34 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			spec_n(t_spec spec, va_list ap)
{
	intmax_t	*len;

	len = va_arg(ap, void *);
	*len = spec.strlen;
	return (0);
}
