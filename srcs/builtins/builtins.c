#include "../minishell.h"

// value может быть пустым NULL
//declare x 
int	add_new_var(t_var *var, t_data *data, t_cmd *cmd)
{
	char **temp;
	int	i;
	i = 0;
	var->next = (t_var *)malloc(sizeof(t_var));
	//if (!var->next)
	var = var->next;
	var->next = NULL;
	var->key = ft_strdup(cmd->args[1]);
	var->value = ft_strdup(cmd->args[3]);
	temp = (char **)malloc((sizeof(char *) * (data->envpc + 2)));
	// if 
	
	while (data->envp[i])
	{
		temp[i] = ft_strdup(data->envp[i]);
		free(data->envp[i]);
	}
	free(data->envp);
	temp[i + 1] = ft_str3join(var->key, "=", var->value);
	temp[i + 2] = NULL;
	data->envpc = envpcpy(data, temp, &data->envp);
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

int export(t_data *data, t_cmd *cmd)
{
	char 	*name;
	char 	*new_str;
	int		i;
	t_var	*var;

	if (cmd->args_qty < 2)
		return (print_env(data), 0);
	// if (cmd->args_qty < 4)
	//  	return (1);
	name = cmd->args[1];
	if (ft_strncmp(cmd->args[2], "=", 1))
		return (1);
	while (*name)
		if (!ft_isalnum(*name) && *name != '_')
			return (printf("%s is wrong variable name\n", name), 1);
	i = 0;
	while (var)
	{
		if (!ft_strncmp(var->key, name, ft_strlen(name)))
		{
			free(data->var->value);
			var->value = ft_strdup(cmd->args[3]);
			return 0;
		}
	}
	return (add_new_var(var, data, cmd));
}
 
// int print(t_var *var)
// {
// 	int	i;

// 	i = 0;
// 	while(var)
// 	{
// 		printf("%s", var->key);
// 		printf("=");
// 		printf("%s\n", var->value);
// 		var = var->next;
// 	}
// 	return (0);
// }
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
		return(export(data, cmd));
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen("env")))
		return(env(data));
	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")))
		return(echo(cmd->args, 0));
	return (1);
}