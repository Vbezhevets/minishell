#include "minishell.h"

//int read_from_u
int		error(char *str)
{
	//free
	printf("%s\n", str);
	exit(1);
}

t_data *data_init(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->tok_quantity = 0;
    data->tok_list = NULL;
	return(data);
}
// void print_tree(t_node *root) 
// {
// 	if (root == NULL) return;
// 	printf("(");
// 	print_tree(root->left);
// 	printf(" %s ", root->value);
// 	print_tree(root->right);
// 	printf(")");
// }

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
			parser(data);
		}
		// print_tree(data->root);
	}
	// print_tokens(data->tok_list);
	exit(0);
}

