/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:32:18 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/19 19:32:21 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_str	*add_chunk( t_str *prev, char *str, int start, int end)
{
	t_str	*chunk;

	chunk = (t_str *)malloc(sizeof(t_str));
	if (!chunk)
		return (error("all3c error", NULL, NULL, 2), NULL);
	chunk->str = ft_substr(str, start, end - start);
	if (!chunk)
		return (free(chunk), error("all4c error", NULL, NULL, 2), NULL);
	if (prev)
	{
		prev->next = chunk;
		chunk->prev = prev;
	}
	else
		chunk->prev = NULL;
	chunk->next = NULL;
	return (chunk);
}

char	*sum_str(t_str *chunk)
{
	t_str	*prev;
	t_str	*next;
	char	*res;

	res = NULL;
	prev = chunk;
	while (prev && prev->prev)
		prev = prev->prev;
	next = prev;
	while (next)
	{
		res = free_join(res, next->str);
		free(next->str);
		next->str = NULL;
		prev = next;
		next = next->next;
		free(prev);
	}
	return (res);
}

char	is_q(char c)
{
	if (c == Q)
		return (Q);
	if (c == QQ)
		return (QQ);
	else
		return (0);
}

char	*get_rid_q(char *str, int i, int start, t_str *chunk)
{
	char	q;

	while (str[i])
	{
		while (str[i] && !is_q(str[i]))
			i++;
		chunk = add_chunk(chunk, str, start, i);
		if (!str[i])
			break ;
		if (is_q(str[i]))
		{
			q = str[i];
			i++;
			start = i;
			while (str[i] && str[i] != q)
				i++;
		}
		chunk = add_chunk(chunk, str, start, i);
		i++;
		start = i;
	}
	return (sum_str(chunk));
}
