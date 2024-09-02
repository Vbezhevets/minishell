/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:20:31 by ggero             #+#    #+#             */
/*   Updated: 2024/04/06 18:21:53 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra.h"
#include <signal.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include "../minishell.h"

int	wait_en_masse(pid_t *running_processes, int last_last)
{
	int	i;
	int	status;

	i = 0;
	status = -999;
	while (running_processes && running_processes[i])
	{
		waitpid(running_processes[i], &status, 0);
		running_processes[i] = 0;
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		i++;
	}
	if (status == -999)
		return (last_last);
	return (status);
}

void	child_init(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	generic_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_quit = SIGINT;
	}
	if (sig == SIGQUIT)
		g_quit = SIGQUIT;
}

void	init_error(bool expr)
{
	if (expr)
	{
		perror("Minishell: init error");
		exit(0);
	}
}

void	init(void)
{
	struct sigaction	sa;
	struct termios		current;
	int					tty_fd;

	sa.sa_handler = generic_sig_handler;
	sa.sa_flags = SA_RESTART;
	sa.sa_restorer = NULL;
	sigemptyset(&sa.sa_mask);
	init_error(sigaction(SIGINT, &sa, NULL) == -1);
	init_error(signal(SIGQUIT, SIG_IGN) == SIG_ERR);
	if (isatty(STDIN_FILENO))
	{
		init_error(tcgetattr(0, &current) == -1);
		tty_fd = open(ttyname(0), O_RDONLY);
		current.c_lflag |= ISIG;
		init_error(tcsetattr(tty_fd, TCSANOW, &current) == -1);
		close(tty_fd);
	}
	init_error(chdir(getenv("HOME")) == -1);
}
