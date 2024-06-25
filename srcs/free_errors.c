#include "minishell.h"



void free_tree(t_node *node)
{
	if (!node)
		return;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	if (node->value && node->type != CMD_NODE && node->type != RDRCT_NODE)
	{	
		free(node->value);
		node->value = NULL;
	}
	free(node);
}

void	free_tok(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token;
		token = token->next;
		// free(temp->value);
		free(temp);
	}
}

void error(char *str)
{
	//free
	printf("%s\n", str);
	exit(1);
}