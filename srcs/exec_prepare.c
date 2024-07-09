#include "minishell.h"

char	*get_path(char **envp, char *cmd)
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
		if (!ft_strncmp(cmd->args[0], builtins[i], ft_strlen(cmd->args[0])))
			{
				cmd->bi = 1;
				return i + 1;
			}
		i--;
	}
	return (0);
}

int in_rdr(t_cmd *cmd)
{
	t_token	*file;
	int		i;

	file = cmd->from_file;
	i = 0;

	while(file && file->next)
	{
		cmd->in_fd = open(file->value, O_RDONLY);
		if (cmd->in_fd < 0)
			return (ft_printf("file \"%s\" open error\n", file->value), 0);
		if (file->next)
			close(cmd->in_fd);
	}
	if (file && cmd->in_fd > 0)
	{
		dup2(cmd->in_fd, 0);
		close(cmd->in_fd);
	}
	return (1);
}

int out_rdr(t_cmd *cmd)
{
	t_token	*file;
	int		i;

	file = cmd->from_file;
	i = 0;
	while(file && file->next)
	{
		if (file->P == 2)
			cmd->out_fd = open(file->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (file->P == 1)
			cmd->out_fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->out_fd < 0)
		{
			ft_printf("file \"%s\" error\n", file->value);
			return (0);
		}
		if (file->next)
			close(cmd->in_fd);
	}
	if (file && cmd->in_fd > 0)
	{
		dup2(cmd->in_fd, 0);
		close(cmd->in_fd);
	}
	return (1);
}

int check_cmd(t_cmd **cmd, t_data *data)
{
	if (!is_bltin(*cmd) && !((*cmd)->path = get_path(data->envp, (*cmd)->args[0])))
	{
		printf("\"%s\" is wrong command\n", (*cmd)->args[0]);
		*cmd = (*cmd)->next;
		return (0);
	}
	else
		return (1);
}
int	handle_cmd(t_data *data, t_cmd *cmd)
{
	char	cwd[8192];

    if (getcwd(cwd, sizeof(cwd)) == NULL)       
        return (perror("getcwd error"), 1);
	while(cmd)
	{
		//pipe create/connnect;
		if (!check_cmd(&cmd, data))
			continue;
		if (!in_rdr(cmd) || !out_rdr(cmd))//
			continue;
		if (cmd->bi)
			builtin(cmd, data);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				exec(data, cmd);
			waitpid(-1, NULL, 0); //? where is should be waiting?
		}
			cmd = cmd->next;
	}
		return 0;
 }