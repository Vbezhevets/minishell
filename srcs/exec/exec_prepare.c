/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:44:20 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 10:49:00 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_path(char **envp, char *cmd)
{
	int		i;
	char	**pathes;
	char	*path;

	pathes = NULL;
	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
		i++;
	if (envp[i])
		pathes = ft_split(envp[i] + 5, ':');
	if (!pathes)
		return (NULL);
	i = 0;
	while (pathes[i])
	{
		path = ft_str3join(pathes[i], "/", cmd);
		if (!access(path, F_OK))
			return (free_and_null_(pathes), free(pathes), path);
		free(path);
		i++;
	}
	free_and_null_(pathes);
	free(pathes);
	return (NULL);
}

int	is_bltin(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (strnlcmp(cmd->args[0], data->builtins[i]))
		{
			cmd->bi = 1;
			return (i + 1);
		}
		i--;
	}
	return (0);
}

int	is_cmd_exists(t_cmd **cmd, t_data *data)
{
	if (!(*cmd)->args)
	{
		data->cmd_qty--;
		*cmd = (*cmd)->next;
		return (0);
	}
	return (1);
}

int	check_cmd(t_cmd **cmd, t_data *data)
{
	if (!is_cmd_exists(cmd, data))
		return (0);
	if (is_bltin(*cmd, data))
		return (1);
	else if (ft_strchr((*cmd)->args[0], '/'))
	{
		(*cmd)->path = ft_strdup((*cmd)->args[0]);
		if (!(*cmd)->path)
			return (error("alloc error", NULL, NULL, 2), 0);
	}
	else
		((*cmd)->path = get_cmd_path(data->envp, (*cmd)->args[0]));
	if (!(*cmd)->path)
	{
		error((*cmd)->args[0], ": command not found", data, 127);
		if ((*cmd)->prev && (*cmd)->prev->ok)
			close(data->next_pipe[0]);
		data->cmd_qty--;
		*cmd = (*cmd)->next;
		data->ex_stat = 127;
		return (0);
	}
	(*cmd)->ok++;
	return (1);
}

int	reset_descrpt(t_data *data)
{
	t_cmd	*cmd;

	if (dup2(data->std_in, STDIN_FILENO) == -1)
		return (perror("dup2 std_in"), -1);
	if (dup2(data->std_out, STDOUT_FILENO) == -1)
		return (perror("dup2 std_out"), -1);
	while (data->fds_c > 3)
		close(data->fds[--data->fds_c]);
	cmd = data->cmd_list;
	while (cmd)
	{
		if (!cmd->bi || !data->ex_stat)
			waitpid(cmd->pid, &data->ex_stat, 0);
		cmd = cmd->next;
	}
	return (0);
}


#include "../minishell.h"

int	manage_pipes(t_cmd *cmd, t_data *data )
{
	if (data->cmd_qty < 2)
		return (0);
	if (cmd->prev)
	{
		data->prev_pipe[0] = data->next_pipe[0];
		if (dup2(data->prev_pipe[0], STDIN_FILENO) == -1)
			return (perror("dup2 prev_pipe"), -1);
		close(data->prev_pipe[0]);
	}
	if (cmd->next)
	{
		if (pipe (data->next_pipe) < 0)
			return (perror("pipe error"), -1);
		if (dup2(data->next_pipe[1], STDOUT_FILENO) == -1)
			return (perror("dup2 next_pipe"), -1);
		close(data->next_pipe[1]);
	}
	else
	{
		if (dup2(data->std_out, STDOUT_FILENO) == -1)
			return (perror("dup2 std_out"), -1);
	}
	return (0);
}

void	save_orig_descrpit(t_data *data)
{
	data->std_in = dup(STDIN_FILENO);
	data->fds[data->fds_c++] = data->std_in;
	data->std_out = dup(STDOUT_FILENO);
	data->fds[data->fds_c++] = data->std_out;
}

void	handle_cmd(t_data *data, t_cmd *cmd)
{
	save_orig_descrpit(data);
	while (cmd)
	{
		if (getcwd(data->cwd, sizeof(data->cwd)) == NULL)
			my_exit(data, "cwd_ errror\n");
		if (!check_cmd(&cmd, data))
			continue ;
		manage_pipes(cmd, data);
		if (!redirect(&cmd, data))
			continue ;
		if (cmd->bi)
			data->ex_stat = builtin(cmd, data);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				exec(data, cmd);
		}
		cmd = cmd->next;
	}
	reset_descrpt(data);
}
