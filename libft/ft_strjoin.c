/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:48:44 by bvalerii          #+#    #+#             */
/*   Updated: 2024/07/23 15:39:11 by bvalerii         ###   ########.fr       */
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
	if (a)
	{
		while (*a != '\0')
			(*new++ = *a++);
	}
	if (b)
	{
		while (*b != '\0')
			(*new++ = *b++);
	}
	if (c)
	{
		while (*c != '\0')
			*new++ = *c++;
	}
	*new = '\0';
	return (ret);
}
char	*free_join(char *a, char *b)
{
	char	*new;
	char	*ret;
	char	*beg_a;

	beg_a = a;
	new = malloc((ft_strlen(a) + ft_strlen(b) + 1)
			* sizeof(char));
	if (new == NULL)
		return (NULL);
	ret = new;
	if (a)
	{
		while (*a != '\0')
			(*new++ = *a++);
	}
	if (b)
	{
		while (*b != '\0')
			(*new++ = *b++);
	}
	if (beg_a)
		free(beg_a);
	a = NULL;
	*new = '\0';
	return (ret);
}