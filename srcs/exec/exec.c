/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:20:00 by ggero             #+#    #+#             */
/*   Updated: 2024/08/19 15:18:51 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

int	exec(t_data *data, t_cmd *cmd)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (execve(cmd->path, cmd->args, data->envp) == -1)
	{
		perror("execve error");
		data->ex_stat = 127;
		return (1);
	}
	return (1);
}
