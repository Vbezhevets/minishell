#include "../minishell.h"
#include <complex.h>
#include <stdio.h>

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
/*
int from_rdr(char *cwd, t_cmd *cmd)
{
	t_token	*file;
	char	*path;

	file = cmd->from_file;
	if (!file)
		return 1;
	while(file)
	{
		path = ft_str3join(cwd, "/", file->value);
		cmd->from_fd = open(path, O_RDONLY);
		if (cmd->from_fd < 0)
			return (free(path), ft_printf("file \"%s\" open error\n", file->value), 0);
		if (file->next)
			close(cmd->from_fd);
		file = file->next;
		free(path);
	}
	if (cmd->from_fd > 0)
	{
		dup2(cmd->from_fd, 0);
		close(cmd->from_fd);
	}
	return (1);
}

int to_rdr(t_cmd *cmd)
{
	t_token	*file;

	file = cmd->to_file;
	if (!file)
		return 1;
	while(file)
	{
		if (file->P == 2)
			cmd->to_fd = open(file->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (file->P == 1)
			cmd->to_fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->to_fd < 0)
			return (ft_printf("file \"%s\" error\n", file->value), 0);
		if (file->next)
			close(cmd->to_fd);
		file = file->next;
	}
	if (cmd->to_fd > 0)
	{
		dup2(cmd->to_fd, 1);
		close(cmd->to_fd);
	}
	return (1);
} */

int is_bltin(t_cmd *cmd)
{
	int i;

	i = 6;
	while (i >= 0)
	{
		if (!ft_strncmp(cmd->args[0], builtins[i], ft_strlen((char *)builtins[i])))
			{
				cmd->bi = 1;
				return i + 1;
			}
		i--;
	}
	return (0);
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

int rdr(t_token *file, char *cwd, t_cmd *cmd, int drct)
{
	char	*path;
	int		fd = 0;

	while(file)
	{
		printf("value %s\n", file->value);
		path = ft_str3join(cwd, "/", file->value);
		if (file->P == 2)
			fd = open(file->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (file->P == 1)
			fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->P == 0)
		{
			printf("trying  %s\n", path );
			if (access(cmd->path, F_OK) == -1) 
			{
				perror("File does not exist");
				free(path);
				return 0;
			}
			fd = open(path, O_RDONLY);
		}
		if (fd < 0)
			return (free(path), ft_printf("file \"%s\" access error\n", file->value), 0);
		if (file->next)
			close(fd);
		file = file->next;
		free(path);
	}
	printf("%d\n", fd);
	if (fd > 0)
	{
		dup2(fd, drct);
		close(fd);
		return(1);
	}
	return (0);
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
		if (cmd->bi)
			builtin(cmd, data);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				// if (from_rdr(cwd, cmd) && to_rdr(cmd))
				if (rdr(cmd->from_file, cwd, cmd, 0) && rdr(cmd->to_file, cwd, cmd, 1))
				{
					exec(data, cmd);
				}
				waitpid(-1, NULL, 0);
				// else 
				// 	printf("bad redirection\n");
			}
		}
		cmd = cmd->next;
	}
		return 0;
 }