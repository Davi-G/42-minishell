/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/03/13 17:48:45 by davi-g           ###   ########.fr       */
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
	while(control.exit_status == 0)
	{
		out = readline("minishell->$ ");
		info = parser(out);
		printf("toke1: %s\n", info.toke1);
		exe_existing_command(&info, &control);
	}
	return (0);
}