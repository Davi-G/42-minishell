/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:45 by sergisan          #+#    #+#             */
/*   Updated: 2024/05/22 20:48:40 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Desde donde se llame a exe_existing_command hay que igualarlo a una variable entera
//Para que cuando se ejecute echo $? tengamos un numero de salida del ultimo comando

int	exe_existing_command(t_data *command, t_master *info_shell, char **env)
{
	if (ft_strcmp(command->toke1, "echo") == 0)
		return (echo_cmd(command));
	else if (ft_strcmp(command->toke1, "pwd") == 0)
		return (pwd_cmd());
	else if (ft_strcmp(command->toke1, "cd") == 0)
		return (cd_cmd(info_shell, command));
	else if (ft_strcmp(command->toke1, "env") == 0)
		env_cmd(info_shell);
	else if (ft_strcmp(command->toke1, "exit") == 0)
		return (exit_cmd(command, info_shell));
	else if (ft_strcmp(command->toke1, "export") == 0)
		export_cmd(info_shell, command, env);
	else
		execute_cmd(command, env);
//	else if (ft_strcmp(command->toke1, "unset") == 0)
//		unset_cmd();
	return (0);
}
