int rdr(t_token *file, char *cwd, t_cmd *cmd, int drct)
{
	char	*path;
	int		fd;

	while(file)
	{
		path = ft_str3join(cwd, "/", file->value);
		if (file->P == 2)
			fd = open(file->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (file->P == 1)
			fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (rdr == 0)
			fd = open(path, O_RDONLY);
		if (fd < 0)
			return (free(path), ft_printf("file \"%s\" error\n", file->value), 0);
		if (file->next)
			close(fd);
		file = file->next;
		free(path);
	}
	if (fd > 0)
	{
		dup2(cmd->fd, drct);
		close(cmd->fd);
	}
	return (1);
}

int redirect(cwd, cmd)
{
	if (cmd->from_file)
		return (rdr(cmd->from_file, cwd, cmd, 0));
	if (cmd->to_file)
		return (rdr(cmd->to_file, cwd, cmd, 1));
	return(1);
}