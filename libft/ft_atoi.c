/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:30:50 by bvalerii          #+#    #+#             */
/*   Updated: 2024/02/15 16:30:30 by v                ###   ########.fr       */
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

	n = 0;
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
