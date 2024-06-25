#include "minishell.h"
#include <stdio.h>

t_cmd *init_cmd(t_data *data)
{
	t_cmd	*cmd;

	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error("ты пидор!\n");
	// data->cmd[data->cmd_num] = cmd;
	data->cmd_qty++;
	cmd->args = NULL;
	cmd->to_file = NULL;
	cmd->to_to_file = NULL;
	cmd->from_file = NULL;
	// cmd->her_doc = NULL;

	return (cmd);
}
 // може сразу выполнять? нах этот массив комманд
void assign_fild(t_node *node, t_cmd *cmd, int depth)
{
	t_token *token;
	
	token = create_tok(node->value);
	token->P = depth;

	if (node->type == ARG  || node->type == CMD)
		cmd->args = token;
	else if (node->type == TO_FILE)
		cmd->to_file = token;
	else if (node->type == TO_TO_FILE)
		cmd->to_to_file = token;
	else if (node->type == FROM_FILE)
		cmd->from_file = token;
}
t_cmd **add_cmd(t_data *data, int num)
{
	int i;
	t_cmd **old_array;
	t_cmd **new_a;

	old_array = data->cmd;
	i = 0;
	if (num > 0)
	{
		while (i < num)
		{
			new_a[i] = (t_cmd *)malloc(sizeof(t_cmd));
			ft_memcpy(new_a[i], old_array[i], sizeof(t_cmd));
			free(old_array[i]);
			i++;
		}
		new_a[i] = (t_cmd *)malloc(sizeof(t_cmd));
		free(old_array);
		data->cmd_qty++;
	}
	else 

	return (new_a);
}
data->cmd[data->cmd_num++] = init_cmd(data);

void build_cmd(t_node *node, t_data *data, int depth)
{
	t_token	*next_arg;
	
	next_arg = NULL;
	if (data->cmd_num == data->cmd_qty)
		data->cmd[data->cmd_num] = init_cmd(data); // new
	else if (node->type == PIPE)
	{
		data->cmd = add_cmd(data, data->cmd_num++);
		return;	// + handle_pipe();
	}
	if (node->type == ARG  || node->type == CMD)
		next_arg = data->cmd[data->cmd_num]->args;
	else if (node->type == TO_FILE)
		next_arg = data->cmd[data->cmd_num]->to_file;
	else if (node->type == TO_TO_FILE)
		next_arg = data->cmd[data->cmd_num]->to_to_file;
	else if (node->type == FROM_FILE)
		next_arg = data->cmd[data->cmd_num]->from_file;
	// else if (node->type == HEREDOC)
	// 	next_arg = data->cmd[data->cmd_num]->her_doc;
	if (!next_arg)
		assign_fild(node, data->cmd[data->cmd_num], depth);
	else
	{
		while(next_arg && (next_arg)->next)
			next_arg = (next_arg)->next;
		(next_arg)->next = create_tok(node->value);
		(next_arg)->next->P = depth;
	}
}

void travel_tree(t_node *node,  int depth, t_data *data)
{
	if (!node)
		return;
	if (node->left)
		travel_tree(node->left, depth + 1, data);
	if (node->right)
	{
		travel_tree(node->right, depth + 1, data);
	}
	// if (node->type == PIPE)
	// 	return;
	if (node->type > 7 && node->type < 15)
		build_cmd(node, data, depth);
	// printf("%s d: %d =- ", node->value, depth);
}