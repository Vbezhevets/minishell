/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:28:57 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 10:28:20 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var_name(char *name)
{
	int		i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (1);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	is_new_var(char *new_var, t_var *var)
{
	char	**temp;
	char	*name;

	temp = ft_split(new_var, '=');
	if (!temp)
		return (printf("wrong variable arguments\n"), 1);
	name = temp[0];
	while (var && var->key)
	{
		if (strnlcmp(var->key, name))
		{
			free_and_null_(temp);
			free(temp);
			return (0);
		}
		var = var->next;
	}
	free_and_null_(temp);
	free(temp);
	return (1);
}

int	replace_env_str(char *new_var_str, t_data *data, char **temp_new, int i)
{
	temp_new = ft_split(new_var_str, '=');
	if (!temp_new)
		return (printf("wrong variable arguments\n"), 0);
	if (!chr_mlc(&data->temp_envp, data->envpc + 1))
		return (free_and_null_(temp_new), free(temp_new), 0);
	while (++i < data->envpc)
	{
		data->temp_exists = ft_split(data->envp[i], '=');
		if (!data->temp_exists)
			return (f_till(data->temp_envp, --i), 0);
		if (strnlcmp(temp_new[0], data->temp_exists[0]))
			data->temp_envp[i] = ft_strdup(new_var_str);
		else
			data->temp_envp[i] = ft_strdup(data->envp[i]);
		if (!data->temp_envp[i])
			return (f_till(data->temp_envp, i), 0);
		free(data->envp[i]);
		ch3to_null(data->temp_exists, NULL, NULL);
	}
	data->temp_envp[i] = NULL;
	free(data->envp);
	envpcpy(data->temp_envp, &data->envp, data);
	ch3to_null(temp_new, data->temp_envp, NULL);
	return (0);
}

int	add_envp_str_and_var(char *new_var_str, t_data *data, int i)
{
	if (is_new_var(new_var_str, data->var))
	{
		if (!chr_mlc(&data->temp_arr, data->envpc + 2))
			return (error("allc error\n", NULL, data, 12), 12);
		while (i < data->envpc)
		{
			data->temp_arr[i] = ft_strdup(data->envp[i]);
			if (!data->temp_arr[i])
				return (f_till(data->temp_arr, --i), fnl(data->temp_arr[i]), 2);
			free(data->envp[i]);
			i++;
		}
		free(data->envp);
		data->temp_arr[i] = ft_strdup(new_var_str);
		if (!data->temp_arr[i])
			return (f_till(data->temp_arr, --i), fnl(data->temp_arr[i]), 2);
		data->temp_arr[i + 1] = NULL;
		data->envpc++;
		envpcpy(data->temp_arr, &data->envp, data);
		free_and_null_(data->temp_arr);
		fnl(data->temp_arr);
	}
	else
		return (replace_env_str(new_var_str, data, NULL, -1));
	return (0);
}

int	unset(char *var_name, t_data *data, int i, int k)
{
	if (!chr_mlc(&data->temp_envp, data->envpc + 1))
		return (error("all6c error\n", NULL, data, 12), 12);
	while (i < data->envpc)
	{
		if (!splt_mlc(&data->temp_exists, data->envp[i], '='))
			return (f_till(data->temp_envp, --i), fnl(data->temp_envp), 12);
		if (!strnlcmp(var_name, data->temp_exists[0]))
		{
			data->temp_envp[k] = ft_strdup(data->envp[i]);
			if (!data->temp_envp[k])
				return (f_till(data->temp_envp, --i), fnl(data->temp_envp), 1);
		}
		else
			del_var(var_name, data->var, data, &k);
		free(data->envp[i++]);
		ch3to_null(data->temp_exists, NULL, NULL);
		k++;
	}
	data->temp_envp[k] = NULL;
	free(data->envp);
	envpcpy(data->temp_envp, &data->envp, data);
	ch3to_null(data->temp_envp, NULL, NULL);
	if (k < i)
		data->envpc--;
	return (0);
}

int	exp0rt(char *arg, t_data *data)
{
	char	**temp;

	if (arg[0] == '=')
		return (error(arg, ": not a valid identifier", data, 1), 1);
	temp = ft_split(arg, '=');
	if (!temp)
		return (0);
	if (check_var_name(temp[0]))
	{
		error(temp[0], ": not a valid identifier", data, 1);
		free_and_null_(temp);
		free(temp);
		return (1);
	}
	free_and_null_(temp);
	free(temp);
	if (!add_envp_str_and_var(arg, data, 0))
		return (0);
	return (0);
}