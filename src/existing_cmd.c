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
	printf("n_boolean: %d\n", n_boolean);
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
/* {
	int	n_boolean;
	int	i;
	
	n_boolean = 0;
	i = 1;
	if (ft_strcmp(argv[i], "-n") == 0)
	{
		n_boolean = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (argv[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (n_boolean != 1 && i != 1)
		write (1, "\n", 1);
	return (0);
} */

int	pwd_cmd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	ft_putstr(cwd);
	ft_putstr("\n");
	return (0);
}

int	exit_cmd(char	*command, t_master *minishell)
{
	/* if (command[0] && command[1] && command[2])
	{
		ft_putstr("exit\n");
		ft_putstr("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (command[0] && command[1] && isnumeric(command[1]) == 1)
	{
		ft_putstr("exit\n");
		ft_putstr("minishell: exit: numeric argument required\n");
		return (255);
	}
	else
	{
		ft_putstr("exit\n");
		if (command[1])
			return(ft_atoi(command[1]));
		else
			return (0);
	} */
	(void)command;
	minishell->exit_status = 1;
	return 0;
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

int env_cmd(t_mini *info_shell)
{
	int i;
	
	i = 0;
	while (info_shell->envp[i])
		ft_putendl_fd(info_shell->envp[i++], 1);
	return 0;
}

int	cd_cmd(t_mini *info_shell, char** command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	if (i > 1)
	{
		ft_putstr("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (i == 1)
	{
		//Arreglar aqui?¿?¿?¿?¿?¿
		info_shell->oldpwd = getcwd(0, 0);
		chdir("");
	}
}

cd
export
*/
