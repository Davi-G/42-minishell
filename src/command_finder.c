/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:45 by sergisan          #+#    #+#             */
/*   Updated: 2024/04/25 14:34:35 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Desde donde se llame a exe_existing_command hay que igualarlo a una variable entera
//Para que cuando se ejecute echo $? tengamos un numero de salida del ultimo comando

int	exe_existing_command(t_data *info, t_master *minishell, char **env)
{
	if (ft_strcmp(info->toke1, "echo") == 0)
		return (echo_cmd(info));
	else if (ft_strcmp(info->toke1, "pwd") == 0)
		return (pwd_cmd());
	else if (ft_strcmp(info->toke1, "cd") == 0)
		return (cd_cmd(minishell, info));
	else if (ft_strcmp(info->toke1, "env") == 0)
		env_cmd(env);
	else if (ft_strcmp(info->toke1, "exit") == 0)
		exit_cmd(info, minishell);
	else
	{
		execute_cmd(info, env);
	}
//	else if (ft_strcmp(info->toke1, "export") == 0)
//		export_cmd(info, env);
//	else if (ft_strcmp(info->toke1, "unset") == 0)
//		unset_cmd();
	return (0);
}
