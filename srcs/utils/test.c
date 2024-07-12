#include "../minishell.h"

void print_token_list(t_token *token) {
    while (token != NULL) {
        printf(" %d |", token->type);
        printf(" %s\n", token->value);

        token = token->next;
    }
    printf("\n");
}

void print_tree(t_node *node, int intent)
{
	if (!node)
		return;
	int i = intent;


	if (node->left)
	{	
		print_tree(node->left, intent + 1);
	}
	while (i > 0)
	{
		printf("+---");
		i--;
	}
	printf("%s\n", node->value);
	if (node->right)
	{
		// printf("right");
		print_tree(node->right, intent + 1);
	}
}

/*
void print_cmd_fields(t_cmd **cmd_array, int cmd_count) {
    for (int i = 0; i < cmd_count; i++) {
        printf("Command %d:\n", i + 1);
        t_cmd *cmd = cmd_array[i];

        // if (cmd->in != 0)
        //     printf("  in: %d\n", cmd->in);
        // if (cmd->out != 0)
        //     printf("  out: %d\n", cmd->out);
        if (cmd->to_file != NULL) {
            printf("  to_file:");
            print_token_list(cmd->to_file);
        }
        if (cmd->to_to_file != NULL) {
            printf("  to_to_file:");
            print_token_list(cmd->to_to_file);
        }
        if (cmd->from_file != NULL) {
            printf("  from_file:");
            print_token_list(cmd->from_file);
        }
        if (cmd->args != NULL) {
            printf("  args:");
            print_token_list(cmd->args);
        }
        if (cmd->her_doc != NULL)
            printf("  her_doc: %s\n", cmd->her_doc);
    }
} */

/*
int from_rdr(char *cwd, t_cmd *cmd)
{
	t_token	*file;
	char	*path;

	file = cmd->from_file;
	if (!file)
		return 1;
	while(file)
	{
		path = ft_str3join(cwd, "/", file->value);
		cmd->from_fd = open(path, O_RDONLY);
		if (cmd->from_fd < 0)
			return (free(path), ft_printf("file \"%s\" open error\n", file->value), 0);
		if (file->next)
			close(cmd->from_fd);
		file = file->next;
		free(path);
	}
	if (cmd->from_fd > 0)
	{
		dup2(cmd->from_fd, 0);
		close(cmd->from_fd);
	}
	return (1);
}

int to_rdr(t_cmd *cmd)
{
	t_token	*file;

	file = cmd->to_file;
	if (!file)
		return 1;
	while(file)
	{
		if (file->P == 2)
			cmd->to_fd = open(file->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (file->P == 1)
			cmd->to_fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->to_fd < 0)
			return (ft_printf("file \"%s\" error\n", file->value), 0);
		if (file->next)
			close(cmd->to_fd);
		file = file->next;
	}
	if (cmd->to_fd > 0)
	{
		dup2(cmd->to_fd, 1);
		close(cmd->to_fd);
	}
	return (1);
} */