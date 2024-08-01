#include "../minishell.h"
#include <stdio.h>

int print_vars(t_var *var)
{
	int	i;

	i = 0;
	while(var && var->next)
	{
		printf("%s", var->key);
		printf("=");
		printf("%s\n", var->value);
		var = var->next;
	}
	return (0);
}

int env(t_data *data)
{
	int i;

	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return (0);
}


int echo(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		printf("%s", args[i]);
		if(args[i + 1] && ft_strlen(args[i + 1]) > 0)
			printf(" ");
	}
	printf("\n");

	// if (args[1] = "-n")
	// while(args[i])

	return (0);
}


int builtin(t_cmd *cmd, t_data *data)
{
	int	i;
	int	res;

	i = 1;
	if (strnlcmp(cmd->args[0], "export"))
	{
		if (cmd->args_qty < 2)
			return (print_vars(data->var));
		else
			while (i < cmd->args_qty)
			{
				res = (exp0rt(cmd->args[i], data->var, data));
				i++;
				if (res)
					return(res);
			}
	}
	if (strnlcmp(cmd->args[0], "env"))
		return(env(data));
	if (strnlcmp(cmd->args[0], "echo"))
		return(echo(cmd->args));
	if (strnlcmp(cmd->args[0], "exit"))
		my_exit(data);
	return (1);
}