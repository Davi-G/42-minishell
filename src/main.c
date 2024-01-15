/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:00:36 by davi-g            #+#    #+#             */
/*   Updated: 2024/01/15 14:38:37 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *str;
	char *out;
	
	out = "0";
	str = "minishell->$ ";
	while(strcmp("exit", out) != 0)
	{
		if (str)
			out = readline(str);
		else
			out = readline("minishell->$ ");
	}
	return (0);
}