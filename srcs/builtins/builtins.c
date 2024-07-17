#include "../minishell.h"
#include <stdio.h>
// value может быть пустым NULL
//declare x??
int	add_new_var(t_data *data, int i, t_cmd *cmd)
{
	data->envpc = envpcpy(data->var, data->var, 0, NULL);

	data->var[i].key = ft_strdup(cmd->args[1]);
	data->var[i].value = ft_strdup(cmd->args[3]);
	return (0);
}

int export(t_data *data, t_cmd *cmd)
{
	char *name;
	char *new_str;
	int	i;

	if (cmd->args_qty < 4) // убрать долждна работать и без второго аргумента
	 	return (1);
	name = cmd->args[1];
	if (ft_strncmp(cmd->args[2], "=", 1))
		return (1);
	while (*name)
		if (!ft_isalnum(*name) && *name != '_')
			return (printf("%s is wrong variable name\n", name), 1);
	i = 0;
	while (data->var[i]->key)
	{
		if (!ft_strncmp(data->var[i]->key, name, ft_strlen(name)))
		{
			free(data->var[i]->value);
			data->var[i]->value = ft_strdup(cmd->args[3]);
			return 0;
		}
		i++;
	}
	return (add_new_var(data, i, cmd));
}
 
int env(t_var **var)
{
	int	i;

	i = 0;
	while(var[i])
	{
		if (var[i])
		{
			printf("%s", var[i]->key);
			printf("=");
			printf("%s\n", var[i]->value);
		}
		i++;
	}
	return (0);
}
int echo(char **args, int i)
{
	while (args[++i])
	{
		printf("%s", args[i]);
		if(args[i])
			printf(" ");
	}
	printf("\n");

	// if (args[1] = "-n")
	// while(args[i])

	return (0);
}


int builtin(t_cmd *cmd, t_data *data)
{
	// if (!ft_strncmp(cmd->args[0], "export", ft_strlen("export")))
	// 	return(export(data, cmd));
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen("env")))
		return(env(data->var));
	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")))
		return(echo(cmd->args, 0));
	return (1);
}