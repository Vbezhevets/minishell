#include "../minishell.h"

int rdr(t_cmd_field *file, t_data *data, t_cmd *cmd, int drct)
{
	char	*path;
	int		fd;

	fd = -1;
	while(file)
	{
		path = ft_str3join(data->cwd, "/", file->value);
		if (file->P == 3)
			fd = open(file->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (file->P == 2)
				fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->P == 1)
				fd = open(path, O_RDONLY);
		if (fd < 0)
			return (free(path), printf("file \"%s\" access error\n", file->value), 0);
		if (file->next)
			close(fd);
		file = file->next;
		free(path);
	}
	if (fd > 0)
	{
		if (dup2(fd, drct) < 0)
			return (-1);
		close(fd);
	}
	return (1);
}

int	redirect(t_cmd **cmd, t_data *data)
{
	int result;

	result =1;
	
	if ((*cmd)->from_file)
	{
		if (data->pipe[0] != -1)
			close (data->pipe[0]);
		dup2(data->std_in, STDIN_FILENO);
		result = rdr((*cmd)->from_file, data, *cmd, STDIN_FILENO);
	}
	if ((*cmd)->to_file)
	{
		if (data->pipe[1] != -1)
			close (data->pipe[1]);
		dup2(data->std_out, STDOUT_FILENO);
		result = rdr((*cmd)->to_file, data, *cmd, STDOUT_FILENO);
	}
	if (result <= 0) 	
		return (*cmd = (*cmd)->next, 0);
	return (result);
}