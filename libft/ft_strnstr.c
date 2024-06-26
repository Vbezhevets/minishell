/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:38:35 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/27 21:35:27 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *small, size_t n)
{
	size_t	o;
	size_t	i;

	if (*small == '\0')
		return ((char *)big);
	o = 0;
	while (o < n)
	{
		i = 0;
		if (!*(big + o))
			break ;
		while (*(big + o + i) == *(small + i) && (o + i) < n)
		{
			i++;
			if (*(small + i) == '\0')
				return ((char *)(big + o));
		}
		o++;
	}
	return (NULL);
}
