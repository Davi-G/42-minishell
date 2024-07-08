/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:48:11 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 21:48:24 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirection(t_data *cmd)
{
    int fd;

    if (cmd->type == TRUNC)
    {
        fd = open(cmd->next->toke, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    else if (cmd->type == APPEND)
    {
        fd = open(cmd->next->toke, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    else if (cmd->type == INPUT)
    {
        fd = open(cmd->next->toke, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}

void	while_commands(t_master *info_shell, t_data *cmd)
{
    t_data *current_cmd = cmd;

    while (current_cmd)
    {
        if (current_cmd->type == CMD )
        {
            if (current_cmd->next && current_cmd->next->type == PIPE)
            {
                execute_pipeline(info_shell, current_cmd);
                while (current_cmd && current_cmd->type != PIPE)
                    current_cmd = current_cmd->next;
				if (current_cmd)
                    current_cmd = current_cmd->next; 
            }
            else if (current_cmd->next && (current_cmd->next->type == TRUNC || current_cmd->next->type == APPEND || current_cmd->next->type == INPUT))
            {
                handle_redirection(current_cmd->next);
                exe_existing_command(current_cmd, info_shell, info_shell->env);
                current_cmd = current_cmd->next->next;
            }
            else
            {
			    exe_existing_command(current_cmd, info_shell, info_shell->env);
				current_cmd = current_cmd->next;
			}	
			
		}
		else
        	current_cmd = current_cmd->next;
    }
}
