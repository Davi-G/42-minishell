/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:33:28 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/09 12:31:01 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
    {
        global_response = 130;
	    rl_on_new_line();
        ft_putstr("\n");
	    rl_redisplay();
	    rl_replace_line("", 0);
    }
}

void	handle_eof(char *input)
{
    if (!input)
	{
		global_response = 131;
        ft_putstr("Exiting minishell\n");
        exit(0);
    }
}
