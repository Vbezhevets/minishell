#include "minishell.h"

t_cmd *init_cmd(t_data *data)
{
	t_cmd	*cmd;
	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error("ты пидор!\n");
	data->cmd[data->cmd_qty] = cmd;
	cmd->args = NULL;
	cmd->to_file = NULL;
	cmd->to_to_file = NULL;
	cmd->from_file = NULL;
	// cmd->her_doc = NULL;

	return (cmd);
}
 // може сразу выполнять? нах этот массив комманд
void build_cmd(t_node *node, t_data *data, int depth)
{
	t_token	**next_arg;
	
	next_arg = NULL;
	if (node->type == CMD) //why does the cmd become ARG!)))!?!!?!?!?!
		data->cmd[data->cmd_qty]->args = create_tok(node->value);
	else if (node->type == PIPE)
		data->cmd[data->cmd_qty++] = init_cmd(data);	// + handle_pipe();
	else
	{
		if (node->type == ARG)
			next_arg = &data->cmd[data->cmd_qty]->args;
		else if (node->type == TO_FILE)
			next_arg = &data->cmd[data->cmd_qty]->to_file;
		else if (node->type == TO_TO_FILE)
			next_arg = &data->cmd[data->cmd_qty]->to_to_file;
		else if (node->type == FROM_FILE)
			next_arg = &data->cmd[data->cmd_qty]->from_file;
		// else if (node->type == HEREDOC)
		// 	next_arg = data->cmd[data->cmd_qty]->her_doc;
		while(*next_arg)
			*next_arg = (*next_arg)->next;
		*next_arg = create_tok(node->value);
		(*next_arg)->P = depth;
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