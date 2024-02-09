/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:10:12 by dagomez           #+#    #+#             */
/*   Updated: 2022/05/17 15:40:58 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	k;
	char	*a;

	i = (size_t)start;
	k = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s);
	a = (char *)malloc((sizeof(char) * (len + 1)));
	if (!a)
		return (0);
	k = 0;
	while (k < len && s[i])
		a[k++] = s[i++];
	a[k] = 0;
	return (a);
}
