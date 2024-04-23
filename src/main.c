/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/23 17:57:58 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*out;
	t_master	control;
	t_data		info;

	(void)ac;
	(void)av;
	(void)env;
	using_history();
	control.exit_status = 0;
	out = 0;
	while (control.exit_status != 1)
	{
		out = readline("minishell->$ ");
		if (ft_strlen(out) > 0)
			add_history(out);
		info = parser(out);
		control.old_pwd = getcwd(0, 0);
		if (info.toke1)
			exe_existing_command(&info, &control);
	}
	return (0);
}
