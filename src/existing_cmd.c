/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existing_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:35 by sergisan          #+#    #+#             */
/*   Updated: 2024/04/23 14:52:35 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_cmd(t_data *info)
{
	int	n_boolean;
	int	i;

	i = 0;
	n_boolean = 0;
	if (ft_strcmp(info->toke2, "-n") == 0)
		n_boolean = 1;
	if (!info->toke3)
		return (1);
	while (info->toke3[i])
	{
		ft_putstr(info->toke3[i]);
		if (info->toke3[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (n_boolean == 1)
		write (1, "%", 1);
	write (1, "\n", 1);
	return (0);
}

int	pwd_cmd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	ft_putstr(cwd);
	ft_putstr("\n");
	return (0);
}

int	exit_cmd(t_data	*command, t_master *minishell)
{
	if (!command->toke3)
	{
		minishell->exit_status = 1;
		return (0);
	}
	else if (command->toke1 && command->toke3[0] && command->toke3[1])
	{
		ft_putstr("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (command->toke1 && command->toke3[0] && is_numeric(command->toke3[0]) == 1)
	{
		//comprobar si es necesario que sea numerico o es valido com palabras
		ft_putstr("minishell: exit: numeric argument required\n");
		return (255);
	}
	else if (command->toke3[0])
	{
		minishell->exit_status = 1;
		return (ft_atoi(command->toke3[0]));
	}
	return (0);
}

/* 
char **delete_envp_single_var(char **str, const char *var) {
    int i;
	int j;
	
	i = 0;
    j = 0;
	while (str[i])
	{
        if (ft_strcmp(str[i], var) != 0)
            str[j++] = ft_strdup(str[i]);
        i++;
    }
    str[j] = NULL;
    return str;
}

void delete_envp_vars(char **str, char **vars)
{
    int i;
	
	i = 0;
    while (vars[i])
        str = delete_envp_single_var(str, vars[i++]);
}

void unset_cmd(t_mini *info_shell, char *var)
{
    char **vars;
	
	vars = ft_split(var, ' ');
    if (vars == NULL)
	{
        ft_printf("Error al dividir la cadena de variables\n");
        return;
    }
    delete_envp_vars(info_shell->envp, vars);
    free_array(vars);
}
*/

int env_cmd(char **env)
{
	int i;
	
	i = 0;
		write(1, "H\n", 2);
	while (env[i])
		printf("%s\n", env[i++]);
	return 0;
}

int	try_prev_dir(char *full_route)
{
	char	*final_route;
	int		i;

	i = ft_strlen(full_route);
	while (full_route[i] != '/')
		i--;
	i++;
	final_route = ft_calloc(i, sizeof(char));
	ft_strlcpy(final_route, full_route, i);
	if (chdir(final_route) == -1)
		return (1);
	return (0);
}

/* int	try_change_dir()
{

} */

int	cd_cmd(t_master *info_shell, t_data *command)
{
/* 	printf("old_pwd: %s\n", info_shell->old_pwd);
	printf("toke1 %s\n", command->toke1);
	printf("toke2 %s\n", command->toke2); */
	if (!command->toke3 && !command->toke2)
		chdir(getenv("HOME"));
	else if (command->toke3[1])
	{
		ft_putstr("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (command->toke2 && ft_strcmp(command->toke2, "-") == 0)
	{
		if (chdir(info_shell->old_pwd) == -1)
		{
			ft_putstr("minishell: cd: OLDPWD not set\n");
			return (1);
		}
		ft_putstr(info_shell->old_pwd);
	}
	else if (command->toke3[0][0] == '.' && command->toke3[0][1] == '.')
		return (try_prev_dir(getcwd(0, 0)));
/* 	else
		try_change_dir(getcwd(0, 0), command->toke3[0]); */
	return (0);
}

/*
export
 */