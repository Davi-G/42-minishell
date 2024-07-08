/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:34 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 15:55:51 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_msg(char *msg)
{
	ft_putstr(RED);
	ft_putstr(msg);
	ft_putstr(RESET);
	ft_putstr("\n");
}

void   error(t_master *info_shell)
{
	char *msg;
	
	msg = NULL;
	if (info_shell->error == 1)
		msg = "minishell: syntax error with open quotes";
	error_msg(msg);
}
