/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:52:47 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/04 16:16:51 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *str, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *) str;
	while (n > 0 && *p != (unsigned char)c)
	{
		p++;
		n--;
	}
	if (n == 0)
		return (NULL);
	return (p);
}
