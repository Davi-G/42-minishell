#include "minishell.h"

int	echo_cmd(char *argv)
{
	int	n_boolean;
	int	i;
	
	n_boolean = 0;
	i = 1;
	while (argv[i] && ft_strcmp(argv, "-n") != 0)
		i++;
	if (ft_strcmp(argv, "-n") == 0)
	{
		i += 2;
		n_boolean = 1;
	}
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (argv[i + 1] && argv[i][0])
			write (1, " ", 1);
		i++;
	}
	if (n_boolean != 1)
		write (1, "\n", 1);
	return (0);
}

int	pwd_cmd(void)
{
	char	*mem;

	mem = getcwd(NULL, 0);
	ft_putstr(mem);
	return (0);
}


int	exit_cmd(char	**command)
{
	if (command[0] && command[1] && command[2])
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
	}
	//minishell->exit = 1;
}