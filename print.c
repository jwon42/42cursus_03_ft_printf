/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:46:01 by jwon              #+#    #+#             */
/*   Updated: 2020/12/11 18:30:34 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_space(t_info *info, long long data)
{
	if (info->spec == 's' || info->spec == 'c' || info->spec == '%')
	{
		if (info->zero && !info->align && !info->dot && !info->prec)
			return ;
		if (info->prec && info->prec < info->data_len)
			info->space_len = info->width - info->prec;
		else
			info->space_len = info->width - info->data_len;
	}
	else
	{
		if (info->data_len < info->prec)
			info->space_len = info->width - info->prec;
		else
			info->space_len = info->width - info->data_len;
		data < 0 ? info->space_len-- : 0;
		info->spec == 'p' ? info->space_len -= 2 : 0;
		if (info->zero && !info->dot && !info->prec)
			info->space_len -= info->width - info->data_len;
	}
	while (info->space_len-- > 0)
		ft_putchar(' ', info);
}

static void		print_zero(t_info *info, long long data)
{
	if (info->spec == 's' || info->spec == 'c' || info->spec == '%')
	{
		if (info->zero && !info->align)
			info->zero_len = info->width - info->data_len;
	}
	else
	{
		if (info->zero && !info->dot && !info->prec)
		{
			info->zero_len = info->width - info->data_len;
			data < 0 ? info->zero_len-- : 0;
		}
		else
			info->zero_len = info->prec - info->data_len;
	}
	while (info->zero_len-- > 0)
		ft_putchar('0', info);
}

static void		print_diuxp(va_list ap, t_info *info)
{
	char			*base;
	long long		data;

	if (info->spec == 'd' || info->spec == 'i')
		data = va_arg(ap, int);
	else if (info->spec == 'u' || info->spec == 'x' || info->spec == 'X')
		data = va_arg(ap, unsigned int);
	else
		data = va_arg(ap, unsigned long);
	if (info->spec == 'd' || info->spec == 'i' || info->spec == 'u')
		base = DEC;
	else if (info->spec == 'X')
		base = HEX_UPPER;
	else
		base = HEX_LOWER;
	info->data_len = data < 0 ? ft_nbrlen_base(-1 * data, base, info)
		: ft_nbrlen_base(data, base, info);
	info->align == 0 ? print_space(info, data) : 0;
	data < 0 ? ft_putchar('-', info) : 0;
	info->spec == 'p' ? ft_putstr("0x", info) : 0;
	print_zero(info, data);
	data < 0 ? ft_putnbr_base(-1 * data, base, info)
		: ft_putnbr_base(data, base, info);
	info->align == 1 ? print_space(info, data) : 0;
}

static void		print_sc(va_list ap, t_info *info)
{
	char			*data_s;
	int				data_c;

	data_s = 0;
	data_c = 0;
	if (info->spec == 's')
		data_s = va_arg(ap, char *);
	else if (info->spec == 'c')
		data_c = va_arg(ap, int);
	else
		data_c = '%';
	data_s = (data_s == NULL) ? "(null)" : data_s;
	info->data_len = (info->spec == 's') ? ft_strlen(data_s, info) : 1;
	info->align == 0 ? print_space(info, 0) : 0;
	print_zero(info, 0);
	info->spec == 's' ? ft_putstr(data_s, info) : ft_putchar(data_c, info);
	info->align == 1 ? print_space(info, 0) : 0;
}

void			print_hub(va_list ap, t_info *info)
{
	if (info->spec == 'd' || info->spec == 'i' || info->spec == 'u' ||
		info->spec == 'x' || info->spec == 'X' || info->spec == 'p')
		print_diuxp(ap, info);
	else if (info->spec == 's' || info->spec == 'c' || info->spec == '%')
		print_sc(ap, info);
}
