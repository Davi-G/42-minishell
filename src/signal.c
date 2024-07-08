/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:33:28 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 19:33:59 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
    ft_putstr("\n");
    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof(char *input)
{
    if (!input)
	{
        ft_putstr("Exiting minishell\n");
        exit(0);
    }
}
