/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/25 18:21:17 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_clean_toke(t_data *info)
{
	info->toke1 = NULL;
	info->toke2 = NULL;
	info->toke3 = NULL;
	return 0;
}

static	int search_quotes(char *str, int i)
{
	int	quote;
	int double_quote;

	quote = 0;
	double_quote = 2;
	while ((str[i] == '\'' || str[i] == '\"') && str[i])
	{
		if (str[i] == '\'')
			quote++;
		if (str[i] == '\"')
			double_quote++;
		if (quote == 2 && str[i])
			return quote;
		if (double_quote == 4 && str[i])
			return double_quote;
		i++;
	}
	return (0);
}

t_data	parser(char *str)
{
	char	**split;
	int		i;
	int		j;
	t_data	data;

	ft_clean_toke(&data);
	split = ft_split(str, ' ');
	if (split[0] == NULL)
		return data;
	data.toke1 = split[0];
	i = 1;
	j = 0;
	if (split[1] != NULL && split[1][0] == '-')
		data.toke2 = split[1];
	if (split[1] != NULL && split[1][0] == '-')
		i = 2;
	if (ft_strlen_array(split) > 1)
	{
		data.toke3 = malloc(sizeof(char *) * ft_strlen_array(split) - 1);
		while (split[i])
		{
			search_quotes(split[i], 0);
			data.toke3[j++] = split[i++];
		}
	}
	return (data);
}
