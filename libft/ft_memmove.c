/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:14:32 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 11:18:24 by ggero            ###   ########.fr       */
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
	if (!to || !from)
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
