/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/06/12 14:13:24 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_env(t_master *info_shell, char **env)
{
	int	i;

	i = 0;
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
	old_pwd = getcwd(0, 0);
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
	home[j] = '-';
	home[j + 1] = '>';
	home[j + 2] = '\0';
	return (home);
}

static char *set_home(char *home)
{
	home = home_finder(getcwd(0, 0), home);
	home = ft_strjoin(MAGENTA, home);
	home = ft_strjoin(home, RESET);
	return (home);
}

int	main(int ac, char **av, char **env)
{
	char		*out;
	char		*home;
	t_master	control;
	t_data		info;

	(void)ac;
	(void)av;
	using_history();
	control.exit_status = 0;
	out = 0;
	control.old_pwd = getcwd(0, 0);
	initialize_env(&control, env);
	while (control.exit_status != 1)
	{
		home = set_home(home);
		out = readline(home);
		free(home);
		if (ft_strlen(out) > 0)
			add_history(out);
		info = parser(out);
		if (info.error == 0 && info.toke1)
			exe_existing_command(&info, &control, env);
		else
			error(&info);
	}
	return (0);
}
