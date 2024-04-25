/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:39:50 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/25 15:12:54 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_access(char **command, char **path)
{
	int		i;
	char	*aux;
	char	*str;

	i = 0;
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

static void	ft_memorymove(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = str[i + 1];
        i++;
    }
}

void	execute_cmd(t_data *info, char **env)
{
	char *path;
	
	path_finder(env, info);
	if (!info->toke3)
	{
		info->toke3 = malloc(sizeof(char *) * 2);
		info->toke3[0] = info->toke1;
	}
	path = check_access(info->toke3, info->path_split);	
	if (ft_strcmp(info->toke3[0], "awk") == 0 && info->toke3[1][0] == '\'')
	{
		ft_memorymove(info->toke3[1]);
		info->toke3[1][ft_strlen(info->toke3[1]) - 1] = '\0';
	}
	if (execve(path, info->toke3, env) != 0)
	{
		printf("minishell: %s: command not found\n", info->toke3[0]);
		return ;
	}
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

char	**split_command(char *av)
{
	char	**split_1;

	split_1 = ft_split(av, ' ');
	return (split_1);
}
