/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/25 17:55:14 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*home_finder(t_master *control)
{
	int		i;
	int		j;
	char	*home;

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
		home = home_finder(&control);
		home = ft_strjoin(MAGENTA, home);
		home = ft_strjoin(home, RESET);
		control.old_pwd = getcwd(0, 0);
		out = readline(home);
		//out = readline(MAGENTA"ms$ "RESET);	
		if (ft_strlen(out) > 0)
			add_history(out);
		info = parser(out);
		if (info.toke1)
			exe_existing_command(&info, &control, env);
	}
	return (0);
}
