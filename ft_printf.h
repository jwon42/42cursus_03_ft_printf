/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:45:57 by jwon              #+#    #+#             */
/*   Updated: 2020/12/12 01:07:09 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define DEC "0123456789"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

typedef struct	s_info
{
	int			align;
	int			zero;
	int			width;
	int			dot;
	int			prec;
	int			spec;
	int			data_len;
	int			space_len;
	int			zero_len;
	int			printed_len;
}				t_info;

/*
** ft_printf.c
*/
void			init_info(t_info *info);
int				ft_printf(const char *str, ...);

/*
** parse.c
*/
void			parse_hub(va_list ap, char *str, t_info *info);

/*
** print.c
*/
void			print_hub(va_list ap, t_info *info);

/*
** utils.c
*/
void			ft_putchar(char c, t_info *info);
void			ft_putstr(char *s, t_info *info);
void			ft_putnbr_base(long long n, char *base, t_info *info);
int				ft_strlen(char *str, t_info *info);
int				ft_nbrlen_base(long long n, char *base, t_info *info);

#endif
