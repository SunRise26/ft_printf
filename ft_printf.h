/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 18:30:57 by vveselov          #+#    #+#             */
/*   Updated: 2018/01/25 21:32:47 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF_H
# define __FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>

typedef struct	s_spec
{
	int				flags;
	int				width;
	int				prec;
	int				mod;
	int				len;
	char			fl;
	int				dol;
	int				dw;
	int				dp;
	int				strlen;
}				t_spec;

int				ft_printf(const char *str, ...);
int				spec_ch(const char c, va_list ap, t_spec *spec, int *i);
char			*ft_strncp(char *s, int prec);
int				ft_u_s(uintmax_t n, int oux, t_spec *spec);
void			str_width_end(char *res, char *str, int j, char sp);
char			*str_width(char *str, int flags, int width);
char			*ft_itoa_intmax(intmax_t n, int ct, unsigned int flags);
char			*ft_base_8(uintmax_t n, int flags, int ct);
char			*ft_base_16(uintmax_t n, int flags, int ct, char c);
char			*w_char_to_str(unsigned int *s, int prec);
uintmax_t		umod_spec(int mod, va_list ap);
int				spec_s(t_spec spec, va_list ap);
int				spec_ls(t_spec spec, va_list ap);
int				spec_di(t_spec spec, va_list ap);
int				spec_oux(t_spec spec, va_list ap);
int				spec_p(t_spec spec, va_list ap);
int				spec_c(t_spec spec, va_list ap);
int				spec_lc(t_spec spec, va_list ap);
int				spec_x(t_spec spec, va_list ap, char c);
int				spec_u(t_spec spec, va_list ap);
int				spec_rest(t_spec spec, char c);
char			*null_line(void);
int				ft_bonus_star1(va_list ap);
int				ft_bonus_star2(va_list ap, int *f);
int				ft_prfout(char *s, int zero);
int				ar1_out(int *i, const char *str);
void			spec_nul(t_spec *spec, int slen);
int				var_par_ct(const char *str, int *i, t_spec *spec);
void			arg_dol(va_list ap, t_spec *spec);
int				spec_b(t_spec spec, va_list ap);
unsigned int	flags_search(const char *str, int *i, char *fl);
unsigned int	mod_search(const char *str, int *i, char *fl);
int				var_par(const char *str, int *i, t_spec *spec, va_list ap);
int				numndol(const char *str, int *i, int *dol);
int				spec_n(t_spec spec, va_list ap);
int				spec_f(t_spec spec, va_list ap);
int				flags_ch0(unsigned int flags, intmax_t num);
int				ft_num_size(intmax_t num, int prec, unsigned int flags);
char			*new_fs(char *s1, char *s2, int *prec, unsigned int flags);
void			ft_apos(char *str);
char			*ft_int_flagch(char *ret, unsigned int flags, int min);

#endif
