#include "../minishell.h"
#include <stdio.h>

// value может быть пустым NULL
//declare x 

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

int	check_var(char *new_var)
{
	char **temp;
	int	i;
	int wrong;

	wrong = 0;
	i = 0;
	temp = ft_split(new_var, '=');
	if (!temp)
		return (printf("wrong variable arguments\n"), 1);
	if (ft_isdigit(temp[0][0]))
		wrong++;
	else 
		while (temp[0][i])
		{
			if (!ft_isalnum(temp[0][i]) && temp[0][i] != '_')
				{
					wrong++;
					break;
				}
			i++;
		}
	if (wrong)
		printf("%s is wrong variable name\n", temp[0]);
	free_and_null_(temp);
	return(free(temp), wrong);
}
int	add_new_envp_str(t_var *var, char *new_var, t_data *data)
{
	char **temp_envp;
	int	i;

	if (check_var(new_var))
		return (1);
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
	temp_envp[i] = ft_strdup(new_var);
	temp_envp[i + 1] = NULL;
	data->envpc++;
	envpcpy(data, temp_envp, &data->envp, var);
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
		if (!ft_strncmp(var->key, temp[0], ft_strlen(temp[0])) &&  (ft_strlen(temp[0]) == ft_strlen(var->key)))
		{
			free(data->var->value);
			var->value = ft_strdup(temp[1]);
			free(data->envp[i]);
			data->envp[i] = cmd->args[1];
			free(temp[0]);
			free(temp);
			return (0);
		}   
		var = var->next;
		i++;
	}
	return (add_new_envp_str(data->var, cmd->args[1], data));
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