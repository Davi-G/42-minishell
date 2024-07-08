/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:12:39 by davi-g            #+#    #+#             */
/*   Updated: 2024/06/26 17:27:37 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	is_numeric(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

int	ft_strlen_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_strlen_array_full(char **array)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
			j++;
		k += j;
		i++;
	}
	return (i + k - 1);
}

void	is_space(char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
			|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}