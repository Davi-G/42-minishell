/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existing_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/04/23 14:52:35 by sergisan          #+#    #+#             */
/*   Updated: 2024/04/23 14:52:35 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	echo_cmd(t_data *info)
{
	int n_boolean;
	int i;

	i = 0;
	n_boolean = 0;
	if (ft_strcmp(info->toke2, "-n") == 0)
		n_boolean = 1;
	if (!info->toke3)
	{
		ft_putstr("\n");
		return (1);
	}
	while (info->toke3[i])
	{
		ft_putstr(info->toke3[i]);
		if (ft_strlen_array(info->toke3) > 1 && i < ft_strlen_array(info->toke3)
			- 1)
			write(1, " ", 1);
		i++;
	}
	if (n_boolean == 1)
		write(1, "%", 1);
	write(1, "\n", 1);
	return (0);
}

int	pwd_cmd(void)
{
	char *cwd;

	cwd = getcwd(0, 0);
	ft_putstr(cwd);
	ft_putstr("\n");
	free(cwd);
	return (0);
}

int	exit_cmd(t_data *command, t_master *minishell)
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
	else if (command->toke1 && command->toke3[0]
		&& is_numeric(command->toke3[0]) == 1)
	{
		// comprobar si es necesario que sea numerico o es valido com palabras
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

void	initialize_env(t_master *info_shell, t_data *command, char **envp)
{
	info_shell->i = 0;

	while (envp[info_shell->i])
		info_shell->i++;
	info_shell->env = ft_calloc((info_shell->i) + 1, sizeof(char *));
	info_shell->i = 0;
	if (!info_shell->env)
	{
		ft_putstr("Error: calloc fail\n");
		command->error = 1;
		return ;
	}
	while (envp[info_shell->i])
	{
		info_shell->env[info_shell->i] = ft_strdup(envp[info_shell->i]);
		info_shell->i++;
	}
	info_shell->i = 0;
}

int	env_cmd(t_master *info_shell)
{
	int i;

	i = 0;
	while (info_shell->env[i] && info_shell->env[i][0] != '\0')
		printf("%s\n", info_shell->env[i++]);
	return (0);
}

static void	actualize_env(t_master *info_shell)
{
	int i;

	i = 0;
	while (info_shell->env[i])
	{
		if (ft_strncmp(info_shell->env[i], "OLDPWD=", 7) == 0)
		{
			if (info_shell->env[i] != NULL)
				free(info_shell->env[i]);
			info_shell->env[i] = ft_strjoin("OLDPWD=", info_shell->old_pwd);
		}
		if (ft_strncmp(info_shell->env[i], "PWD=", 4) == 0)
		{
			if (info_shell->env[i] != NULL)
				free(info_shell->env[i]);
			info_shell->env[i] = ft_strjoin("PWD=", getcwd(0, 0));
		}
		i++;
	}
}

static int	try_prev_dir(t_master *info_shell, char *full_route)
{
	char *final_route;
	int i;

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
	actualize_env(info_shell);
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
	actualize_env(info_shell);
	return (0);
}

int	cd_cmd(t_master *info_shell, t_data *command)
{
	char *aux;

	aux = NULL;
	if (!command->toke3 && !command->toke2)
	{
		actualize_env(info_shell);
		chdir(getenv("HOME"));
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
		actualize_env(info_shell);
		printf("%s\n", info_shell->old_pwd);
	}
	else if (command->toke3[0][0] == '.' && command->toke3[0][1] == '.'
		&& command->toke3[0][2] == '\0')
	{
		info_shell->old_pwd = getcwd(0, 0);
		return (try_prev_dir(info_shell, getcwd(0, 0)));
	}
	else if (command->toke3[1])
	{
		ft_putstr("minishell: cd: too many arguments\n");
		return (1);
	}
	else
		return (try_change_dir(info_shell, command, getcwd(0, 0)));
	return (0);
}

static void	*ft_realloc(void *ptr, size_t current_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (ft_calloc(new_size, sizeof(char)));
	else
	{
		new_ptr = malloc(new_size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, current_size);
			// free(ptr);
		}
		return (new_ptr);
	}
}

t_master	*add_env_var(t_master *info_shell, char *var)
{
	int i;

	i = 0;
	while (info_shell->env[i])
	{
		if (ft_strncmp(info_shell->env[i], var, ft_strlen(var)) == 0)
		{
			// free(info_shell->env[i]);
			info_shell->env[i] = ft_strdup(var);
			return (info_shell);
		}
		i++;
	}
	info_shell->env = ft_realloc(info_shell->env, sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2));
	if (!info_shell->env)
		return (info_shell);
	info_shell->env[i] = var;
	printf("El valor de info_Shell->[i] es %s\n", info_shell->env[i]);
	info_shell->env[i + 1] = NULL;
	return (info_shell);
}

void	export_cmd(t_master *info_shell, t_data *command, char **env)
{
	int i;

	(void)env;
	i = 0;
	if (!command->toke3)
	{
		// En verdad no es asi porque el env o export imprime tambien las funciones
		env_cmd(info_shell);
		return ;
	}
	i = 0;
	while (command->toke3[i])
	{
		if (command->toke3[i][0] == '=')
			printf("minishell: export: not a valid identifier %s\n",
				command->toke3[i]);
		else
			info_shell = add_env_var(info_shell, command->toke3[i]);
		i++;
	}
}

static char	**delete_envp_single_var(char **envp, char *var)
{
	int i;
	int j;
	char **aux_envp;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	aux_envp = ft_calloc(i, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], var) != 0)
		{
			aux_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	aux_envp[j] = "\0";
	free_array(envp);
	return (aux_envp);
}

static int	ft_strlen_array_j(char **array)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
			j++;
		k += j;
		i++;
	}
	return (k);
}

void	unset_cmd(t_master *info_shell, t_data *command)
{
	int i;
	int j;
	char **aux;

	i = 0;
	j = 0;
	aux = NULL;
	(void)i;
	command->i = 0;
	command->j = 0;
	if (!command->toke3)
	{
		ft_putstr("minishell: unset: not enough arguments\n");
		return ;
	}
	aux = ft_calloc(ft_strlen_array(info_shell->env), sizeof(char *) + 1);
	while (command->toke3[command->i])
	{
		command->j = 0;
		if (ft_strchr(command->toke3[command->i], '=') != NULL)
			printf("minishell: unset: `%s': not a valid identifier\n",
				command->toke3[command->i]);
		else
		{
			i = ft_strlen_array_j(info_shell->env)
				- ft_strlen(command->toke3[command->i]);
			while (info_shell->env[command->j]
				&& ft_strcmp(info_shell->env[command->j],
					command->toke3[command->i]) != 0)
			{
				aux[j] = ft_strdup(info_shell->env[command->j]);
				j++;
				command->j++;
			}
			aux[j] = calloc(i, sizeof(char) + 1);
			if (info_shell->env[command->j])
			{
				free(info_shell->env);
				aux = delete_envp_single_var(aux, command->toke3[command->i]);
			}
		}
		command->i++;
	}
	info_shell->env = aux;
}
