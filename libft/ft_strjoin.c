/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:48:44 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/04 15:33:24 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*one;
	char	*two;
	char	*new;
	char	*ret;

	one = (char *) s1;
	two = (char *) s2;
	new = malloc((ft_strlen(one) + ft_strlen(two) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	ret = new;
	while (*one)
	{
		*new = *one;
		new++;
		one++;
	}
	while (*two)
	{
		*new = *two;
		new++;
		two++;
	}
	*new = '\0';
	return (ret);
}

char	*ft_str3join(char *a, char *b, char *c)
{
	char	*new;
	char	*ret;

	new = malloc((ft_strlen(a) + ft_strlen(b) + ft_strlen(c) + 1)
			* sizeof(char));
	if (new == NULL)
		return (NULL);
	ret = new;
	while (*a != '\0')
		(*new++ = *a++);
	while (*b != '\0')
		(*new++ = *b++);
	while (*c != '\0')
		*new++ = *c++;
	*new = '\0';
	return (ret);
}