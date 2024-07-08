/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:33:28 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 19:50:35 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
    {
        global_response = 130;
	    rl_redisplay();
	    rl_on_new_line();
	    rl_replace_line("", 0);
        ft_putstr("\n");
    }
    return ;
}

void	handle_eof(char *input)
{
    if (!input)
	{
        ft_putstr("Exiting minishell\n");
        exit(0);
    }
}
