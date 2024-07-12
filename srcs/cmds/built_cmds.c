#include "../minishell.h"
#include <stdio.h>

t_cmd *init_cmd(t_data *data, t_cmd *prev)
{
	t_cmd	*cmd;

	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error("ты пидор!\n");
	// data->cmd[data->cmd_num] = cmd;
	data->cmd_qty++;
	cmd->args_qty = 0;
	cmd->bi = 0;
	cmd->from_fd = 0;
	cmd->interp = 1; //
	cmd->args = NULL;
	cmd->to_file = NULL;
	// cmd->to_to_file = NULL;
	cmd->from_file = NULL;
	cmd->her_doc = NULL;
	cmd->next = NULL;
	cmd->prev = prev;

	return (cmd);
}

void add_cmd(t_cmd *cmd, t_data *data)
{
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = init_cmd(data, cmd);
}

void assign_fild(t_node *node, t_cmd *cmd)
{
	t_cmd_field *field;
	
	if (node->type == ARG  || node->type == CMD)
		handle_cmd_args(node, cmd);
	else
	{
		field = create_field(node->value, node->type);
		if (node->type == TO_FILE || node->type == TO_TO_FILE)
			cmd->to_file = field;
		else if (node->type == FROM_FILE)
			cmd->from_file = field;
	}
}

void build_cmd(t_node *node, t_data *data, t_cmd *cmd, t_cmd_field *exist_arg)
{
	if (data->cmd_qty == 0)
		data->cmd_list = init_cmd(data, NULL); // new
	cmd = data->cmd_list;
	while (cmd->next)
		cmd = cmd->next;
	if (node->type == TO_FILE || node->type == TO_TO_FILE)
		exist_arg = cmd->to_file;
	else if (node->type == FROM_FILE)
		exist_arg = cmd->from_file;
	// else if (node->type == HEREDOC)
	// 	exist_arg = data->cmd[data->cmd_num]->her_doc;
	if (!exist_arg || node->type == ARG || node->type == CMD)
		assign_fild(node, cmd);
	else
	{
		while(exist_arg && exist_arg->next)
			exist_arg = exist_arg->next;
		exist_arg->next = create_field(node->value, node->type);
	}
}

void travel_tree(t_node *node,  int depth, t_data *data)
{
	if (!node)
		return;
	if (node->left)
		travel_tree(node->left, depth + 1, data);
	if (node->type == PIPE)
		add_cmd(data->cmd_list, data); // nandle |
	if (node->right)
		travel_tree(node->right, depth + 1, data);
	if (node->type > 9 && node->type < 16)
		build_cmd(node, data, NULL, NULL);
}