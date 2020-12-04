/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:46:07 by jwon              #+#    #+#             */
/*   Updated: 2020/12/04 16:48:31 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_space_sc(t_info *info)
{
	int		idx;
	int		len;

	idx = 0;
	if (info->zero && !info->align && !info->dot && !info->prec)
		return ;
	if (info->prec && info->prec < info->data_len)
		len = info->width - info->prec;
	else
		len = info->width - info->data_len;
	while (idx++ < len)
		ft_putchar(' ', info);
}

void		print_space_diuxp(t_info *info, long long data)
{
	int		idx;
	int		len;

	idx = data < 0 ? 1 : 0;
	if (info->zero && !info->dot && !info->prec)
		idx += info->width - info->data_len;
	if (info->spec == 'p')
		idx += 2;
	if (info->data_len < info->prec)
		len = info->width - info->prec;
	else
		len = info->width - info->data_len;
	while (idx++ < len)
		ft_putchar(' ', info);
}

void		print_zero(t_info *info, long long data)
{
	int		idx;
	int		len;

	idx = 0;
	len = 0;
	if (info->spec == 's' || info->spec == 'c' || info->spec == '%')
	{
		if (info->zero && !info->align)
			len = info->width - info->data_len;
	}
	else
	{
		if (info->zero && !info->dot && !info->prec)
		{
			idx = data < 0 ? 1 : 0;
			len = info->width - info->data_len;
		}
		else
			len = info->prec - info->data_len;
	}
	while (idx++ < len)
		ft_putchar('0', info);
}
