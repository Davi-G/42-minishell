/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/26 21:11:54 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
	return (0);
}
