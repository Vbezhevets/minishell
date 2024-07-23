#include "../minishell.h"


int add_env_var(t_var **var, char *add_str)
{
	char	**temp;
	int		i;

	temp = ft_split(add_str, '=');
	// if (!temp)
		//printf("wrong variable arguments\n"); exit
	i = 0;
	(*var)->key = temp[0];
	if (temp[1])
		(*var)->value = temp[1]; 
	else
		(*var)->value = ft_strdup("\0");
	(*var)->next = (t_var *)malloc(sizeof(t_var));
	*var = (*var)->next;
	free(temp); //?
	return (0);
}

int envpcpy(t_data *data, char **src_envp, char ***dst_envp, t_var *var)
{
	int		i;
	
	i = 0;
	while(src_envp[i])
		i++;
	*dst_envp = (char **)malloc((sizeof(char *) * (i + 1)));
	// if
	i = 0;
	while (src_envp[i])
	{
		// if (var && var->next) // why??????
		// 	var = var->next;
		// else
		add_env_var(&var, src_envp[i]);
		(*dst_envp)[i] = (char *)malloc(sizeof(char) * (ft_strlen(src_envp[i]) + 1));
		// if 
		ft_strcpy((*dst_envp)[i], src_envp[i]);
		i++;
	}
	(*dst_envp)[i] = NULL;
	if (var)
		var = NULL;
	return (i);
}

// int	check_var(char *new_var)
// {
// 	char 	**temp;
// 	int		i;
// 	int 	wrong;
// 	char	*value;

// 	wrong = 0;
// 	i = 0;
// 	temp = ft_split(new_var, '=');
// 	if (!temp)
// 		return (printf("wrong variable arguments\n"), 1);
// 	value = temp[1];
// 	if (ft_isdigit(temp[0][0]))
// 		wrong++;
// 	else 
// 		while (temp[0][i])
// 		{
// 			if (!ft_isalnum(temp[0][i]) && temp[0][i] != '_')
// 				{
// 					wrong++;
// 					break;
// 				}
// 			i++;
// 		}
// 	if (wrong)
// 		printf("%s is wrong variable name\n", temp[0]);
// 	free_and_null_(temp);
// 	return(free(temp), wrong);
// }

int	check_var_name(char *name)
{
	int 	wrong;
	int		i;

	i = 0;
	wrong = 0;
	if (ft_isdigit(name[0]))
		wrong++;
	else 
		while (name[i])
		{
			if (!ft_isalnum(name[i]) && name[i] != '_')
				{
					wrong++;
					break;
				}
			i++;
		}
	return (wrong);
}

char **get_new_var(char *new_var)
{
	char 	**temp;
	int 	i;

	i = 1;
	temp = ft_split(new_var, '=');
	if (!temp)
		return (printf("wrong variable arguments\n"), NULL);
	if (check_var_name(temp[0]))
	{
		printf("%s is wrong var name\n", temp[0]);
		free_and_null_(temp);
		return (NULL);
	}
	if (temp[1])
	{
		temp[1] = expand_str(temp[1]);
		while (temp[++i])
		{
			temp[1] = free_join(temp[1], "=");
			temp[1] = free_join(temp[1], expand_str(temp[i]));
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

	new_var = get_new_var(new_var_str);
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
 
