/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:57:58 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 10:30:56 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return (0);
}

int	pwd(void)
{
	char	*w;

	w = getcwd(NULL, 0);
	if (!w)
		return (1);
	if (printf("%s\n", w) == -1)
	{
		free(w);
		return (1);
	}
	free(w);
	return (0);
}

static char	*fabricate_string(char *name, char *value)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	ret = ft_strjoin(tmp, value);
	free(tmp);
	return (ret);
}

static char	*ft_getenv(const char *const name, t_data *const data)
{
	size_t	max;
	t_var	*var;

	var = data->var;
	while (var)
	{
		if (ft_strlen((char *)name) > ft_strlen(var->key))
			max = ft_strlen((char *)name);
		else
			max = ft_strlen(var->key);
		if (!ft_strncmp((char *)name, var->key, max))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

int	cd(char *new, t_data *data)
{
	char	old[PATH_MAX];
	char	*ptr;

	getcwd(old, PATH_MAX);
	if (!new)
	{
		new = ft_getenv("HOME", data);
		if (!new)
			return (printf("There is no $HOME\n"), 1);
	}
	if (chdir(new) == -1)
	{
		perror("Minishell");
		return (1);
	}
	ptr = fabricate_string("PWD", new);
	exp0rt(ptr, data);
	free(ptr);
	ptr = fabricate_string("OLDPWD", old);
	exp0rt(ptr, data);
	free(ptr);
	return (0);
}

int	echo(char **args, int i, int k, int n)
{
	while (args[++i])
	{
		k = 1;
		if (args[i][0] && args[i][0] == '-' && args[i][1] && args[i][1] == 'n')
		{
			while (args[i][k] && args[i][k] == 'n')
				k++;
			if (!args[i][k])
				n = 1;
			else
				break ;
		}
		else
			break ;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] && ft_strlen(args[i + 1]) > 0)
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}

int	exit_handle(t_cmd *cmd, t_data *data)
{
	int	num;
	int	i;

	i = -1;
	if (cmd->args[1])
	{
		num = ft_atoi(cmd->args[1]) % 256;
		data->ex_stat = num;
	}
	if (cmd->args[1] && cmd->args[2])
		return (error("exit", ": too many arguments", data, 130), 130);
	if (cmd->args[1])
	{
		while (cmd->args[1][++i])
			if (!ft_isdigit(cmd->args[1][i]) && cmd->args[1][0] != '+'
			&& cmd->args[1][0] != '-')
				return (error(cmd->args[1], ": numeric argument required",
						data, 2), my_exit(data, NULL));
	}
	if (data->cmd_qty == 1)
		my_exit(data, NULL);
	return (0);
}

int	builtin(t_cmd *cmd, t_data *data)
{
	if (strnlcmp(cmd->args[0], "export"))
	{
		if (cmd->args_qty < 2)
			return (env(data));
		else
			return (exp0rt(cmd->args[1], data));
	}
	if (strnlcmp(cmd->args[0], "env"))
		return (env(data));
	if (strnlcmp(cmd->args[0], "unset"))
		return (unset(cmd->args[1], data, 0, 0));
	if (strnlcmp(cmd->args[0], "cd") && cmd->args[1] && !cmd->args[2])
		return (cd(cmd->args[1], data));
	if (strnlcmp(cmd->args[0], "pwd"))
		return (pwd());
	if (strnlcmp(cmd->args[0], "echo"))
		return (echo(cmd->args, 0, 1, 0));
	if (strnlcmp(cmd->args[0], "exit"))
		exit_handle(cmd, data);
	return (1);
}
