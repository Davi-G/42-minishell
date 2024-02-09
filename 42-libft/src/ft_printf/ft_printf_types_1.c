/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 00:07:11 by dagomez           #+#    #+#             */
/*   Updated: 2022/06/28 19:40:40 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_d_r(int num, int i)
{
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (num < 0)
	{
		print_pf('-');
		i = type_d_r((num * -1), i);
	}
	else if (num >= 10)
	{
		i = type_d_r((num / 10), i);
		type_d_r((num % 10), i);
	}
	else
		print_pf(num + '0');
	return (i + 1);
}

int	type_u(int num)
{
	int	i;

	i = 0;
	i = type_u_r(num, i);
	return (i);
}

int	type_u_r(int num, int i)
{
	unsigned int	num_aux;

	num_aux = (unsigned int)num;
	if (num_aux == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (num_aux >= 10)
	{
		i = type_u_r((num_aux / 10), i);
		type_u_r((num_aux % 10), i);
	}
	else
		print_pf(num_aux + '0');
	return (i + 1);
}

int	type_x_r(int num, const char type, int i)
{
	unsigned int	num_aux;

	num_aux = num;
	if (num < 0)
		num_aux = (unsigned int)num;
	if (num_aux >= 16)
	{
		i = type_x_r(num_aux / 16, type, i);
		type_x_r(num_aux % 16, type, i);
	}
	else
	{
		if (num_aux <= 9)
			print_pf(num_aux + '0');
		else
		{
			if (type == 'x')
				print_pf(num_aux - 10 + 'a');
			if (type == 'X')
				print_pf(num_aux - 10 + 'A');
		}
	}
	return (i + 1);
}

int	type_x(int num, const char type)
{
	int	i;

	i = 0;
	i = type_x_r(num, type, i);
	return (i);
}
