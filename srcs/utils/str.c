/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:32:14 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/19 16:32:36 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty(char *str)
{
	if (!ft_strlen(str))
		return (1);
	while (*str)
	{
		if (!ft_strchr(DELIM, *str))
			return (0);
		str++;
	}
	return (1);
}

int	strnlcmp(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	if ((ft_strlen(str1) == ft_strlen(str2))
		&& !ft_strncmp(str1, str2, ft_strlen(str2)))
		return (1);
	return (0);
}

int	ft_strset(char *str, char *set)
{
	int		i;

	if (!str || !set)
		return (0);
	i = 0;
	while (*set)
	{
		while (str[i])
		{
			if (str[i] == *set)
				return (1);
			i++;
		}
		set++;
		i = 0;
	}
	return (i);
}

int	chr_mlc(char ***arr, int i)
{
	*arr = malloc((sizeof(char *) * (i)));
	if (!*arr)
		return (0);
	return (1);
}

int	splt_mlc(char ***splited, char *to_split, char delim)
{
	*splited = ft_split(to_split, delim);
	if (!*splited)
		return (0);
	return (1);
}
