#include "../minishell.h"
#include <complex.h>
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

	i = 6;
	while (i >= 0)
	{
		if (strnlcmp(cmd->args[0], (char *)builtins[i]))
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
	dup2(data->std_in, STDIN_FILENO);
		// return(close(data->std_in), -1);
	dup2(data->std_out, STDOUT_FILENO);
		// return(close(data->std_in), close(data->std_out), -1);
	close(data->std_in);
	close(data->std_out);
	if (data->pipe[0] != -1)
			close (data->pipe[0]);
	if (data->pipe[1] != -1)
			close (data->pipe[1]);
	return (0);
}

int	manage_pipes(t_cmd *cmd, t_data *data )
{
	if (cmd->prev)
	{
		dup2(data->pipe[0], data->std_in);
		close(data->pipe[0]);
		close(data->pipe[1]);
	}
	if (cmd->next)
	{
		if (pipe (data->pipe) < 0)
			return (perror("getcwd error"), -1);
		dup2(data->pipe[1], data->std_out);
		close(data->pipe[1]);
	}
	else 
	{
		dup2(data->std_out, STDOUT_FILENO);
		close(data->std_out);
	}
	return (0);
}

int	close_pipes(t_cmd *cmd, t_data *data)
{
	
// 	if (cmd->prev)
// 	{
// 		close(data->pipe[0]);
// 		close(data->pipe[1]);
// 	}
// 	if (cmd->next)
// 	{
// 		close(data->pipe[0]);
// 		close(data->pipe[1]);
// 	}
}

int	handle_cmd(t_data *data, t_cmd *cmd)
{
	while(cmd)
	{
    	if (getcwd(data->cwd, sizeof(data->cwd)) == NULL)       
        	return (perror("getcwd error"), 1);
		if (!check_cmd(&cmd, data))
		{
			cmd = cmd->next;
			continue;
		}
		if (data->cmd_qty > 1)
			manage_pipes(cmd, data);
		if (!redirect(cmd, data))
		{
			reset_descrpt(data);
			cmd = cmd->next;
			continue;
		}	
		if (cmd->bi)
			builtin(cmd, data);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				exec(data, cmd);
			waitpid(cmd->pid, &cmd->ex_stat, WUNTRACED);	
		}
		cmd = cmd->next;
	}
		reset_descrpt(data);
	return 0;
 } 



