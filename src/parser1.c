/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:37:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 19:40:27 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_sep(char *str, int i, char quote)
{
	if (i > 0 && str[i - 1] == '\\' && ft_strchr("<>|;", str[i]))
		return (0);
	else if (ft_strchr("<>|;", str[i]) && quote == 0)
		return (1);
	else
		return (0);
}

char	*spaces(char *str, t_data *data, char *aux)
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

int	count_space(char *str, t_data *data)
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
