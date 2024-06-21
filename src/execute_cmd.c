/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:39:50 by davi-g            #+#    #+#             */
/*   Updated: 2024/06/19 17:57:18 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_access(char **command, char **path)
{
	int		i;
	char	*aux;
	char	*str;

	i = 0;
	if (!command)
		return (0);
	while (path[i])
	{
		aux = path[i];
		str = ft_strjoin(aux, "/");
		aux = ft_strjoin(str, command[0]);
		if (access(aux, X_OK) == 0)
		{
			return (aux);
			break ;
		}
		i++;
	}
	return (0);
}

/* void	execute_cmd(t_data *info, char **env)
{
	char *path;
	
	path_finder(env, info);
	if (!info->toke3)
	{
		info->toke3 = malloc(sizeof(char *) * 2);
		info->toke3[0] = info->toke1;
	}
	path = check_access(info->toke3, info->path_split);	
	if (execve(path, info->toke3, env) != 0)
	{
		printf("minishell: %s: command not found\n", info->toke3[0]);
		return ;
	}
} */

char	**unitary_command(t_data *info)
{
	char	*aux;
	char 	**command;
	
	aux = NULL;
	command = malloc(sizeof(char *) * 3);
	if (info->toke2)
	{
		command[0] = info->toke1[0];
		command[1] = info->toke2[0]; 
		/* aux = ft_strjoin(info->toke1, " ");
		command = ft_strjoin(aux, info->toke2); */
	}
	else if (info->toke3)
	{
		aux = ft_strjoin(info->toke1[0], " ");
		command[0] = ft_strjoin(aux, info->toke3[0]);
	}
	else
		command[0] = ft_strdup(info->toke1[0]);
	free (aux);
	return (command);
}

int	execute_cmd(t_data *info, char **env)
{
	char *path;
	char **command;
	pid_t pid;
	
	command = malloc(sizeof(char *) * 10);
	path_finder(env, info);
	command = unitary_command(info);
	if (ft_strchr(info->toke1[0], '/') != NULL)
        path = ft_strdup(info->toke1[0]);
    else
	{
        path = check_access(command, info->path_split);
	}
	if (!path)
	{
		printf("minishell: %s: command not found\n", info->toke1[0]);
		free (command);
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("Fork error\n");
		exit(1);
	}
	if (pid != 0)
		waitpid(pid, NULL, 0);
	else if (execve(path, command, env) != 0)
	{
		free (command);
		return (1);
	}
	free (command);
	return (0);
}

char	**path_finder(char **env, t_data *info)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i]);
			info->path_split = ft_split(path + 5, ':');
			free(path);
			return (info->path_split);
		}
		i++;
	}
	return (0);
}
