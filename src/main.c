/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/25 17:20:45 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
static char	*home_finder(t_master *control)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (control->old_pwd[i])
		i++;
	int j = i;
	while (control->old_pwd[i] != '/')
		i--;
	home = malloc(sizeof(char) * (j - i + 1));
	while (control->old_pwd[i])
	{
		home[i] = control->old_pwd[i];
		i++;
	}
	printf("home: %s\n", home);
	return (home);
} */

int	main(int ac, char **av, char **env)
{
	char		*out;
	//char		*home;
	t_master	control;
	t_data		info;

	(void)ac;
	(void)av;
	using_history();
	control.exit_status = 0;
	out = 0;
	//home = home_finder(&control);
	while (control.exit_status != 1)
	{
		control.old_pwd = getcwd(0, 0);
		out = readline(MAGENTA"minishell$ "RESET);	
		if (ft_strlen(out) > 0)
			add_history(out);
		info = parser(out);
		if (info.toke1)
			exe_existing_command(&info, &control, env);
	}
	return (0);
}
