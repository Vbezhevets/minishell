/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:39:12 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/04 16:16:51 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, void *from, size_t n)
{
	char	*ptr_from;
	char	*ptr_to;

	if (!to && !from)
		return (to);
	ptr_from = (char *)from;
	ptr_to = (char *)to;
	while (n > 0)
	{
		*ptr_to++ = *ptr_from++;
		n--;
	}
	return (to);
}
