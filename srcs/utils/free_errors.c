#include "../minishell.h"

void	free_and_null_(char **a)
{
	int	i;

	i = 0;
	if (a != NULL)
	{
		while (a[i] != NULL)
		{
			free(a[i]);
			a[i] = NULL;
			i++;
		}
	}
}

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


// void	free_cmds(t_cmd *cmd)
// {
// 	t_token *temp;

// 	while (cmd)
// 	{
// 		cmd = cmd->next;
// 		free(temp);
// 	}
// }


void free_all(t_data *data)
{
	free_tree(data->tree);
	free_tok(data->tok_list);
	// free_cmds(data->cmd_list);
}

void error(char *str)
{
	//free
	printf("%s\n", str);
	exit(1);
}