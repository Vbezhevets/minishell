/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:03:28 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/27 21:34:46 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchr(char c, int *count)
{
	write(1, &c, 1);
	*count = *count + 1;
}

void	ft_putstr(char *s, int *count)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		*count = *count + 6;
	}
	else
	{
		while (*s != '\0')
		{
			write(1, s, 1);
			*count = *count + 1;
			s++;
		}
	}
}

void	ft_putnbr(long long int n, int *count)
{
	char	c;
	char	m;

	if (n == -9223372036854775807)
	{
		write(1, "−9223372036854775807", 20);
		*count += 20;
	}
	if (n < 0)
	{
		m = '-';
		write(1, &m, 1);
		n = -n;
		*count = *count + 1;
	}
	if (n >= 10)
		ft_putnbr(n / 10, count);
	*count = *count + 1;
	c = '0' + n % 10;
	write(1, &c, 1);
}

void	ft_putunbr(unsigned int n, int *count)
{
	char	c;

	if (n >= 10)
		ft_putunbr(n / 10, count);
	*count = *count + 1;
	c = '0' + n % 10;
	write(1, &c, 1);
}
