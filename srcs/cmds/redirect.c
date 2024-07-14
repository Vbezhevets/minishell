#include "../minishell.h"

int rdr(t_cmd_field *file, char *cwd, t_cmd *cmd, int drct)
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
		if (file->P == 0)
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
		dup2(fd, drct);
		close(fd);
	}
	return (1);
}
