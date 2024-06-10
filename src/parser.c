/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/06/10 18:16:34 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	ft_clean_toke(t_data *info)
{
	info->error = 0;
	info->toke1 = NULL;
	info->toke2 = NULL;
	info->toke3 = NULL;
	return *info;
}

static int search_quotes(char *str, int i)
{
	int quote;
	int open;

	open = 0;
	quote = 0;
	while (str[quote] && quote < i)
	{
		/* if (i > 0 && str[i - 1] == '\\')
			continue; */	
		if (open == 0 && str[quote] == '\"')
			open = 1;
		else if (open == 0 && str[quote] == '\'')
			open = 3;
		else if (open == 1 && str[quote] == '\"')
			open = 0;
		else if (open == 3 && str[quote] == '\'')
			open = 0;
		quote++;
	}
	return (open);
}

static void search_token(char *str, t_data *info, int pos, int tk)
{
	if (tk == 1)
		info->toke1 = str;
	else if (tk == 2)
		info->toke2 = str;
	else if (tk == 3)
		info->toke3[pos] = str;
	
}

static char quote_type(char *str)
{
	int i;
	char quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			return (quote);
		}
		i++;
	}
	return (quote);
}

static void	remove_quotes(char *str, t_data *info, int pos, int tk)
{
	char *aux;
	char quote;

	quote = quote_type(str);
	info->j = 0;
	info->x = 0;
	if (tk == 3)
		aux = calloc(ft_strlen(info->toke3[pos]), sizeof(char));
	else if (tk == 1)
		aux = calloc(ft_strlen(info->toke1), sizeof(char));
	else if (tk == 2)
		aux = calloc(ft_strlen(info->toke2), sizeof(char));
	while (info->j <= (int)ft_strlen(str))
	{
		if (quote == str[info->j])
			info->j++;
		if (str[info->j] == '\\')
			info->j++;
		aux[info->x++] = str[info->j];
		info->j++;
	}
	if ((str[info->j] == '\"' || str[info->j] == '\''))
		aux[info->x] = '\0';
	search_token(aux, info, pos, tk);
}

static void parse_2(t_data *info, char **split)
{
	int l;

	info->toke3 = NULL;
	info->toke3 = calloc(ft_strlen_array(split), sizeof(char *));
	while (info->i <= ft_strlen_array(split) - 1)
		info->toke3[info->j++] = split[info->i++];
	if (ft_strcmp(info->toke3[0], "..") == 0)
		return ;
	info->i = 0;
	l = 0;
	while (info->i <= ft_strlen_array(info->toke3))
	{
		if (info->toke3[info->i] == NULL)
			break ;
		l += search_quotes(info->toke3[info->i], 2147483647);
		if (l % 2 != 0 && info->toke3[info->i + 1] == NULL)
		{
			info->error = 1;
			return ;
		}
		remove_quotes(info->toke3[info->i], info, info->i, 3);
		info->i++;
	}
	return ;
}

t_data	parser(char *str)
{
	char	**split;
	t_data	data;

	data = ft_clean_toke(&data);
	split = ft_split(str, ' ');
	if (split[0] == NULL)
		return data;
	data.toke1 = split[0];
	if (search_quotes(split[0], 2147483647) != 0)
	{
		data.error = 1;
		return data;
	}
	else
		remove_quotes(data.toke1, &data, 0, 1);
	data.i = 1;
	data.j = 0;
	if (split[1] != NULL && split[1][0] == '-')
		data.toke2 = split[1];
	if (split[1] != NULL && split[1][0] == '-')
		data.i = 2;
	if (ft_strlen_array(split) > 1 && split[data.i] != NULL)
		parse_2(&data, split);
	return (data);
}
