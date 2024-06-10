#include "minishell.h"

//int read_from_u
int		error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

t_data *data_init(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->tok_qty = 0;
    data->tok_list = NULL;
	return(data);
}
void print_tree(t_node *root) 
{
	if (root == NULL) return;
	printf("(");
	print_tree(root->left_node);
	printf(" %s ", root->value);
	print_tree(root->right_node);
	printf(")");
}

int main()
{
	t_data	*data;
	char	*input;

	data = data_init(data);
	// while (1)
	{
		input = readline("Slava Ukraini! 🇺🇦 >"); 
		if (input)
		{
			tokenizer(input, data);
			data->root = climb_test(data->tok_list, 1);
			// parser(data);
		}
		// print_tree(data->root);
	}
	print_tokens(data->tok_list);
	// printf("%s", data->tok_list->next->value);
	exit(0);
}