/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:48:49 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 22:03:17 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*----<Includes>----*/
# include "../42-libft/libft.h"
//# include "libft.h"
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
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

/*----<Colors>----*/
# define RESET		"\e[0m"
# define YELLOW		"\e[33m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"

/*------>Types<------*/
# define NONE		0
# define CMD		1
# define ARG		2
# define TRUNC		3
# define APPEND		4
# define INPUT		5
# define PIPE		6
# define HEREDOC	7
# define END		8

/*----<Structures>----*/
typedef struct s_data
{
	char	*toke;
	int		type;
	struct	s_data	*next;
	struct	s_data	*prev;
	char 	**path_split;
	char 	quote;
	int		i;
	int		j;
	int		x;
}	t_data;

typedef struct s_master
{
	char	*old_pwd;
	char	*new_pwd;
	char 	**env;
	int		cmd_response;
	int		exported_vars;
	int 	error;
	int		i;
	int		j;
	int		exit_status;
}	t_master;

/*----<Functions>----*/
t_data	parser(char *str, t_master *info_shell);
void	init_info(t_data *info, t_master *control);
int		exe_existing_command(t_data *info, t_master *minishell, char **env);
int		cd_cmd(t_master *info_shell, t_data *command);
int		echo_cmd(t_master *info_shell, t_data *info);
int		exit_cmd(t_data	*command, t_master *minishell);
int		pwd_cmd(void);
int 	env_cmd(t_master *info_shell);
void    export_cmd(t_master *info_shell, t_data *command);
int		ft_strlen_until(char *str, char c);
void	unset_cmd(t_master *info_shell, t_data *command);
int		ft_strcmp(char *str1, char *str2);
int		is_numeric(char *argv);
void	free_array(char **array);
void	ft_putstr(char *s);
int		ft_strlen_array(char **array);
char	*path_finder(char *cmd, char **env);
void	exe_cmd(t_master *info_shell, t_data *command, char **env);
int		ft_strlen_array_full(char **array);
void	error(t_master *info_shell);
char	**unitary_command(t_data *info);
int		is_ignore(char *str, int i);
t_data	set_toke(t_data *data, char *str);
t_data	*next_toke(t_data *data, char *str);
void	while_commands(t_master *info_shell, t_data *cmd);
void	handle_eof(char *input);
void	is_space(char *str, int *i);
t_data	ft_clean_toke(t_master *info_shell, t_data *data);
void	del_toke(t_data *data);
int		is_sep(char *str, int i, char quote);
char	*spaces(char *str, t_data *data, char *aux);
int		count_space(char *str, t_data *data);
char*	remove_quotes(char *str, t_data *data);
void	ctrl_c(int sig);
void	print_tokens(t_data *data);
char *find_command_path(char *command, char *path_var);
char *path_finder(char *command, char **env);
char **unitary_command(t_data *cmd);
void exe_cmd(t_master *info_shell, t_data *command, char **env);
void execute_pipeline(t_master *info_shell, t_data *cmd);
void handle_redirection(t_data *cmd);
void	while_commands(t_master *info_shell, t_data *cmd);
int	check_boolean(t_data *info);
int	print_value(char *str, int i);
void	check_cases(t_master *info_shell, char *str);
int echo_cmd(t_master *info_shell, t_data *info);
int	pwd_cmd(void);
void	ft_swap_arr(char **a, char **b);
char **env_sorter(char **env, int i, int length);
void	*ft_realloc(void *ptr, size_t current_size, size_t new_size);
int ft_strcmp_until(char *str1, char *str2, char c);
char **add_env_var(t_master *info_shell, char *var);
void	export_cmd(t_master *info_shell, t_data *current);
int	ft_strlen_until(char *str, char c);
void	delete_envp_single_var(t_master *info_shell, t_data *current);
void	unset_cmd(t_master *info_shell, t_data *current);
int	exit_cmd(t_data *current, t_master *minishell);
int	env_cmd(t_master *info_shell);
void	actualize_env(t_master *info_shell);
int	try_change_dir(t_master *info_shell, char *route, char *pwd);
int	cd_cmd(t_master *info_shell, t_data *current);

extern int global_response;
#endif 
