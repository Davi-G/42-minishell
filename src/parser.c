/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/22 14:21:33 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	parser(char *str)
{
	char **split;
	int i;
	int j;
	t_data	data;
	
	split = NULL;
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
	return (data);
}
	/* while (*split)
	{
		printf("%s\n", *split);
		split++;
	} */
