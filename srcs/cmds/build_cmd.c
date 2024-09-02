#include "../minishell.h"

t_cmd_field	*add_hdfile(int heredoc_count)
{
	char		*number;
	char		*path;
	t_cmd_field	*field;

	number = ft_itoa(heredoc_count);
	path = ft_strjoin("heredoc_tmp", number);
	free(number);
	field = create_field(path, FROM_FILE);
	free(path);
	return (field);
}

void	build_cmd(t_node *node, t_data *data, t_cmd *cmd, t_cmd_field *exist)
{
	if (data->cmd_qty == 0)
		data->cmd_list = init_cmd(data, NULL);
	cmd = data->cmd_list;
	while (cmd && cmd->next)
		cmd = cmd->next;
	if ((node->type == TO_FILE || node->type == TO_TO_FILE) && cmd)
		exist = cmd->to_file;
	else if (node->type == HEREDOC && cmd)
	{
		handle_heredoc(node->value, data);
		cmd->from_file = add_hdfile(data->hd);
	}
	if (node->type == FROM_FILE && cmd)
		exist = cmd->from_file;
	if (!exist || node->type == ARG || node->type == CMD)
		assign_fild(node, cmd);
	else
	{
		while (exist && exist->next)
			exist = exist->next;
		exist->next = create_field(node->value, node->type);
	}
}

void	travel_tree(t_node *node, int depth, t_data *data)
{
	if (!node)
		return ;
	if (node->left)
		travel_tree(node->left, depth + 1, data);
	if (node->type == PIPE)
		add_cmd(data->cmd_list, data);
	if (node->right)
		travel_tree(node->right, depth + 1, data);
	if (node->type > 9 && node->type <= 16)
		build_cmd(node, data, NULL, NULL);
}
