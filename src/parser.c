/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 16:56:48 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_toke(t_data *data)
{
	t_data	*aux;

	while (data)
	{
		aux = data->next;
		free(data->toke);
	//	free(data);
		data = aux;
	}
}

static t_data	ft_clean_toke(t_master *info_shell, t_data *data)
{
	if (data->toke)
		del_toke(data);
	info_shell->error = 0;
	data->quote = 0;
	return (*data);
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
	if (str[data->i] == '$' && data->quote == '\"')
	{
		aux[data->j++] = (char)-str[data->i++];
		if (str[data->x] == '\"')
		{
			data->x++;
			data->quote = 0;
		}
	}
	else if (str[data->i] == '$' && data->quote == 0 && str[data->i - 1] != '\\')
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
	data->x++;
	return (aux);
}

static	char*	remove_quotes(char *str, t_data *data)
{
	char *aux;

	data->i = 0;
	data->j = 0;
	data->quote = 0;
	aux = calloc(ft_strlen(str) + 10, sizeof(char));
	while (str[data->i])
	{
		while (str[data->x] == '\"' || str[data->x] == '\'')
		{
			if (data->quote == 0)
				data->quote = str[data->x++];
			else if (str[data->x] == data->quote)
			{
				data->quote = 0;
				data->x++;
			}
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
	else if (ft_strcmp(data->toke, ">") == 0 && sep == 0)
		data->type = TRUNC;
	else if (ft_strcmp(data->toke, ">>") == 0 && sep == 0)
		data->type = APPEND;
	else if (ft_strcmp(data->toke, "<") == 0 && sep == 0)
		data->type = INPUT;
	else if (ft_strcmp(data->toke, "<<") == 0 && sep == 0)
		data->type = HEREDOC;
	else if (ft_strcmp(data->toke, "|") == 0 && sep == 0)
		data->type = PIPE;
	else if (ft_strcmp(data->toke, ";") == 0 && sep == 0)
		data->type = END;
	else if (data->prev == NULL || data->prev->type >= TRUNC)
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
		if (c == ' ' && (str[data->i] == '\'' || str[data->i] == '\"'))
			c = str[data->i++];
		else if (c != ' ' && str[data->i] == c)
		{
			c = ' ';
			data->i++;
		}
		else if (str[data->i] == '\\' && data->i++)
			new->toke[data->j++] = str[data->i++];
		else
			new->toke[data->j++] = str[data->i++];
	}
	new->toke[data->j] = '\0';
	return (new);
}

t_data	set_toke(t_data *data, char *str)
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
		argument_type(next, sep);
		is_space(str, &data->i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (*next);
}

t_data	parser(char *str, t_master *info_shell)
{
	t_data	data;
	char 	quote;

	data = ft_clean_toke(info_shell, &data);
	is_space(str, &data.i);
	if (str[data.i] == '\0')
		return (data);
	data.x = -1;
	str = remove_quotes(str, &data);
	quote = data.quote;
	data = set_toke(&data, str);
	data.quote = quote;
	if (data.quote != 0)
		info_shell->error = 1;
	//print_tokens(&data);
	return (data);
}

void	print_tokens(t_data *data)
{
	t_data	*aux;

	aux = data;
	while (aux)
	{
		ft_printf("toke: %s\n", aux->toke);
		ft_printf("type: %d\n", aux->type);
		aux = aux->next;
	}
}
