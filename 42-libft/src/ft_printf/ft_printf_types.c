/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:54:10 by dagomez           #+#    #+#             */
/*   Updated: 2022/06/28 19:39:46 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_c(char c)
{
	print_pf(c);
	return (1);
}

int	type_s(char *s)
{
	return (ft_putstr_pf(s));
}

int	type_p_r(unsigned long long num, int i)
{
	if (num >= 16)
		i = type_p_r(num / 16, i);
	write(1, &"0123456789abcdef"[num % 16], 1);
	return (i + 1);
}

int	type_p(unsigned long long num)
{
	int	i;

	i = 2;
	write(1, "0x", 2);
	i = type_p_r(num, i);
	return (i);
}

int	type_d(int num)
{
	int	i;

	i = 0;
	i = type_d_r(num, i);
	return (i);
}
