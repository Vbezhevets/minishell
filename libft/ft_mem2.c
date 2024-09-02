/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:16:39 by ggero             #+#    #+#             */
/*   Updated: 2024/07/18 21:16:40 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memdup(void *src, size_t n)
{
	size_t	i;
	void	*dest;

	dest = malloc(n);
	i = 0;
	while (i < n && dest != NULL && src != NULL)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}
