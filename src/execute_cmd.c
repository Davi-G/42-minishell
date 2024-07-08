/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:39:50 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 15:56:23 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_command_path(char *command, char *path_var)
{
    char	**path_split;
	char	*path;
    char	*full_path;
	int		i;
	
	path_split = ft_split(path_var, ':');
	i = 0;
    while (path_split[i])
	{
        path = ft_strjoin(path_split[i], "/");
        full_path = ft_strjoin(path, command);
        free(path);
        if (access(full_path, X_OK) == 0)
		{
            free_array(path_split);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_array(path_split);
    return (NULL);
}

char *path_finder(char *command, char **env)
{
    char *result;
    int i;

	i = 0;
    while (env[i])
	{
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
            result = find_command_path(command, env[i] + 5);
            break;
        }
        i++;
    }
    return (result);
}

char **unitary_command(t_data *cmd)
{
	t_data	*aux;
	char	**unitary_cmd;
	int		i;

	i = 0;
	aux = cmd;
	while (aux && (aux->type == CMD || aux->type == ARG))
	{
		aux = aux->next;
		i++;
	}
	unitary_cmd = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (cmd && (cmd->type == CMD || cmd->type == ARG))
	{
		unitary_cmd[i] = ft_strdup(cmd->toke);
		cmd = cmd->next;
		i++;
	}
	return (unitary_cmd);
}

/* void	execve_cmd(t_master *info_shell, t_data *cmd, char **env)
{
	char *path;
	char **unitary_cmd;

	(void)info_shell;
	path = path_finder(cmd->toke, env);
	unitary_cmd = unitary_command(cmd);
	printf("path: %s\n", path);
	if (path == NULL)
	{
		ft_putstr("minishell: command not found\n");
		exit(127);
	}
	while (unitary_cmd)
	{
		ft_putstr(*unitary_cmd);
		unitary_cmd++;
	}
	if (execve(path, unitary_cmd, env) == -1)
	{
		ft_putstr("minishell: command not found\n");
		exit(127);
	}
	free_array(unitary_cmd);
	free(path);
} */

void exe_cmd(t_master *info_shell, t_data *command, char **env)
{
    char	*path;
    char	**unitary_cmd;
	int		pid;

    path = path_finder(command->toke, env);
    unitary_cmd = unitary_command(command);
	if (path == NULL)
    {
        ft_putstr("minishell: command not found\n");
        info_shell->exit_status = 127;
		return ;
    }
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, unitary_cmd, env) == -1)
		{
			ft_putstr("minishell: command not found\n");
			info_shell->exit_status = 127;
		}
	}
	else
		waitpid(pid, NULL, 0);
    free_array(unitary_cmd);
    free(path);
}

void execute_pipeline(t_master *info_shell, t_data *cmd)
{
    int in_fd = 0;
    int fd[2];
    t_data *current_cmd = cmd;

    while (current_cmd)
    {
        pipe(fd);
        if (fork() == 0)
        {
            dup2(in_fd, STDIN_FILENO);
            if (current_cmd->next && current_cmd->next->type == PIPE)
                dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            exe_existing_command(current_cmd, info_shell, info_shell->env);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            in_fd = fd[0];
            while (current_cmd && current_cmd->type != PIPE)
                current_cmd = current_cmd->next;
            if (current_cmd)
                current_cmd = current_cmd->next;
        }
    }
}

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
