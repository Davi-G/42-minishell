/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/23 11:37:04 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *out;
	t_master	control;
	t_data		info;
	
	control.exit_status = 0;
	out = 0;
	while(control.exit_status != 1)
	{
		out = readline("minishell->$ ");
		info = parser(out);
		control.old_pwd = getcwd(0, 0);
		exe_existing_command(&info, &control);
	}
	return (0);
}