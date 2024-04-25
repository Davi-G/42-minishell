/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/25 18:29:41 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*home_finder(t_master *control, char *home)
{
	int		i;
	int		j;

	i = 0;
	home = NULL;
	control->old_pwd = getcwd(0, 0);
	while (control->old_pwd[i])
		i++;
	j = i;
	while (control->old_pwd[i] != '/')
		i--;
	i++;
	home = malloc(sizeof(char) * (j - i));
	j = 0;
	while (control->old_pwd[i])
	{
		home[j] = control->old_pwd[i];
		i++;
		j++;
	}
	home[j] = '-';
	home[j + 1] = '>';
	home[j + 2] = '$';
	home[j + 3] = '\0';
	return (home);
}

static char *set_home(char *home, t_master *control)
{
	home = home_finder(control, home);
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
	while (control.exit_status != 1)
	{
		home = set_home(home, &control);
		out = readline(home);
		if (ft_strlen(out) > 0)
			add_history(out);
		info = parser(out);
		if (info.toke1)
			exe_existing_command(&info, &control, env);
	}
	return (0);
}
