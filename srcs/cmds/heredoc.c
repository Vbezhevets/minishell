/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:26:52 by ggero             #+#    #+#             */
/*   Updated: 2024/08/20 10:27:56 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include "../utils/extra.h"

static void	reset_signal(int prev_quit);

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_quit = SIGINT;
		ft_printf("\n");
	}
}

#define BUF_SZ 100000

static char	*dispatch_size(struct s_read_vars read_vars,
		const char *const delim, bool *is_flushed)
{
	if (read_vars.size == 0)
	{
		*is_flushed = true;
		return (read_vars.buf);
	}
	if (read_vars.size == -1)
	{
		perror(NULL);
		if (read_vars.buf > (char *)10)
			free(read_vars.buf);
		return (NULL);
	}
	if (ft_strncmp(read_vars.buf + read_vars.total_size - 1
			- ft_strlen((char *)delim),
			delim, ft_strlen((char *)delim)) == 0)
	{
		ft_bzero(read_vars.buf + read_vars.total_size - 1
			- ft_strlen((char *)delim),
			ft_strlen((char *)delim) + 1);
		return (read_vars.buf);
	}
	return ((char *)1);
}

static char	*read_indefinitely(const char *const delim, bool *is_flushed,
	int total_size)
{
	char	*buf;
	int		size;
	char	*tmp;

	buf = ft_calloc(BUF_SZ, 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		size = read(STDIN_FILENO, buf + total_size, BUF_SZ - 1 - total_size);
		if (g_quit == SIGINT || size == -1)
		{
			if (buf > (char *)10)
				free(buf);
			g_quit = 0;
			return (NULL);
		}
		total_size += size;
		tmp = dispatch_size((struct s_read_vars){size, total_size, buf}, delim,
				is_flushed);
		if (tmp == (char *)1)
			continue ;
		return (tmp);
	}
}

char	*heredoc_prompt(const char *const delim)
{
	char				*str;
	struct sigaction	sa;
	int					prev_quit;
	bool				is_flushed;

	prev_quit = g_quit;
	g_quit = 0;
	sa.sa_handler = heredoc_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	is_flushed = false;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (write(2, "Signal error\n", 13), NULL);
	str = read_indefinitely(delim, &is_flushed, 0);
	if (!str || g_quit == SIGINT)
		return (NULL);
	reset_signal(prev_quit);
	return (str);
}

static void	reset_signal(int prev_quit)
{
	struct sigaction	sa;

	g_quit = prev_quit;
	sa.sa_handler = generic_sig_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_heredoc(char *delim, t_data *data)
{
	char	*copy;
	char	*joined;
	char	*number;
	int		fd;

	number = ft_itoa(++data->hd);
	joined = ft_strjoin("heredoc_tmp", number);
	fd = open(joined, O_CREAT | O_RDWR | O_TRUNC, 0777);
	free(joined);
	free(number);
	if (fd < 0)
		return ;
	copy = heredoc_prompt(delim);
	if (!copy)
		return ;
	write(fd, copy, ft_strlen(copy));
	close(fd);
	free(copy);
}

int	del_temp_hd(t_data *data)
{
	char	*joined;
	char	*number;

	while (data->hd > 0)
	{
		number = ft_itoa(data->hd);
		joined = ft_strjoin("heredoc_tmp", number);
		free(number);
		if (unlink(joined) < 0)
			return (error(joined, ": del error", data, 1), free(joined), -1);
		free(joined);
		data->hd--;
	}
	return (0);
}
