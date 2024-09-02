/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:58:15 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 09:20:06 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(char *s, char c)
{
	int		l;
	char	*p;

	p = s;
	l = 0;
	while (*p && *p != c)
	{
		p++;
		l++;
	}
	return (l);
}

static int	qty(char *s, char c)
{
	int	count;
	int	f;

	count = 0;
	f = 1;
	while (*s)
	{
		if (*s == c)
			f = 1;
		if (*s != c && f == 1)
		{
			f = 0;
			count++;
		}
		s++;
	}
	return (count);
}

static void	free_all(char **new, int w)
{
	while (w > 0)
		free(new[w--]);
}

char	**ft_split(char *s, char c)
{
	int		l;
	int		w;
	char	**new;

	if (s == NULL || !qty(s, c))
		return (NULL);
	new = (char **)malloc((qty(s, c) + 1) * sizeof(char *));
	if (new == 0)
		return (NULL);
	w = 0;
	while (qty(s, c) > 0)
	{
		while (*s == c)
			s++;
		l = ft_length(s, c);
		new[w] = (char *)malloc((l + 1) * sizeof(char));
		if (new[w] == NULL)
			return (free_all(new, w--), free(new), NULL);
		ft_strlcpy(new[w], s, l + 1);
		s = s + l;
		w++;
	}
	new[w] = NULL;
	return (new);
}
