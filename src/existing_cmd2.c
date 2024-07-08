/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existing_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:50:25 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/08 22:01:49 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	*ft_realloc(void *ptr, size_t current_size, size_t new_size)
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
				if (ft_strchr(var, '=') && !var[var_length + 1])
					var = ft_strjoin(var, "''");
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
	if (!ft_strchr(var, '='))
		var = ft_strjoin(var, "=''");
	else if (ft_strchr(var, '=') && !var[var_length + 1])
		var = ft_strjoin(var, "''");
    info_shell->env[i] = ft_strdup(var);
    info_shell->env[i + 1] = NULL;
	info_shell->exported_vars++;
    return (info_shell->env);
}