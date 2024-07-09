/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:34 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/09 16:12:49 by dagomez          ###   ########.fr       */
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

void   error(t_master *info_shell, t_data *data)
{
	char *msg;
	
	ft_clean_toke(info_shell, data);
	msg = NULL;
	if (info_shell->error == 1)
		msg = "minishell: syntax error with open quotes";
	error_msg(msg);
}
