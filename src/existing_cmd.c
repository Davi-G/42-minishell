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

int	print_value(char *str, int i)
{
	int		j;
	char	*get_env;
	char	*aux;

	j = 0;
	while (str[i + j])
		j++;
	aux = ft_calloc(j + 1, sizeof(char *));
	j = 0;
	while (str[i] && str[i] != -36)
	{
		aux[j] = str[i];
		i++;
		j++;
	}
	get_env = getenv(aux);
	if (get_env)
		ft_printf("%s", get_env);
	return (j - 2);
}

void	check_cases(t_master *info_shell, char *str)
{
	int	i;

	i = 0;
	if (str[i] == -36 && !str[1])
		write(1, "$", 1);
	while (str[i])
	{
		if (str[i] == -36)
		{
			i++;
			if (str[i] == 36)
				write(1, "$$", 2);
			else if (str[i] == '?')
				ft_printf("%i", info_shell->cmd_response);
			else
				i += print_value(str, i) + 1;
		}
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
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
	if (current && n_boolean)
	{
		if (current->toke[0] && current->toke[0] == -36)
			ft_putstr("$\n");
		else if (current->toke[0])
			ft_printf("%s\n", current->toke);
	    return (0);
	}
	if (n_boolean)
		current = current->next;
	while (current)
	{
		check_cases(info_shell, current->toke);
		current = current->next;
		write(1, " ", 1);
	}
	if (!n_boolean)
		ft_putstr("\n");
	else
		ft_putstr("%\n");
	return (0);
}

int	pwd_cmd(void)
{
	char *cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (1);
	ft_putstr(cwd);
	ft_putstr("\n");
	free(cwd);
	return (0);
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