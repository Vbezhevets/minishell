/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:31:12 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/27 21:35:37 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	ret_size;
	size_t	src_size;
	size_t	dst_size;

	src_size = (size_t)ft_strlen(src);
	dst_size = (size_t)ft_strlen(dst);
	if (n < dst_size)
		ret_size = n + src_size;
	else
		ret_size = src_size + dst_size;
	if (n == 0)
		return (ret_size);
	i = 0;
	while (*dst != '\0')
	{
		dst++;
		i++;
	}
	while (*src != '\0' && i++ < n - 1)
		*dst++ = *src++;
	*dst = '\0';
	return (ret_size);
}
