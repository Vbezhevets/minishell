#include "../minishell.h"

t_cmd	*init_cmd(t_data *data, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (error("alloc errror\n", NULL, data, 12), NULL);
	data->cmd_qty++;
	cmd->args_qty = 0;
	cmd->bi = 0;
	cmd->pid = 0;
	cmd->from_fd = 0;
	cmd->args = NULL;
	cmd->to_file = NULL;
	cmd->to_to_file = NULL;
	cmd->from_file = NULL;
	cmd->her_doc = NULL;
	cmd->next = NULL;
	cmd->prev = prev;
	cmd->path = NULL;
	cmd->ex_stat = 0;
	cmd->ok = 0;
	return (cmd);
}

void	add_cmd(t_cmd *cmd, t_data *data)
{
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = init_cmd(data, cmd);
}

char	**add_cmd_arg(char **old, int *qty, char *str)
{
	int		i;
	char	**new_a;

	new_a = (char **)malloc((*qty + 2) * sizeof(char *));
	if (!new_a)
		return (error("all0c error", NULL, NULL, 2), NULL);
	i = 0;
	while (i < *qty)
	{
		new_a[i] = (char *)malloc(sizeof(char) * (ft_strlen(old[i]) + 1));
		if (!new_a[i])
			return (f_till((new_a), --i), free(new_a), NULL);
		ft_strcpy(new_a[i], old[i]);
		i++;
	}
	if (old)
		ch3to_null(old, NULL, NULL);
	new_a[i] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_a[i])
		return (f_till((new_a), --i), free(new_a), NULL);
	ft_strcpy(new_a[i], str);
	new_a[i + 1] = NULL;
	*qty = *qty + 1;
	return (new_a);
}

t_cmd_field	*create_field(char *input_str, int type)
{
	t_cmd_field	*field;

	field = (t_cmd_field *)malloc(sizeof(t_cmd_field));
	if (!field)
		return (error("alloc errrorrr", NULL, NULL, 2), NULL);
	field->length = ft_strlen(input_str);
	field->value = (char *)malloc((field->length + 1) * sizeof(char));
	if (field->value == NULL)
		return (free(field), NULL);
	ft_strlcpy(field->value, input_str, field->length + 1);
	field->type = type;
	field->next = NULL;
	field->prev = NULL;
	if (type == TO_FILE)
		field->p = 2;
	if (type == TO_TO_FILE)
		field->p = 3;
	if (type == FROM_FILE)
		field->p = 1;
	return (field);
}

void	assign_fild(t_node *node, t_cmd *cmd)
{
	t_cmd_field	*field;

	if (node->type == ARG || node->type == CMD)
		cmd->args = add_cmd_arg(cmd->args, &cmd->args_qty, node->value);
	else if (node->type != HEREDOC)
	{
		field = create_field(node->value, node->type);
		if (node->type == TO_FILE || node->type == TO_TO_FILE)
			cmd->to_file = field;
		else if (node->type == FROM_FILE)
			cmd->from_file = field;
		else
		{
			free(field->value);
			free(field);
		}
	}
}
