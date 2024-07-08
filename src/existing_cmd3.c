/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existing_cmd3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:51:21 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 21:51:44 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_master *info_shell, t_data *current)
{
	int 	i;
	char	**var;

	i = 0;
	current = current->next;
	if (current == NULL || current->type != 2)
	{
		var = env_sorter(info_shell->env, 0, 0);
		while (var[i])
			ft_printf("declare -x %s\n", var[i++]);
		return ;
	}
	while (current && current->toke)
	{
 		if (current->type == 2)
			info_shell->env = add_env_var(info_shell, current->toke);
		current = current->next;
	}
}

int	ft_strlen_until(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	delete_envp_single_var(t_master *info_shell, t_data *current)
{
	int	env_var_length;
	int	curr_var_length;
	int i;

	i = 0;
	while (info_shell->env[i])
	{
		env_var_length = ft_strlen_until(info_shell->env[i], '=');
		curr_var_length = ft_strlen_until(current->toke, '=');
		if (env_var_length == curr_var_length)
		{
			if (ft_strncmp(info_shell->env[i], current->toke, env_var_length) == 0)
			{
				while (info_shell->env[i])
				{
					info_shell->env[i] = info_shell->env[i + 1];
					i++;
				}
				info_shell->exported_vars -= 1;
				break;
			}
		}
		i++;
	}
}

void	unset_cmd(t_master *info_shell, t_data *current)
{
	current = current->next;
	if (current == NULL || current->toke == NULL)
	{
		ft_putstr("minishell: unset: not enough arguments\n");
		return ;
	}
	while (current != NULL && current->type == 2)
	{
		if (ft_strchr(current->toke, '=') != NULL)
			printf("minishell: unset: `%s': not a valid identifier\n", current->toke);
		else
			delete_envp_single_var(info_shell, current);
		current = current->next;
	}
}
