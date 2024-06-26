/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:43:05 by bvalerii          #+#    #+#             */
/*   Updated: 2024/02/18 20:06:39 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_and_null(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*new;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new == NULL)
		return (free_and_null(&s1), free_and_null(&s2), NULL);
	ret = new;
	while (s1 && s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free_and_null(&s1);
	free_and_null(&s2);
	return (ret);
}

int	check_newline(char *remainder)
{
	int	i;

	i = 0;
	if (!remainder)
		return (0);
	while (remainder[i] != '\n' && remainder[i])
		i++;
	if (remainder[i] == '\n')
		return (i);
	return (0);
}

char	*extract_until_n(char **remain, int i, int j)
{
	char	*ret_str;
	char	*temp;

	if (*remain == NULL)
		return (NULL);
	if (**remain == '\0')
		return (free_and_null(remain), NULL);
	while ((*remain)[i] != '\n' && (*remain)[i])
		i++;
	if ((*remain)[i] == '\n')
		i++;
	ret_str = (char *)malloc(i + 1);
	if (!ret_str)
		return (free_and_null(remain), NULL);
	while (++j < i)
		ret_str[j] = (*remain)[j];
	ret_str[j] = '\0';
	temp = malloc((ft_strlen(*remain) - i + 1) * sizeof(char));
	if (temp == NULL)
		return (free(ret_str), free_and_null(remain), NULL);
	ft_strcpy(temp, (*remain + i));
	return (free_and_null(remain), *remain = temp, ret_str);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	int			bytes_read;

	if (BUFFER_SIZE <= 0 || fd <= 0)
		return (free(remainder), remainder = NULL);
	while (1)
	{
		if (check_newline(remainder))
			return (extract_until_n(&remainder, 0, -1));
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (free_and_null(&remainder), NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free_and_null(&buffer), extract_until_n(&remainder, 0, -1));
		if (bytes_read == -1)
			return (free_and_null(&buffer), free_and_null(&remainder), NULL);
		buffer[bytes_read] = '\0';
		remainder = ft_my_strjoin(remainder, buffer);
	}
}
/*
int main ()
{
int		fd;
char	*b = "1";
char	*file = "./2.txt";
//char *str;

fd = open(file, O_RDONLY);
while (b)
	{
	printf("%s", b = get_next_line(fd));
	}
}*/