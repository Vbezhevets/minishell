/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:23:36 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 11:15:23 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*var_init(char *name)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		return (error("all8c error", NULL, NULL, 2), NULL);
	var->next = NULL;
	var->value = NULL;
	var->key = NULL;
	if (name)
		var->key = ft_strdup(name);
	if (!var->key)
		return (free(var), NULL);
	return (var);
}

t_var	*take_or_create_var(char *name, t_data *data, t_var *var, t_var *prev)
{
	var = data->var;
	while (var && var->key)
	{
		if (strnlcmp(var->key, name))
		{
			free(var->value);
			return (var);
		}
		prev = var;
		var = var->next;
	}
	if (!var)
	{
		var = var_init(name);
		if (!var)
			return (NULL);
		if (prev)
			prev->next = var;
		else
			data->var = var;
	}
	return (var);
}

int	add_env_var(char *add_str, t_data *data, char *temp_str, int i)
{
	char	**temp;
	t_var	*new_var;

	temp = ft_split(add_str, '=');
	if (!temp)
		return (printf("%s wrong variable\n", add_str), 0);
	new_var = take_or_create_var(temp[0], data, NULL, NULL);
	if (temp[1])
		new_var->value = get_rid_q(temp[1], 0, 0, NULL);
	else
	{
		new_var->value = ft_strdup("\0");
		if (!new_var->value)
			return (free(new_var), ch3to_null(temp, NULL, NULL), 0);
		return (ch3to_null(temp, NULL, NULL), 0);
	}
	while (temp[++i])
	{
		new_var->value = free_join(new_var->value, "=");
		temp_str = ft_strdup(temp[i]);
		new_var->value = free_join(new_var->value, temp_str);
		free(temp_str);
	}
	return (ch3to_null(temp, NULL, NULL), 0);
}

int	envpcpy(char **src_envp, char ***dst_envp, t_data *data)
{
	int		i;

	i = 0;
	while (src_envp[i])
		i++;
	*dst_envp = (char **)malloc((sizeof(char *) * (i + 1)));
	if (!dst_envp)
		return (0);
	i = 0;
	while (src_envp[i])
	{
		if (add_env_var(src_envp[i], data, NULL, 1))
			return (f_till((*dst_envp), --i), free(*dst_envp), 0);
		(*dst_envp)[i] = (char *)malloc(sizeof
				(char) *(ft_strlen(src_envp[i]) + 1));
		if (!(*dst_envp)[i])
			return (f_till((*dst_envp), --i), free(*dst_envp), 0);
		ft_strcpy((*dst_envp)[i], src_envp[i]);
		i++;
	}
	(*dst_envp)[i] = NULL;
	return (i);
}

int	del_var(char *var_name, t_var *var, t_data *data, int *k)
{
	t_var	*prev;

	prev = NULL;
	while (var && var->key)
	{
		if (strnlcmp(var->key, var_name))
		{
			if (prev)
				prev->next = var->next;
			else
				data->var = var->next;
			free(var->key);
			free(var->value);
			free(var);
			*k = *k - 1;
			var = NULL;
		}
		prev = var;
		if (var)
			var = var->next;
	}
	return (0);
}
