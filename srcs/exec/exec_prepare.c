#include "../minishell.h"
#include <stdio.h>

char	*get_cmd_path(char **envp, char *cmd)
{
	int		i;
	char	**pathes;
	char	*path;

	pathes = NULL;
	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) && envp[i])
		i++;
	pathes = ft_split(envp[i] + 5, ':');
	if (!pathes)
		return (ft_printf("split error\n"), NULL);
	i = 0;
	while (pathes[i])
	{
		path = ft_str3join(pathes[i], "/", cmd);
		if (!access(path, F_OK)) //success
			return (free_and_null_(pathes), free(pathes), path);
		free(path);
		i++;
	}
	free_and_null_(pathes);
	free(pathes);
	return (NULL);
}

int is_bltin(t_cmd *cmd)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		if (strnlcmp(cmd->args[0], (char *)BUILTINS[i]))
			{
				cmd->bi = 1;
				return (i + 1);
			}
		i--;
	}
	return (0);
}

int check_cmd(t_cmd **cmd, t_data *data)
{
	char *just_name;
	
	// if (ft_strchr((*cmd)->args[0], '/'))
	// {
	// 	just_name = ft_trimend((*cmd)->args[0], '/');
 	// 	free((*cmd)->args[0]);
	// 	(*cmd)->args[0] = just_name;
	// }
	if (!is_bltin(*cmd) && 
		!((*cmd)->path = get_cmd_path(data->envp, (*cmd)->args[0])))
		{
			printf("\"%s\" is wrong command\n", (*cmd)->args[0]);
			*cmd = (*cmd)->next;
			return (0);
		}
	else
		return (1);
}

int reset_descrpt(t_data *data)
{
	// if (data->cmd_qty < 2)
	// 	return (0);
	if (dup2(data->std_in, STDIN_FILENO) == -1)
		return perror("dup2 std_in"), -1;
	if (data->std_out != STDOUT_FILENO)
		if (dup2(data->std_out, STDOUT_FILENO) == -1)
			return perror("dup2 std_out (from reset)"), -1; 
	if (data->std_in != -1)
        close(data->std_in);
    if (data->std_out != -1)
        close(data->std_out);
	return (0);
}


int	manage_pipes(t_cmd *cmd, t_data *data )
{
	if (data->cmd_qty < 2)
		return (0);
	if (cmd->prev)
	{
		data->prev_pipe[0] = data->next_pipe[0];
		if (dup2(data->prev_pipe[0], STDIN_FILENO) == -1)
			return perror("dup2 prev_pipe"), -1;
		close(data->prev_pipe[0]);
	}
	if (cmd->next)
	{
		if (pipe (data->next_pipe) < 0)
			return (perror("pipe error"), -1);
		if (dup2(data->next_pipe[1], STDOUT_FILENO) == -1)
			return perror("dup2 next_pipe"), -1;
		close(data->next_pipe[1]);
	}
	else 
	{
		if (dup2(data->std_out, STDOUT_FILENO) == -1)
			return perror("dup2 std_out"), -1;
	}
	return (0);
}

int	handle_cmd(t_data *data, t_cmd *cmd)
{
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	while(cmd)
	{
		if (getcwd(data->cwd, sizeof(data->cwd)) == NULL)       
			return (perror("getcwd error"), 1);
		if (!check_cmd(&cmd, data))
			continue;
		manage_pipes(cmd, data);
		if (!redirect(&cmd, data))
			continue;
		if (cmd->bi)
			data->ex_stat = builtin(cmd, data);
		else 
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				exec(data, cmd);
			waitpid(cmd->pid, &cmd->ex_stat, WUNTRACED);
		}
		if (!cmd->next)
			data->ex_stat = cmd->ex_stat;
		cmd = cmd->next;
	}
		reset_descrpt(data);
	return (0);
 } 



