#include "minishell.h"

/* 
int	exist_command(char *command)
{
	if (ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0)
	{
		return (1);
	}
	return (0);
} */

//Desde donde se llame a exe_existing_command hay que igualarlo a una variable entera
//Para que cuando se ejecute echo $? tengamos un numero de salida del ultimo comando

int	exe_existing_command(t_data *info, t_master *minishell)
{
 /*	if (ft_strcmp((*info).toke1, "echo") == 0)
		return (echo_cmd((*info).toke3));
	if (ft_strcmp((*info).command[0], "pwd") == 0)
		return (pwd_cmd());
	if (ft_strcmp((*info).command[0], "cd") == 0)
		return (cd_cmd((*info).command));
	if (ft_strcmp((*info).command[0], "export") == 0)
		export_cmd();
	if (ft_strcmp((*info).command[0], "unset") == 0)
		unset_cmd();
	if (ft_strcmp((*info).command[0], "env") == 0)
		env_cmd(); */
	if (ft_strcmp((*info).toke1, "exit") == 0)
		exit_cmd((*info).toke1, minishell);
	return (0);
}
/* 
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
} */

/* int	pwd_cmd(void)
{
	char	*mem;

	mem = getcwd(NULL, 0);
	ft_putstr(mem);
	return (0);
} */

//int	cd_cmd(char *str)
//int	export_cmd()
//int	unset_cmd()
//int	env()

int	exit_cmd(char	*command, t_master *minishell)
{
	(void)command;
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
	} */
	
		//ft_putstr("exit\n");
		minishell->exit_status = 1;
		/* if (command[1])
			return(ft_atoi(command[1]));
		else */
			return (0);

}
