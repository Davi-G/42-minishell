/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/03/13 17:48:24 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	parser(char *str)
{
	char **split;
	t_data	data;
	
	split = NULL;
	data.toke1 = NULL;
	data.toke2 = NULL;
	data.toke3 = NULL;
	split = ft_split(str, ' ');
	data.toke1 = split[0];
	data.toke2 = split[1];
	data.toke3 = split[2];	
/* 	while (*split)
	{
		printf("%s\n", *split);
		split++;
	} */
	return (data);
}
