/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:06:52 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/28 20:59:49 by dagomez          ###   ########.fr       */
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

static int search_quotes(char *str, int i)
{
	int quote;
	int open;

	open = 0;
	quote = 0;
	while (str[quote] && quote < i)
	{
		if (quote > 0 && str[quote - 1] == '\\')
			;
		else if (open == 0 && str[quote] == '\"')
			open = 1;
		else if (open == 0 && str[quote] == '\'')
			open = 2;
		else if (open == 1 && str[quote] == '\"')
			open = 0;
		else if (open == 2 && str[quote] == '\'')
			open = 0;
		quote++;
	}
	return (open);
}

static void	remove_quotes(char *str, t_data *info, int pos, int tk)
{
	int k;
	char *aux;

	info->i = 0;
	k = 0;
	if (tk == 3)
		aux = malloc(sizeof(char) * (ft_strlen(info->toke3[info->i]) + 1));
	if (tk == 1)
		aux = malloc(sizeof(char) * (ft_strlen(info->toke1) + 1));
	if (tk == 2)
		aux = malloc(sizeof(char) * (ft_strlen(info->toke2) + 1));
	//printf("aux[%d] = %c\n", k, str[k]);
	while (str[info->i])
	{
		info->j = 0;
		if ((str[info->i] == '\"' || str[info->i] == '\''))
			info->i++;
		aux[k++] = str[info->i];
		//printf("aux[%d] = %c\n", k, str[k]);
		info->i++;
	}
	if ((str[info->i] == '\"' || str[info->i] == '\''))
		aux[k] = '\0';
	if (tk == 1)
		info->toke1 = aux;
	if (tk == 2)
		info->toke2 = aux;
	if (tk == 3)
		info->toke3[pos] = aux;
}

static void parse_2(t_data *info, char **split)
{
	int l;

	l = 0;
	info->toke3 = NULL;
	info->toke3 = malloc(sizeof(char *) * ft_strlen_array(split) - 1);
	while (split[info->i])
		info->toke3[info->j++] = split[info->i++];
	if (ft_strcmp(info->toke3[0], "..") == 0)
		return ;
	info->i = 0;
	printf("len = %d\n", ft_strlen_array(info->toke3));
	while (info->i <= ft_strlen_array(info->toke3))
	{
		write(1, "HERE\n", 5);
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

	ft_clean_toke(&data);
	split = ft_split(str, ' ');
	if (split[0] == NULL)
		return data;
	data.toke1 = split[0];
	if (search_quotes(data.toke1, 2147483647) != 0)
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
