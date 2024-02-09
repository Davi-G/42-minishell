/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:33:45 by dagomez           #+#    #+#             */
/*   Updated: 2022/06/27 19:29:17 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void	*buffer;
	size_t	i;

	i = (count * size);
	if (count != 0 && i / count != size)
		return (0);
	buffer = (void *)malloc(i);
	if (!buffer)
		return (0);
	ft_bzero_gnl(buffer, i);
	return (buffer);
}

void	ft_bzero_gnl(void *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((char *)s)[i++] = 0;
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*rs;

	j = 0;
	if (!s2 || !s1)
		return (0);
	i = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	rs = malloc(sizeof(char) * i);
	if (!rs)
		return (0);
	i = 0;
	while (s1[j])
	{
		rs[j] = s1[j];
		j++;
	}
	while (s2[i])
		rs[j++] = s2[i++];
	rs[j++] = 0;
	return (rs);
}

char	*ft_strchr_gnl(const char *src, int c)
{
	int	i;

	i = 0;
	while (src[i] != c && src[i] != 0)
		i++;
	if (src[i] == c)
		return (&((char *)src)[i]);
	else
		return (0);
}
