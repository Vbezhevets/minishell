/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:41:58 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/19 16:42:05 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tree(t_node *node, int intent)
{
	int	i;

	if (!node)
		return ;
	i = intent;
	if (node->left)
	{
		print_tree(node->left, intent + 1);
	}
	while (i > 0)
	{
		printf("+---");
		i--;
	}
	printf("%s\n", node->value);
	if (node->right)
		print_tree(node->right, intent + 1);
}
