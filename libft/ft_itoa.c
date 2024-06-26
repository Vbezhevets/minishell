/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:16:22 by bvalerii          #+#    #+#             */
/*   Updated: 2023/10/02 14:29:32 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*min_max(int n)
{
	char	*str;

	if (n == 2147483647)
	{
		str = (char *)malloc(11 * sizeof(char));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, "2147483647", 11);
	}
	else
	{
		str = (char *)malloc(12 * sizeof(char));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
	}
	return (str);
}

static	char	*minus_zero(int *n, char *s)
{
	if (*n == 0)
	{
		*s = (char)48;
		s++;
	}
	if (*n < 0)
	{
		*s = '-';
		s++;
		*n = -*n;
	}
	return (s);
}

static	int	dec_count(int n, long int *dec)
{
	int	i;
	int	sign;

	*dec = 1;
	sign = 1;
	i = 0;
	if (n <= 0)
		sign = 2;
	while (n != 0)
	{
		n = n / 10;
		i++;
		*dec = *dec * 10;
	}
	return (i + sign);
}

char	*ft_itoa(int n)
{
	int			r;
	char		*s;
	char		*begin;
	long int	dec;

	if (n == -2147483648 || n == 2147483647)
		begin = min_max(n);
	else
	{
		s = (char *)malloc(dec_count(n, &dec) * sizeof(char));
		if (s == NULL)
			return (NULL);
		begin = s;
		s = minus_zero(&n, s);
		while (dec > 1)
		{
			dec = dec / 10;
			r = n / (int)dec;
			n = n - r * dec;
			*s = (char)r + 48;
			s++;
		}
		*s = '\0';
	}
	return (begin);
}
