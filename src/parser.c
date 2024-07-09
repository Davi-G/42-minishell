/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/09 12:25:18 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char*	remove_quotes(char *str, t_data *data)
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
	//signal(SIGINT, ctrl_c);
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
