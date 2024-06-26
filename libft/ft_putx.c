/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:32:50 by bvalerii          #+#    #+#             */
/*   Updated: 2024/01/27 21:34:59 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putx_neg(unsigned int n, int *count, int xX)
{
	char	c;

	if (n >= 16)
		ft_putx_neg((n / 16), count, xX);
	*count = *count + 1;
	if (xX == 1)
		c = "0123456789ABCDEF"[n % 16];
	else
		c = "0123456789abcdef"[n % 16];
	write(1, &c, 1);
}

void	ft_putx(int n, int *count)
{
	char	c;

	if (n < 0)
		ft_putx_neg((unsigned int)n, count, 0);
	else
	{
		if (n >= 16)
			ft_putx((n / 16), count);
		*count = *count + 1;
		c = "0123456789abcdef"[n % 16];
		write(1, &c, 1);
	}
}

void	ft_put_x(int n, int *count)
{
	char	c;

	if (n < 0)
		ft_putx_neg((unsigned int)n, count, 1);
	else
	{
		if (n >= 16)
			ft_put_x((n / 16), count);
		*count = *count + 1;
		c = "0123456789ABCDEF"[n % 16];
		write(1, &c, 1);
	}
}

static void	ft_pputx(size_t n, int *count)
{
	char	c;

	if (n >= 16)
		ft_pputx((n / 16), count);
	*count = *count + 1;
	c = "0123456789abcdef"[n % 16];
	write(1, &c, 1);
}

void	ft_putpntr(void *pntr, int *count)
{
	size_t	k;

	if (pntr == 0)
	{
		write(1, "(nil)", 5);
		*count = *count + 5;
	}
	else
	{
		k = (size_t)pntr;
		write(1, "0x", 2);
		*count = *count + 2;
		ft_pputx(k, count);
	}
}
