/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:14:32 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/04 16:16:51 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *to, void *from, size_t n)
{
	unsigned char	*ptr_to;
	unsigned char	*ptr_from;
	size_t			i;

	ptr_to = (unsigned char *)to;
	ptr_from = (unsigned char *)from;
	if (!to && !from)
		return (to);
	if (ptr_to < ptr_from)
	{
		while (n-- > 0)
			*ptr_to++ = *ptr_from++;
	}
	else
	{
		i = 0;
		while (++i <= n)
			ptr_to[n - i] = ptr_from[n - i];
	}
	return (to);
}
