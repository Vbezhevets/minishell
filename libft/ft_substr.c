/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:28:11 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/04 16:14:40 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*begin;
	char	*ret;
	size_t	size;

	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		size = ft_strlen(s) - start;
	else
		size = len;
	while (start--)
		s++;
	ret = malloc((size + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	begin = ret;
	while (size-- > 0)
		*ret++ = *(char *)s++;
	*ret = '\0';
	return (begin);
}
