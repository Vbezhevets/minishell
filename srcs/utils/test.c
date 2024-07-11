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
