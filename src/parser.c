/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/02/09 18:22:03 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *str)
{
	(void)str;
	t_data	data;
	
	data.splited = NULL;
	data.splited = ft_split(str, ' ');
	while (*data.splited)
	{
		printf("%s\n", *data.splited);
		data.splited++;
	}
}
