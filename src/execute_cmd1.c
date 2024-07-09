/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:48:11 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/09 18:35:51 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirection(t_data *cmd)
{
    int fd;

		ft_printf("entro\n");

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

int pipeline_checker(t_master *info_shell, t_data *cmd)
{
    t_data *current;
    int     boolean;

    boolean = 0;
    current = cmd;
    while (current)
    {
        if (current->type == PIPE)
        {
            boolean = 1;
            break;
        }
        else if (current->type == END)
            break;
        current = current->next;
    }
    if (boolean == 1)
    {
        execute_pipeline(info_shell, current);
        return (boolean);
    }
    return (boolean);

}

t_data    *redirection(t_master *info_shell, t_data *current_cmd)
{
    if (pipeline_checker(info_shell, current_cmd) == 1)
    {
        /* while (current_cmd && current_cmd->type != PIPE)
            current_cmd = current_cmd->next; */
        if (current_cmd->type == PIPE)
            current_cmd = current_cmd->next;
    }
    else
	{
		exe_existing_command(current_cmd, info_shell, info_shell->env);
	}
    return (current_cmd);
}

void	while_commands(t_master *info_shell, t_data *cmd)
{
    t_data  *current_cmd;

    current_cmd = cmd;
    while (current_cmd)
    {
        if (current_cmd->type == CMD)
            current_cmd = redirection(info_shell, current_cmd);
    	if (current_cmd->next &&
        (current_cmd->next->type == TRUNC || current_cmd->next->type == APPEND ||
        current_cmd->next->type == INPUT))
    	{
     		handle_redirection(current_cmd->next);
      		exe_existing_command(current_cmd, info_shell, info_shell->env);
     		current_cmd = current_cmd->next;
   		}
        if (current_cmd)
        	current_cmd = current_cmd->next;
    }
}