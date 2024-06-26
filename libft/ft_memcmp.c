/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:55:58 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/04 16:16:51 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	int				res;
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	p_s1 = (unsigned char *) s1;
	p_s2 = (unsigned char *) s2;
	res = 0;
	while (n > 0 && res == 0)
	{
		res = *p_s1 - *p_s2;
		p_s1++;
		p_s2++;
		n--;
	}
	return (res);
}
