/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:34 by davi-g            #+#    #+#             */
/*   Updated: 2024/06/06 11:53:14 by dagomez          ###   ########.fr       */
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

void   error(t_data *info)
{
	char *msg;
	
	msg = NULL;
	if (info->error == 1)
		msg = "minishell: syntax error with open quotes";
	error_msg(msg);
}