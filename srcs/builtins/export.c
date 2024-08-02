#include "../minishell.h"



int	check_var_name(char *name)
{
	int		i;

	i = 0;
	if (ft_isdigit(name[0]))
		return(1);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return(1);
		i++;
	}
	return (0);
}

char **get_new_var(char *new_var, t_data *data)
{
	char 	**temp;
	int 	i;

	i = 1;
	temp = ft_split(new_var, '=');
	if (!temp)
		return (printf("wrong variable arguments\n"), NULL);
	if (check_var_name(temp[0]))
	{
		error( temp[0], ": not a valid identifier", data, 1);
		free_and_null_(temp);
		return (NULL);
	}
	if (temp[1])
	{
		temp[1] = get_rid_q(temp[1], NULL);
		while (temp[++i])
		{
			temp[1] = free_join(temp[1], "=");
			temp[1] = free_join(temp[1], get_rid_q(temp[i], NULL));
		}
	}
	else
		temp = add_str_arr(temp, "");
	return(temp);
}

int	add_envp_str_and_var(t_var *var, char *new_var_str, t_data *data)
{
	char 	**temp_envp;
	char 	**new_var;
	int		i;

	new_var = get_new_var(new_var_str, data);
	if (!new_var)
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
	temp_envp[i] = ft_str3join(new_var[0], "=", new_var[1]);
	temp_envp[i + 1] = NULL;	
	data->envpc++;
	envpcpy(data, temp_envp, &data->envp, var);
	return (0);
}

int exp0rt(char *arg, t_var *var, t_data *data)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(arg, '='); //? что если несколько =
	if (!temp)
		return (printf("wrong variable name or split alloc error\n"), 1);
	while (var && var->key)
	{
		if (strnlcmp(var->key, temp[0]))
		{
			free(var->value);
			var->value = ft_strdup(temp[1]);
			free(data->envp[i]);
			data->envp[i] = ft_strdup(arg);
			free_and_null_(temp);
			free(temp);
			return (0);
		}   
		var = var->next;
		i++;
	}
	return (add_envp_str_and_var(data->var, arg, data));
}
 
