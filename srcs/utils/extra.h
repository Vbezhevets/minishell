/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:20:36 by ggero             #+#    #+#             */
/*   Updated: 2024/08/19 19:20:35 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_H
# define EXTRA_H
# include <termios.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

struct s_read_vars
{
	int		size;
	int		total_size;
	char	*buf;
};

int		wait_en_masse(pid_t *running_processes, int last_last);
void	child_init(void);
void	init_error(bool expr);
void	init(void);
char	*find_command_path(char *command);
bool	is_only_space(char *word);
char	*ft_strjoin_frees1(char *s1, char *s2);
char	*copy_skip(char *const str, const char *const to_skip);
void	generic_sig_handler(int sig);
#endif
