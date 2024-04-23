/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:45 by sergisan          #+#    #+#             */
/*   Updated: 2024/04/23 15:53:58 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	exist_command(char *command)
{
	if (ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0)
	{
		return (1);
	}
	return (0);
} */

//Desde donde se llame a exe_existing_command hay que igualarlo a una variable entera
//Para que cuando se ejecute echo $? tengamos un numero de salida del ultimo comando

int	exe_existing_command(t_data *info, t_master *minishell)
{
	if (ft_strcmp(info->toke1, "echo") == 0)
		return (echo_cmd(info));
	if (ft_strcmp(info->toke1, "pwd") == 0)
		return (pwd_cmd());
	if (ft_strcmp(info->toke1, "cd") == 0)
		return (cd_cmd(minishell, info));
//	if (ft_strcmp(info->toke1, "export") == 0)
//		export_cmd();
//	if (ft_strcmp(info->toke1, "unset") == 0)
//		unset_cmd();
//	if (ft_strcmp(info->toke1, "env") == 0)
//		env_cmd();
	if (ft_strcmp(info->toke1, "exit") == 0)
		exit_cmd(info, minishell);
	else
	{
		//ft_putstr("minishell: ");
		ft_putstr(info->toke1);
		ft_putstr(": command not found\n");
	}
	return (0);
}