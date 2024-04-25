/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:48:49 by davi-g            #+#    #+#             */
/*   Updated: 2024/04/25 16:55:27 by dagomez          ###   ########.fr       */
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

/*----<Colors>----*/
# define RESET		"\e[0m"
# define YELLOW		"\e[33m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"

/*----<Structures>----*/
typedef struct s_data
{
	char	*toke1;
	char	*toke2;
	char	**toke3;
	char 	**path_split;
	char 	**env;
}	t_data;

typedef struct s_master
{
	int		exit_status;
	char	*old_pwd;
	char	*new_pwd;
}	t_master;

/*----<Functions>----*/
t_data	parser(char *str);
int		exe_existing_command(t_data *info, t_master *minishell, char **env);
int		cd_cmd(t_master *info_shell, t_data *command);
int		echo_cmd(t_data *info);
int		exit_cmd(t_data	*command, t_master *minishell);
int		ft_strcmp(char *str1, char *str2);
int		is_numeric(char *argv);
void	free_array(char **array);
int		pwd_cmd(void);
void	ft_putstr(char *s);
int		ft_strlen_array(char **array);
char	**path_finder(char **env, t_data *info);
void	execute_cmd(t_data *info, char **env);
int 	env_cmd(char **env);

#endif 
