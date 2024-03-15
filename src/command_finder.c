#include "minishell.h"

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
}

//Desde donde se llame a exe_existing_command hay que igualarlo a una variable entera
//Para que cuando se ejecute echo $? tengamos un numero de salida del ultimo comando

int	exe_existing_command(char **command);
{
	if (ft_strcmp(command[0], "echo") == 0)
		return (echo_cmd(command));
	if (ft_strcmp(command[0], "pwd") == 0)
		return (pwd_cmd());
	if (ft_strcmp(command[0], "cd") == 0)
		return (cd_cmd(command));
	if (ft_strcmp(command[0], "export") == 0)
		export_cmd();
	if (ft_strcmp(command[0], "unset") == 0)
		unset_cmd();
	if (ft_strcmp(command[0], "env") == 0)
		env_cmd();
	if (ft_strcmp(command[0], "exit") == 0)
		exit_cmd();
}