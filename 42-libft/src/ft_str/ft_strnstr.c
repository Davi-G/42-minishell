/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:13:08 by dagomez           #+#    #+#             */
/*   Updated: 2022/05/17 13:15:14 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *c, size_t len)
{
	size_t	nlen;

	if (c[0] == '\0')
		return ((char *)str);
	nlen = ft_strlen((char *)c);
	while (*str != '\0' && len-- >= nlen)
	{
		if (*str == *c && ft_memcmp(str, c, nlen) == 0)
			return ((char *)str);
		str++;
	}
	return (0);
}
