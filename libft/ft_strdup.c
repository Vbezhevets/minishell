/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:20:58 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/19 15:32:58 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		size;
	char	*dst;
	char	*src;
	char	*start;

	src = (char *)s;
	size = ft_strlen(src);
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
		return (ft_printf("alloc err0r\n"), NULL);
	if (dst != NULL)
	{
		start = dst;
		while (*src)
		{
			*dst = *src;
			src++;
			dst++;
		}
		*dst = '\0';
		return (start);
	}
	return (NULL);
}
