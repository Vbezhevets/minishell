/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:05:28 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 09:20:18 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *src, char *set)
{
	size_t	i;

	while (ft_strchr(set, *src) && *src)
		src++;
	i = ft_strlen(src);
	while (ft_strchr(set, src[i - 1]))
		i--;
	return (ft_substr(src, 0, i));
}

char	*ft_trimend(char *src, char c)
{
	int	i;

	i = ft_strlen(src);
	while (i >= 0 && src[i] != c)
		i--;
	return (ft_substr(src, i, ft_strlen(src) - 1));
}
