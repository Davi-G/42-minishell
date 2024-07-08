/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existing_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:49:18 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 22:03:04 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cmd(t_data *current, t_master *minishell)
{
	if (!(current->next) || current->next->type != 2)
	{
		minishell->exit_status = 1;
		return (0);
	}
	else if (current->next && current->next->type == 2 && current->next->next && current->next->next->type == 2)
	{
		ft_putstr("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (current->next && current->next->type == 2
		&& is_numeric(current->next->toke) == 1)
	{
		ft_putstr("minishell: exit: numeric argument required\n");
		return (255);
	}
	else if (current->next->type == 2)
	{
		minishell->exit_status = 1;
		return (ft_atoi(current->next->toke));
	}
	return (0);
}

int	env_cmd(t_master *info_shell)
{
	int i;
	int	arr_length;

	i = 0;
	arr_length = ft_strlen_array(info_shell->env);
	while (info_shell->env[i] && info_shell->env[i][0] != '\0')
	{
		if (i < (arr_length - info_shell->exported_vars))
			printf("%s\n", info_shell->env[i]);
		i++;
	}
	return (0);
}

void	actualize_env(t_master *info_shell)
{
	int i;

	i = 0;
	while (info_shell->env[i])
	{
		if (ft_strncmp(info_shell->env[i], "OLDPWD=", 7) == 0)
		{
			if (info_shell->env[i] != NULL)
				free(info_shell->env[i]);
			info_shell->env[i] = ft_strjoin("OLDPWD=", info_shell->old_pwd);
		}
		if (ft_strncmp(info_shell->env[i], "PWD=", 4) == 0)
		{
			if (info_shell->env[i] != NULL)
				free(info_shell->env[i]);
			info_shell->env[i] = ft_strjoin("PWD=", getcwd(0, 0));
		}
		i++;
	}
}

int	try_change_dir(t_master *info_shell, char *route, char *pwd)
{
	if (chdir(route) == -1)
	{
		printf("cd: No such file or directory: %s\n", route);
		return (1);
	}
	info_shell->new_pwd = getcwd(0, 0);
	info_shell->old_pwd = ft_strdup(pwd);
	free(pwd);
	actualize_env(info_shell);
	return (0);
}

int	cd_cmd(t_master *info_shell, t_data *current)
{
	char *aux;

	aux = NULL;
	if (!(current->next))
		chdir(getenv("HOME"));
	else if (current->next->type == 2 && ft_strcmp(current->next->toke, "-") == 0)
	{
		aux = getcwd(0, 0);
		chdir(info_shell->old_pwd);
		free(info_shell->old_pwd);
		free(info_shell->new_pwd);
		info_shell->old_pwd = ft_strdup(aux);
		info_shell->new_pwd = getcwd(0, 0);
		free (aux);
		actualize_env(info_shell);
		ft_printf("%s\n", info_shell->new_pwd);
	}
	else if (!current->next->next)
		return(try_change_dir(info_shell, current->next->toke, getcwd(0, 0)));
	return (0);
}