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

void	f_till(char **a, int c)
{
	int	i;

	i = 0;
	if (a != NULL)
	{
		while (i <= c && a[i] != NULL)
		{
			free(a[i]);
			a[i] = NULL;
			i++;
		}
	}
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	if (node && node->value && node->type != CMD_NODE
		&& node->type != RDRCT_NODE)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}

void	fnl(void *pntr)
{
	if (pntr)
	{
		free(pntr);
		pntr = NULL;
	}
}

void	free_tok(t_token *token)
{
	t_token	*temp;

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
		temp = (NULL);
	}
}

void	free_var(t_var *var)
{
	t_var	*temp;

	while (var)
	{
		temp = var;
		var = var->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		if (temp->key)
		{
			free(temp->key);
			temp->key = NULL;
		}
		free(temp);
	}
}

void	free_field(t_cmd_field	*field)
{
	t_cmd_field	*temp;

	if (!field)
		return ;
	while (field)
	{
		temp = field;
		field = field->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
	}
}

void	free_cmds(t_cmd *cmd, t_cmd *temp)
{
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		if (temp->to_to_file)
			free_field(temp->to_to_file);
		if (temp->to_file)
			free_field(temp->to_file);
		if (temp->from_file)
			free_field(temp->from_file);
		if (temp->path)
		{
			free(temp->path);
			temp->path = NULL;
		}
		if (temp->args)
		{
			free_and_null_(temp->args);
			free(temp->args);
			temp->args = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->tree)
		free_tree(data->tree);
	if (data->tok_list)
		free_tok(data->tok_list);
	if (data->cmd_list)
		free_cmds(data->cmd_list, NULL);
	zeroing_data(data);
	data->f = 1;
}

void	ch3to_null(char **one, char **two, char **three)
{
	if (one)
	{
		free_and_null_(one);
		free(one);
	}
	if (two)
	{
		free_and_null_(two);
		free(two);
	}
	if (three)
	{
		free_and_null_(three);
		free(three);
	}
}

void	error(char *s1, char *s2, t_data *data, int e)
{
	if (s2)
	{
		write(2, s1, ft_strlen(s1));
		write(2, s2, ft_strlen(s2));
	}
	else
		write(2, s1, ft_strlen(s1));
	write(2, "\n", 1);
	if (data)
		data->ex_stat = e;
}
