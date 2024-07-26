#include "../minishell.h"
#include <stdio.h>

t_cmd *init_cmd(t_data *data, t_cmd *prev)
{
	t_cmd	*cmd;

	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error("ahh!\n");
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
/*
void *add_to_array(void *old_a, int *qty, void *elem, size_t size)
{
	int	i;
	void *new_a;

	new_a = malloc((*qty + 2) * sizeof(size));
	i = 0;
	while (i < *qty)
	{
		new_a[i] = malloc(sizeof(old_a[i]));
		//if (!new_a[i])
		memcpy(new_a[i], old_a[i], sizeof(void));
		// free(old[i]);
		// old[i] = NULL;
		i++;
	}
	new_a[i] = (void *)malloc(sizeof(old_a[i]));
	memcpy(new_a[i], old_a[i], sizeof(void));
	new_a[i + 1] = NULL;
    *qty = *qty + 1;
	return (new_a);
} */

char **add_cmd_arg(char **old, int *qty, char *str)
{
	int i;
	char **new_a;

	new_a = (char **)malloc((*qty + 2) * sizeof(char*));
    // if (!new_a)
	i = 0;
	while (i < *qty)
	{
		new_a[i] = (char *)malloc(sizeof(char) * (ft_strlen(old[i]) + 1));
		//if (!new_a[i])
		ft_strcpy(new_a[i], old[i]);
		// free(old[i]);
		// old[i] = NULL;
		i++;
	}
	if(old)
		free_and_null_(old);
	new_a[i] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	//if
	ft_strcpy(new_a[i], str);
	new_a[i + 1] = NULL;
    *qty = *qty + 1;
	return (new_a);
}

t_cmd_field *create_field(char *input_str, int type)
{
	t_cmd_field *field;

	field = (t_cmd_field *)malloc(sizeof(t_cmd_field));
	// if (!field->value)
	// 	return (free_tok(field), exit(1), NULL); //handle exit in error.c
	field->length = ft_strlen(input_str);
	field->value = (char *)malloc((field->length + 1) * sizeof(char));
	// if (field->value == NULL)
	// 	return (free_tok(field), exit(1), NULL); //handle exit
	ft_strlcpy(field->value, input_str, field->length + 1);
    field->type = type;
	field->next = NULL;
	field->prev = NULL;
	if (type == TO_FILE)
		field->P = 2;
    if (type == TO_TO_FILE)
		field->P = 3;
    if (type == FROM_FILE)
		field->P = 1;
	return (field);
}

void assign_fild(t_node *node, t_cmd *cmd)
{
	t_cmd_field *field;
	
	if (node->type == ARG  || node->type == CMD)
		handle_cmd_args(node, cmd);
	else
	{
		field = create_field(node->value, node->type); // check ""
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
	while (cmd && cmd->next)
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

void handle_cmd_args(t_node *node, t_cmd *cmd)
{
	char 	*arg;
	
	// ft_strchr(node->value, '='); //!!!!!!!!!!!!!!!!

	// arg = handle_quotes(node->value);

    cmd->args = add_cmd_arg(cmd->args, &cmd->args_qty, node->value);


	
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


