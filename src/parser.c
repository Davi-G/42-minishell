/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/27 21:32:04 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_clean_toke(t_data *info)
{
	info->error = 0;
	info->toke1 = NULL;
	info->toke2 = NULL;
	info->toke3 = NULL;
	return 0;
}

static int search_quotes(char **str, int i)
{
	int quote;
	int quote_1;
	int open;

	quote = -1;
	open = 0;
	while (str[quote++] && quote < i)
	{
		quote_1 = 0;
		while (str[quote][quote_1])
		{
			if (quote_1 > 0 && str[quote][quote_1 - 1] == '\\')
				;
			else if (open == 0 && str[quote][quote_1] == '\"')
				open = 1;
			else if (open == 0 && str[quote][quote_1] == '\'')
				open = 2;
			else if (open == 1 && str[quote][quote_1] == '\"')
				open = 0;
			else if (open == 2 && str[quote][quote_1] == '\'')
				open = 0;
			quote_1++;
	printf("open: %d\n", open);
		}
	}
	return (open);
}

static void	remove_quotes(t_data *info)
{
	int k;
	int l;
	char *aux;

	info->i = 0;
	k = 0;
	while (info->toke3[info->i])
	{
		aux = NULL;
		aux = malloc(sizeof(char) * (ft_strlen(info->toke3[info->i]) + 1));
		info->j = 0;
		l = 0;
		k = 0;
		while (info->toke3[info->i][info->j])
		{
			if (info->toke3[info->i][info->j] == '\"'
				|| info->toke3[info->i][info->j] == '\'')
				{
					l++;
					info->j++;
				}
			aux[k] = info->toke3[info->i][info->j];
			k++;
			info->j++;
		}
		if (l % 2 == 0 && l > 0)
			info->toke3[info->i] = aux;
		info->i++;
	}
}

static void parse_2(t_data *info, char **split)
{
	info->toke3 = malloc(sizeof(char *) * ft_strlen_array(split) - 1);
	while (split[info->i])
		info->toke3[info->j++] = split[info->i++];
	//printf("quotes: %d\n", search_quotes(info->toke3, 2147483647));
	if (ft_strcmp(info->toke3[0], "..") == 0)
		return ;
	else if (search_quotes(info->toke3, 2147483647) != 0)
	{
		info->error = 1;
		return ;
	}
	else if (search_quotes(info->toke3, 2147483647) == 0)
	{
		if (info->toke3[0][0] == '\"' || info->toke3[0][0] == '\'')
			remove_quotes(info);
	}
	else
		return ;
}

t_data	parser(char *str)
{
	char	**split;
	t_data	data;

	ft_clean_toke(&data);
	split = ft_split(str, ' ');
	if (split[0] == NULL)
		return data;
	data.toke1 = split[0];
	data.i = 1;
	data.j = 0;
	if (split[1] != NULL && split[1][0] == '-')
		data.toke2 = split[1];
	if (split[1] != NULL && split[1][0] == '-')
		data.i = 2;
	if (ft_strlen_array(split) > 1)
		parse_2(&data, split);
	return (data);
}
