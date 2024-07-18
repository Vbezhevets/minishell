#include "../minishell.h"
#include <stdio.h>

// value может быть пустым NULL
//declare x 
int	add_new_var(t_var *var, char *var_str, t_data *data)
{
	char **temp;
	char **temp_envp;
	int	i;
	i = 0;

	temp = ft_split(var_str, '=');
	// if (!temp)
		//printf("wrong variable arguments\n"); exit
	i = 0;
	while (temp[0][i])
	{
		if (!ft_isalnum(temp[0][i]) && temp[0][i] != '_')
			return (printf("%s is wrong variable name\n", temp[0]), 1);
		i++;
	}
	temp_envp = (char **)malloc((sizeof(char *) * (data->envpc + 1)));
	// if 
	i = 0;
	while (i < data->envpc)
	{

		temp_envp[i] = ft_strdup(data->envp[i]);
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	printf("get str: %s\n", var_str);
	temp_envp[i] = ft_strdup(var_str);
	temp_envp[i + 1] = NULL;
	data->envpc++;
	envpcpy(data, temp_envp, &data->envp, var);
	return (0);
}

void print_env(t_data *data)
{
	extern char **environ;
	
	int i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

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

int export(t_cmd *cmd, t_data *data)
{
	int		i;
	t_var	*var;
	char	**temp;

	var = data->var;
	temp = ft_split(cmd->args[1], '=');
	if (!temp)
		return (printf("wrong variable name or split alloc error\n"), 1);
	i = 0;
	while (var && var->key)
	{
		// printf("%s                                     k\n", var->key);
		// printf("%p                                     p\n", var);



		if (!ft_strncmp(var->key, temp[0], ft_strlen(temp[0])))
		{
			free(data->var->value);
			var->value = ft_strdup(temp[1]);
			free(data->envp[i]);
			data->envp[i] = ft_str3join(var->key, "=", var->value);
			free(temp);
			return (0);
		}   
		var = var->next;
		i++;
	}
	return (add_new_var(var, cmd->args[1], data));
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
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen("export")))
	{
		if (cmd->args_qty < 2)
			return (print_vars(data->var));
		else
			return(export(cmd, data));
	}
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen("env")))
		return(env(data));
	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")))
		return(echo(cmd->args, 0));
	return (1);
}