/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:11:19 by dagomez           #+#    #+#             */
/*   Updated: 2022/06/28 19:48:30 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_type(char type, va_list ptr)
{
	if (type == 'c')
		return (type_c(va_arg(ptr, int)));
	if (type == 's')
		return (type_s(va_arg(ptr, char *)));
	if (type == 'p')
		return (type_p(va_arg(ptr, unsigned long long)));
	if (type == 'd' || type == 'i')
		return (type_d(va_arg(ptr, int)));
	if (type == 'u')
		return (type_u(va_arg(ptr, int)));
	if (type == 'x' || type == 'X')
		return (type_x(va_arg(ptr, int), type));
	if (type == '%')
		return (type_c('%'));
	return (0);
}

int	ft_printf(char const *src, ...)
{
	int		i;
	int		totalcount;
	va_list	ptr;

	va_start(ptr, src);
	i = 0;
	totalcount = 0;
	while (src[i])
	{
		if (src[i] == '%')
		{
			i++;
			totalcount += print_type(src[i], ptr);
		}
		else
		{
			print_pf(src[i]);
			totalcount++;
		}
		i++;
	}
	va_end(ptr);
	return (totalcount);
}
