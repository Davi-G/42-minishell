/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/23 15:47:43 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	parser(char *str)
{
	char	**split;
	int		i;
	int		j;
	t_data	data;

	data.toke1 = NULL;
	data.toke2 = NULL;
	data.toke3 = NULL;
	split = ft_split(str, ' ');
	data.toke1 = split[0];
	i = 1;
	j = 0;
	if (split[1] != NULL && split[1][0] == '-')
	{
		data.toke2 = split[1];
		i = 2;
	}
	if (ft_strlen_array(split) > 1)
	{
		data.toke3 = malloc(sizeof(char *) * ft_strlen_array(split) - 1);
		while (split[i])
		{
			data.toke3[j] = split[i];
			i++;
			j++;
		}
	}
	i = 0;
	while (data.toke3[i])
	{
		printf("toke3 en posicion de i %i : %s\n", i, data.toke3[i]);
		i++;
	}
	return (data);
}
