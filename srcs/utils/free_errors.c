#include "../minishell.h"
#include <unistd.h>

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
	if (node && node->value && node->type != CMD_NODE && node->type != RDRCT_NODE)
	{	
		// free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}

void	free_tok(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token;
		token = token->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
	}
}

void	free_field(t_cmd_field	*field)
{
	t_cmd_field	*temp;

	if (!field)
		return;
	while (field)
	{
		temp = field;
		field = field->next;
		if(temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd *temp;

	while (cmd)
	{	
		temp = cmd;
		cmd = cmd->next;
		free_field(temp->to_to_file);
		free_field(temp->to_file);
		free_field(temp->from_file);
		// free(temp->her_doc);
		if (temp->path)
			free(temp->path);
		temp->path = NULL;
		free_and_null_(temp->args);
		if (temp->args)
			free(temp->args);
		free(temp);
		temp = NULL;
	}
}


void free_all(t_data *data)
{
	if (data->tree)
	{
		free_tree(data->tree);
		// free(data->tree);
		// data->tree = NULL;
	}
	if (data->tok_list)
	{
		free_tok(data->tok_list);
		// free(data->tok_list);
		// data->tok_list = NULL;
	}
	if (data->cmd_list)
	{
		free_cmds(data->cmd_list);
		// free(data->cmd_list);
		// data->cmd_list = NULL;	
	}
}

void error(char *s1, char *s2)
{
	//free
	if (s2)
	{
		write(2, "\"", 1);
		write(2, s1, ft_strlen(s1));
		write(2, "\" ", 2);
		write(2, s2, ft_strlen(s2));
	}
	else 
		write(2, s1, ft_strlen(s1));
	write(2, "\n", 1);
}
