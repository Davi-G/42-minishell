/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/06/26 17:54:59 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	ft_clean_toke(t_data *info)
{
	info->error = 0;
	info->quote = 0;
	return (*info);
}

int	is_ignore(char *str, int i)
{
	if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == ';')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '|')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '>')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '>'
		&& str[i + 2] && str[i + 2] == '>')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '<'
		&& str[i + 2] && str[i + 2] == '<')
		return (1);
	return (0);
}

static int	is_sep(char *str, int i, char quote)
{
	if (i > 0 && str[i - 1] == '\\' && ft_strchr("<>|;", str[i]))
		return (0);
	else if (ft_strchr("<>|;", str[i]) && quote == 0)
		return (1);
	else
		return (0);
}

static	char	*spaces(char *str, t_data *data, char *aux)
{
	if (str[data->i] == '$' && data->quote == 0 && str[data->i - 1] != '\\')
		aux[data->j++] = (char)(-str[data->i++]);
	else if (data->quote == 0 && is_sep(str, data->i, data->quote))
	{
		aux[data->j++] = ' ';
		aux[data->j++] = str[data->i++];
		if (data->quote == 0 && str[data->i] == '>')
			aux[data->j++] = str[data->i++];
		if (data->quote == 0 && str[data->i] == '<')
		aux[data->j++] = str[data->i++];
		aux[data->j++] = ' ';
	}
	return (aux);
}

static	char*	remove_quotes(char *str, t_data *data)
{
	char *aux;

	data->i = 0;
	data->j = 0;
	data->quote = 0;
	aux = calloc(ft_strlen(str), sizeof(char));
	while (str[data->i])
	{
		while (str[data->i] == '\"' || str[data->i] == '\'')
		{
			if (str[data->i] == data->quote)
			{
				data->quote = 0;
				data->i++;
			}
			else if (data->quote == 0)
				data->quote = str[data->i++];
			else
				break;
		}
		aux = spaces(str, data, aux);
		aux[data->j++] = str[data->i++];
	}
	aux[data->j] = '\0';
	return (free(str), aux);
}

void	argument_type(t_data *data, int	sep)
{
	if (ft_strcmp(data->toke, "") == 0)
		data->type = NONE;
	else if (ft_strcmp(data->toke, "|") == 0 && sep == 0)
		data->type = PIPE;
	else if (ft_strcmp(data->toke, ";") == 0 && sep == 0)
		data->type = END;
	else if (data->prev == NULL || data->prev->type >= PIPE)
		data->type = CMD;
	else
		data->type = ARG;
}

static	int	count_space(char *str, t_data *data)
{
	int	i;
	int	count;

	i = data->i;
	count = 0;
	while (str[i] != ' ' && str[i])
	{
		count++;
		if (str[i] == '\\')
			count--;
		i++;	
	}
	return (i - count);
}

t_data	*next_toke(t_data *data, char *str)
{
	t_data	*new;
	char	c;

	c = ' ';
	data->j = 0;
	new = malloc(sizeof(t_data));
	new->toke = calloc(count_space(str, data), sizeof(char));
	if (!new || !new->toke)
		return (NULL);
	while (str[data->i] && (str[data->i] != ' ' || c != ' '))
	{
		if (str[data->i] == '\\' && data->i++)
			new->toke[data->j++] = str[data->i++];
		else
			new->toke[data->j++] = str[data->i++];
	}
	return (new->toke[data->j] = '\0', new);
}

t_data	*set_toke(t_data *data, char *str)
{
	t_data	*next;
	t_data	*prev;
	int		sep;
	
	data->i = 0;
	next = NULL;
	prev = NULL;
	is_space(str, &data->i);
	while (str[data->i])
	{
		sep = is_ignore(str, data->i);
		next = next_toke(data, str);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		argument_type(data, sep);
		is_space(str, &data->i);
		ft_printf("prev: %s\n", prev->toke);
		ft_printf("toke: %s\n", next->toke);
		ft_printf("type: %d\n", data->type);
	}
	return (next);
}

t_data	parser(char *str)
{
	t_data	data;

	data = ft_clean_toke(&data);
	str = remove_quotes(str, &data);
	if (data.quote != 0)
		data.error = 1;
	set_toke(&data, str);
	ft_printf("str: %s\n", str);
	return (data);
}

//quote_type(str, &data);
/*
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
static void search_new(char *str, t_data *info, int pos, int tk)
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
	//search_new(aux, info, pos, tk);
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