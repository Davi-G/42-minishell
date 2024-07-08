/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 19:42:42 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_env(t_master *info_shell, char **env)
{
	int	i;

	i = 0;
	info_shell->exported_vars = 0;
	info_shell->cmd_response = 0;
	while (env[i])
		i++;
	info_shell->env = ft_calloc(i + 1, sizeof(char *));
	if (!info_shell->env)
	{
		ft_putstr("Error: calloc fail\n");
		return ;
	}
	i = 0;
	while (env[i])
	{
		info_shell->env[i] = ft_strdup(env[i]);
		i++;
	}
}

static char	*home_finder(char *old_pwd, char *home)
{
	int		i;
	int		j;

	i = 0;
	home = NULL;
	while (old_pwd[i])
		i++;
	j = i;
	while (old_pwd[i] != '/')
		i--;
	i++;
	home = malloc(sizeof(char) * (j - i));
	j = 0;
	while (old_pwd[i])
	{
		home[j] = old_pwd[i];
		i++;
		j++;
	}
	home[j] = '/';
	home[j + 1] = '\0';
	return (home);
}

static char *set_home(char *home)
{
	char	*aux;

	aux = getcwd(0, 0);
	if (!ft_strcmp(aux, getenv("HOME")))
		home = ft_strdup("~");
	else
		home = home_finder(aux, home);
	home = ft_strjoin(MAGENTA, home);
	home = ft_strjoin(home, RESET);
	free(aux);
	return (home);
}

void	init_info(t_data *info, t_master *control)
{
	info->toke = NULL;
	info->type = 0;
	info->next = NULL;
	info->prev = NULL;
	info->path_split = NULL;
	info->quote = 0;
	info->i = 0;
	info->j = 0;
	info->x = 0;
	control->exit_status = 0;
	control->old_pwd = getcwd(0, 0);
	control->new_pwd = getcwd(0, 0);
	global_response = 0;
}

int	main(int ac, char **av, char **env)
{
	char		*out;
	char		*home;
	t_master	control;
	t_data		info;

	out = 0;
	using_history();
	init_info(&info, &control);
	initialize_env(&control, env);
	while (control.exit_status != 1 && ac == 1 && av[0])
	{
		signal(SIGINT, ctrl_c);
		home = set_home(home);
		out = readline(home);
		handle_eof(out);
		free(home);
		if (ft_strlen(out) > 0)
			add_history(out);
		info = parser(out, &control);
		if (control.error == 0 && info.toke)
			while_commands(&control, &info);
		else
			error(&control);
	}
	return (0);
}
