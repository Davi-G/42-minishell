/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:18:04 by dagomez           #+#    #+#             */
/*   Updated: 2024/07/09 16:20:54 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_finder(char *old_pwd, char *home)
{
	int		i;
	int		j;

	i = 0;
	home = NULL;
	while (old_pwd[i])
		i++;
	j = i;
	while (old_pwd[i] != '/')
		i--;
	i++;
	home = malloc(sizeof(char) * (j - i));
	j = 0;
	while (old_pwd[i])
	{
		home[j] = old_pwd[i];
		i++;
		j++;
	}
	home[j] = '/';
	home[j + 1] = '\0';
	return (home);
}

void	free_all(t_master *info_shell, t_data *data)
{
	ft_clean_toke(info_shell, data);
	free(info_shell->old_pwd);
	free(info_shell->new_pwd);
}