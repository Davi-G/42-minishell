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

//actualmente "funciona"
//mete un salto de linea por la cara
//si el $?esta en medio deuna palabra no funciona jajajaj salu2

int	check_boolean(t_data *info)
{
	t_data *current;
	char	*token;
	int		i;

	current = info;
	i = 1;
	if (current && current->toke)
    {
        token = current->toke;
        while (token[i])
		{
			if (token[0] == '-' && token[1] == 'n' && token[i] == 'n')
				i++;
			else
				return (0);
		}
    }
	return (1);
}

int echo_cmd(t_master *info_shell, t_data *info)
{
	int n_boolean;
	t_data *current;

	if (!info || !info->next)
	{
		ft_putstr("\n");
		return (0);
	}
	n_boolean = 0;
	current = info->next;
	n_boolean = check_boolean(current);
	if (current && !current->next && n_boolean)
        return (0);
	if (n_boolean)
		current = current->next;
	while (current->next)
	{
		if (current->toke)
		{
			if (ft_strcmp(current->toke, "$?") == 0)
				ft_printf("%i", info_shell->exit_status);
			else
				ft_putstr(current->toke);
		}
		current = current->next;
		write(1, " ", 1);
	}
	if (!n_boolean)
		ft_putstr("\n");
	ft_putstr("\n");
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
int	exit_cmd(t_data *current, t_master *minishell)
{
	if (!(current->next) || current->next->type != 2)
	{
		minishell->exit_status = 1;
		return (0);
	}
	else if (current->next && current->next->type == 2 && current->next->next && current->next->next->type == 2)
	{
		ft_putstr("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (current->next && current->next->type == 2
		&& is_numeric(current->next->toke) == 1)
	{
		//No debe salir normal con palabras (num 2). El exit dara codigo de 2, aunque saldrá
		ft_putstr("minishell: exit: numeric argument required\n");
		return (2);
	}
	else if (current->next->type == 2)
	{
		minishell->exit_status = 1;
		return (ft_atoi(current->next->toke));
	}
	return (0);
}

void	initialize_env(t_master *info_shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	info_shell->env = ft_calloc(i + 1, sizeof(char *));
	if (!info_shell->env)
	{
		ft_putstr("Error: calloc fail\n");
		info_shell->error = 1;
		return ;
	}
	i = 0;
	while (envp[i])
	{
		info_shell->env[i] = ft_strdup(envp[i]);
		i++;
	}
}

int	env_cmd(t_master *info_shell)
{
	int i;
	int	arr_length;

	i = 0;
	arr_length = ft_strlen_array(info_shell->env);
	while (info_shell->env[i] && info_shell->env[i][0] != '\0')
	{
		if (i < (arr_length - info_shell->exported_vars))
			printf("%s\n", info_shell->env[i]);
		i++;
	}
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
/* 
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
*/
static int	try_change_dir(t_master *info_shell, char *route, char *pwd)
{
	if (chdir(route) == -1)
	{
		printf("cd: No such file or directory: %s\n", route);
		return (1);
	}
	//free(info_shell->new_pwd);
	//free(info_shell->old_pwd);
	info_shell->new_pwd = getcwd(0, 0);
	info_shell->old_pwd = ft_strdup(pwd);
	free(pwd);
	actualize_env(info_shell);
	return (0);
}
//Si no hay nada, o el que hay detras es != 2 (ARG) -> chdir(getenv("HOME"));
//Si si hay algo, hay que diferenciarlos
//Si hay 2 argumentos tras el cd y los dos son arg, toomanyarguments
int	cd_cmd(t_master *info_shell, t_data *current)
{
	char *aux;

	aux = NULL;
	if (!(current->next))
		chdir(getenv("HOME"));
	else if (current->next->type == 2 && ft_strcmp(current->next->toke, "-") == 0)
	{
		//El if esta porque si el directorio al que entra es el home, entonces imprime la virgulilla
		//Si no, imprime el directorio al que entra
		//Tambien habra que liberar aux, old_pwd (puesto que se iguala) y tambien new_pwd antes de igualarlo de nuevo
		aux = getcwd(0, 0);
		chdir(info_shell->old_pwd);
		free(info_shell->old_pwd);
		free(info_shell->new_pwd);
		info_shell->old_pwd = ft_strdup(aux);
		info_shell->new_pwd = getcwd(0, 0);
		free (aux);
		actualize_env(info_shell);
		if (ft_strcmp(info_shell->new_pwd, getenv("HOME")) != 0)
			printf("%s\n", info_shell->new_pwd);
		else
			ft_putstr("~");
	}
	else if (!current->next->next)
		return(try_change_dir(info_shell, current->next->toke, getcwd(0, 0)));
	return (0);
}

void	ft_swap_arr(char **a, char **b)
{
    char *temp;

	temp = *a;
    *a = *b;
    *b = temp;
}

char **env_sorter(char **env, int i, int length)
{
    int checker;
    char **env_copy;

    length = ft_strlen_array(env);
    env_copy = (char **)malloc(sizeof(char *) * (length + 1));
    while (i < length)
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
    env_copy[length] = NULL;
    checker = 0;
    while (checker == 0)
	{
        i = 0;
        checker = 1;
        while (i < length - 1)
		{
            if (ft_strcmp(env_copy[i], env_copy[i + 1]) > 0)
			{
                ft_swap_arr(&env_copy[i], &env_copy[i + 1]);
				i = 0;
                checker = 0;
            }
            i++;
        }
        length--;
    }
    return (env_copy);
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
			//free(ptr);
		}
		return (new_ptr);
	}
}

int ft_strcmp_until(char *str1, char *str2, char c)
{
    int i;

	i = 0;
    while (str1[i] && str2[i] && str1[i] != c && str2[i] != c)
	{
        if (str1[i] != str2[i])
            return (1);
        i++;
    }
    if ((str1[i] == c && str2[i] == c))
        return (2);
	else if ((str1[i] == '\0' && str2[i] == '\0') || str1[i] != str2[i])
		return (2);
    return (0);
}

char **add_env_var(t_master *info_shell, char *var)
{
	char	**aux;
    int 	i;
	int		var_length;

    i = 0;
	var_length = ft_strlen_until(var, '=');
    while (info_shell->env[i])
	{
        if (ft_strlen_until(info_shell->env[i], '=') == var_length)
		{
			if (ft_strncmp(info_shell->env[i], var, var_length) == 0)
			{
            	free(info_shell->env[i]);
            	info_shell->env[i] = ft_strdup(var);
            	return (info_shell->env);
			}
		}
        i++;
    }
    aux = ft_realloc(info_shell->env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
    if (!aux)
	{
        return (NULL);
	}
	info_shell->env = aux;
    info_shell->env[i] = ft_strdup(var);
    info_shell->env[i + 1] = NULL;
	info_shell->exported_vars++;
    return (info_shell->env);
}
//El free_array comentado es por que lo se que se pasa no es una copia, sino la original
//Quiero entender que si
//En mi wsl cuando haces export de una variable (por ejemplo export hola) se genera hola=''
//En este export no, falta probar que ocurre en 42
void	export_cmd(t_master *info_shell, t_data *current)
{
	int 	i;
	char	**var;

	i = 0;
	current = current->next;
	if (current == NULL || current->type != 2)
	{
		var = env_sorter(info_shell->env, 0, 0);
		while (var[i])
			ft_printf("declare -x %s\n", var[i++]);
		//free_array(var);
		return ;
	}
	while (current && current->toke)
	{
 		if (current->type == 2)
			info_shell->env = add_env_var(info_shell, current->toke);
		current = current->next;
	}
}

int	ft_strlen_until(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	delete_envp_single_var(t_master *info_shell, t_data *current)
{
	int	env_var_length;
	int	curr_var_length;
	int i;

	i = 0;
	while (info_shell->env[i])
	{
		env_var_length = ft_strlen_until(info_shell->env[i], '=');
		curr_var_length = ft_strlen_until(current->toke, '=');
		if (env_var_length == curr_var_length)
		{
			if (ft_strncmp(info_shell->env[i], current->toke, env_var_length) == 0)
			{
				while (info_shell->env[i])
				{
					info_shell->env[i] = info_shell->env[i + 1];
					i++;
				}
				break;
			}
		}
		i++;
	}
}

void	unset_cmd(t_master *info_shell, t_data *current)
{
	current = current->next;
	if (current == NULL || current->toke == NULL)
	{
		ft_putstr("minishell: unset: not enough arguments\n");
		return ;
	}
	while (current != NULL && current->type == 2)
	{
		if (ft_strchr(current->toke, '=') != NULL)
			printf("minishell: unset: `%s': not a valid identifier\n", current->toke);
		else
			delete_envp_single_var(info_shell, current);
		current = current->next;
	}
}
/*
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
*/