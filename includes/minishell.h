/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:48:49 by davi-g            #+#    #+#             */
/*   Updated: 2024/03/13 17:58:56 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*----<Includes>----*/
# include <../42-libft/libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

/*----<Structures>----*/
typedef struct s_data
{
	char *toke1;
	char *toke2;
	char *toke3;
}	t_data;

typedef struct s_master
{
	int	exit_status;
}	t_master;


/*----<Functions>----*/
t_data	parser(char *str);
int		exe_existing_command(t_data *info, t_master *minishell);
int		echo_cmd(char *argv);
int		exit_cmd(char	*command, t_master *minishell);
int		ft_strcmp(char *str1, char *str2);
int		is_numeric(char *argv);
void	free_array(char **array);

#endif
