/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:30:50 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/08 15:10:28 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_plus(char *nptr)
{
	int	f;

	f = 1;
	while (*nptr == 43)
	{
		nptr++;
		f--;
	}
	return (f);
}

int	ft_atoi( char *nptr)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || (*nptr == 32))
		nptr++;
	if (ft_plus((char *)nptr) < 0)
		return (0);
	if (*nptr == 43)
		nptr++;
	if (*nptr == 45 && (*(nptr - 1) != 43))
	{
		sign = -1;
		nptr++;
	}
	while ((*nptr) && (*nptr > 47) && (*nptr < 58))
	{
		n = *nptr - 48;
		i = i * 10 + n;
		nptr++;
	}
	return (i * sign);
}
