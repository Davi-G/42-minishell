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

static int    try_prev_dir(char *full_route)
{
    char    *final_route;
    int        i;

    i = ft_strlen(full_route);
    while (full_route[i] != '/')
        i--;
    i++;
    final_route = ft_calloc(i, sizeof(char));
    ft_strlcpy(final_route, full_route, i);
    if (chdir(final_route) == -1)
    {
	    return (1);
	}
    return (0);
}

static int	try_change_dir(t_master *info_shell, t_data *command, char *pwd)
{
	if (chdir(command->toke3[0]) == -1)
	{
		printf("cd: No such file or directory: %s\n", command->toke3[0]);
		return (1);
	}
	info_shell->new_pwd = getcwd(0, 0);
	info_shell->old_pwd = ft_strdup(pwd);
	return (0);
}


int	cd_cmd(t_master *info_shell, t_data *command)
{
	char *aux;

	aux = NULL;
	if (!command->toke3 && !command->toke2)
		chdir(getenv("HOME"));
	else if (command->toke3[1])
	{
		ft_putstr("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (command->toke2 && ft_strcmp(command->toke2, "-") == 0)
	{
		aux = getcwd(0, 0);
		if (chdir(info_shell->old_pwd) == -1)
		{
			ft_putstr("minishell: cd: OLDPWD not set\n");
			return (1);
		}
		info_shell->old_pwd = aux;
		info_shell->new_pwd = getcwd(0, 0);
		printf("%s\n", info_shell->old_pwd);
	}
	else if (command->toke3[0][0] == '.' && command->toke3[0][1] == '.' && command->toke3[0][2] == '\0')
		{
			info_shell->old_pwd = getcwd(0, 0);
			return (try_prev_dir(getcwd(0, 0)));
		}
 	else
		return (try_change_dir(info_shell, command, getcwd(0, 0)));
	return (0);
}

static void	env_printer(t_data *info_shell)
{
	int i;
	
	i = 0;
	while (info_shell->env[i])
	{
		printf("%s\n", info_shell->env[i]);
		i++;
	}
}

static void	*ft_realloc(void *ptr, size_t current_size, size_t new_size)
{
    void	*new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    else if (!ptr)
        return (ft_calloc(new_size, sizeof(char)));
    else
    {
        new_ptr = malloc(new_size);
        if (new_ptr)
        {
            ft_memcpy(new_ptr, ptr, current_size);
            free(ptr);
        }
        return (new_ptr);
    }
}

void	add_env_var(t_data *data, char *var)
{
	int i;
	
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, ft_strlen(var)) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(var);
			return ;
		}
		i++;
	}
	data->env = ft_realloc(data->env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	if (!data->env)
		return ;
	data->env[i] = ft_strdup(var);
	data->env[i + 1] = NULL;

}

void	export_cmd(t_data *command, char **env)
{
	int i;
	
	command->env = env;
	i = 0;
	if (!command->toke3[0])
	{
		env_printer(command);
		return ;
	}
	i = 0;
	while (command->toke3[i])
	{
		if (command->toke3[i][0] == '=')
			printf("minishell: export: not a valid identifier %s\n", command->toke3[i]);
		else
			add_env_var(command, command->toke3[i]);
		i++;
	}
}