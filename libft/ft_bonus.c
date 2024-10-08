/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggero <ggero@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:46:58 by ggero             #+#    #+#             */
/*   Updated: 2024/07/06 12:00:53 by ggero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	volatile t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return ((t_list *)list);
}

int	ft_lstsize(t_list *lst)
{
	unsigned int	i;

	i = 0;
	if (lst != NULL)
	{
		i++;
		while (lst->next != NULL)
		{
			lst = lst->next;
			i++;
		}
	}
	return (i);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst != NULL && f != NULL)
	{
		while (lst->next != NULL)
		{
			f(lst->content);
			lst = lst->next;
		}
		f(lst->content);
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
