/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/06/20 22:14:09 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	ft_clean_toke(t_data *info)
{
	info->error = 0;
	info->quote = 0;
	info->toke1 = NULL;
	info->toke2 = NULL;
	info->toke3 = NULL;
	return *info;
}

static int search_quotes(char *str, char type)
{
	int i;
	int open;

	open = 0;
	i = 0;
	while (str[i])
		if (str[i++] == type)
			open++;
	return (open);
}

static int count_quotes(char *str)
{
	int i;
	int quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			quote++;
		i++;
	}
	return (quote);
}

static void quote_type(char *str, t_data *data)
{
	int i;
	int k;
	char *quote;
	
	quote = calloc(count_quotes(str), sizeof(char));
	quote[0] = 0;
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote[k] = str[i];
			k++;
		}
		i++;
	}
	data->q_d = search_quotes(str, '\"');
	data->q_s = search_quotes(str, '\'');
	data->quote = ft_strdup(quote);
	free(quote);
}

static	char	first_quote(char *str)
{
	int i;
	int j;
	//int k;
	char quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			break ;
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			quote = str[i];
			j++;
			if (j == 2)
				break ;
		}
		i++;
	}
	return (quote);
}

static	void	remove_quotes(char *str, t_data *data)
{
	int i;
	int j;
	//int k;
	char *aux;

	i = 0;
	j = 0;
//	k = 0;
	(void)data;
	aux = calloc(ft_strlen(str), sizeof(char));
	while (str[i])
	{
		if (str[i] == first_quote(str))
			i++;
		aux[j] = str[i];
		j++;
		i++;
	}
	aux[j] = '\0';
}

t_data	parser(char *str)
{
	t_data	data;
	char	**split_dot;
	char	**split_pipe;
	char	**split;

	split_dot = ft_split(str, ';');
	data.i = 0;
	while (split_dot[data.i])
		ft_printf("dot: %s\n", split_dot[data.i++]);
	(void)split_pipe;
	(void)split;
	data.i = 0;
	data = ft_clean_toke(&data);
	quote_type(str, &data);
	ft_printf("data.quote: %s\n", data.quote);
	ft_printf("data.q_d: %d\n", data.q_d);
	ft_printf("data.q_s: %d\n", data.q_s);
	remove_quotes(str, &data);
	return (data);
}


/* static void search_token(char *str, t_data *info, int pos, int tk)
{
	if (tk == 1)
		info->toke1 = str;
	else if (tk == 2)
		info->toke2 = str;
	else if (tk == 3)
		info->toke3[pos] = str;
	return ;
} */

/* static char	*remove_quotes(char *str, t_data *info, int pos, int tk)
{
	char *aux;
	char quote;

	quote = info->quote[0];
	info->j = 0;
	info->x = 0;
	(void)pos;
	(void)tk;
	aux = calloc(ft_strlen(str), sizeof(char));
 	if (tk == 3)
		aux = calloc(ft_strlen(info->toke3[pos]), sizeof(char));
	else if (tk == 1)
		aux = calloc(ft_strlen(info->toke1), sizeof(char));
	else if (tk == 2)
		aux = calloc(ft_strlen(info->toke2), sizeof(char));
	while (info->j < (int)ft_strlen(str))
	{
		if (quote == str[info->j])
			info->j++;
		aux[info->x++] = str[info->j];
		info->j++;
	}
	if ((str[info->j] == '\"' || str[info->j] == '\''))
		aux[info->x] = '\0';
	aux[info->x++] = '\0';
	return (aux);
	//search_token(aux, info, pos, tk);
} */


/* 
static void parse_2(t_data *info, char **split)
{
	int l;

	info->j = 0;
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
		l += search_quotes(info->toke3[info->i], 2147483647, info);
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
	if (search_quotes(split[0], 2147483647, &data) != 0)
	{
		data.error = 1;
		return data;
	}
	else
		remove_quotes(data.toke1, &data, 0, 1);
	data.quote = 0;
	data.i = 1;
	if (split[1] != NULL && split[1][0] == '-')
		data.toke2 = ft_strdup(split[1]);
	if (split[1] != NULL && split[1][0] == '-')
		data.i = 2;
	if (ft_strlen_array(split) > 1 && split[data.i] != NULL)
		parse_2(&data, split);
	free_array(split);
	return (data);
}
*/