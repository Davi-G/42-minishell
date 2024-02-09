/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:08:26 by dagomez           #+#    #+#             */
/*   Updated: 2022/05/05 12:56:26 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;
	size_t	i;

	i = (count * size);
	if (count != 0 && i / count != size)
		return (0);
	buffer = (void *)malloc(i);
	if (!buffer)
		return (0);
	ft_bzero(buffer, i);
	return (buffer);
}
