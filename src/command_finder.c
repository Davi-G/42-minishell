/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:45 by sergisan          #+#    #+#             */
/*   Updated: 2024/07/08 15:54:57 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Desde donde se llame a exe_existing_command hay que igualarlo a una variable entera
//Para que cuando se ejecute echo $? tengamos un numero de salida del ultimo comando

int	exe_existing_command(t_data *command, t_master *info_shell, char **env)
{
	if (ft_strcmp(command->toke, "echo") == 0)
		return (echo_cmd(info_shell, command));
	else if (ft_strcmp(command->toke, "pwd") == 0)
		return (pwd_cmd());
	 else if (ft_strcmp(command->toke, "cd") == 0)
		return (cd_cmd(info_shell, command)); //segfault siempre
	else if (ft_strcmp(command->toke, "env") == 0)
		env_cmd(info_shell);
	else if (ft_strcmp(command->toke, "exit") == 0)
		return (exit_cmd(command, info_shell));
	else if (ft_strcmp(command->toke, "export") == 0)
		export_cmd(info_shell, command);
	else if (ft_strcmp(command->toke, "unset") == 0)
		unset_cmd(info_shell, command);
	else
		exe_cmd(info_shell, command, env);
	while (command && command->type != PIPE && command->type != TRUNC && command->type != APPEND && command->type != END)
		command = command->next;
	return (0);
}
