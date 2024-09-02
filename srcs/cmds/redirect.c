/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:31:25 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 11:25:24 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rdr(t_cmd_field *file, t_data *data, int drct, int fd)
{
	char	*path;

	while (file)
	{
		path = ft_str3join(data->cwd, "/", file->value);
		if (file->p == 3)
			fd = open(file->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (file->p == 2)
			fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->p == 1)
			fd = open(path, O_RDONLY);
		if (fd < 0)
			return (free(path), error(file->value,
					": No such file or directory", data, 1), 0);
		if (file->next)
			close(fd);
		file = file->next;
		free(path);
	}
	if (fd < 0)
		return (-1);
	if (dup2(fd, drct) < 0)
		return (-1);
	return (close(fd), 1);
}

int	redirect(t_cmd **cmd, t_data *data)
{
	int	result;

	result = 1;
	if ((*cmd)->from_file)
		result = rdr((*cmd)->from_file, data, STDIN_FILENO, -1);
	if ((*cmd)->to_file)
		result = rdr((*cmd)->to_file, data, STDOUT_FILENO, -1);
	if (result <= 0)
		return (*cmd = (*cmd)->next, 0);
	return (result);
}
