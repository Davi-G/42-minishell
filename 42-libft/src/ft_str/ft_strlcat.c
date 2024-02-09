/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:08:56 by dagomez           #+#    #+#             */
/*   Updated: 2022/05/03 16:53:16 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	m;
	size_t	c;

	i = 0;
	c = ft_strlen(src);
	m = ft_strlen(dest);
	while (src[i] && (m + i + 1 < size))
	{
		dest[m + i] = src[i];
		i++;
	}
	dest[m + i] = '\0';
	if (size > m)
		return (m + c);
	else
		return (c + size);
}
