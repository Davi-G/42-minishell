/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:54:22 by dagomez           #+#    #+#             */
/*   Updated: 2022/05/17 15:47:33 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if ((unsigned char)c == src[i])
			return (&((char *)src)[i]);
		i++;
	}
	if (src[i] == (unsigned char)c)
		return (&((char *)src)[i]);
	else
		return (0);
}
