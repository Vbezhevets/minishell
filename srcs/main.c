#include "minishell.h"

//int read_from_u



t_data *init_data(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->tok_quantity = 0;
	data->cmd_qty = 0;
	data->tok_list = NULL;
	data->cmd = (t_cmd **)malloc(sizeof(t_cmd *));
	return(data);
}


int main() 
{
	t_data	*data;	
	char	*input;

	while (1)
	{
		data = init_data(data);
		input = readline("Slava Ukraini! 🇺🇦 >"); 
		if (input)  
		{
			tokenizer(input, data);
			parser(data);
			data->cmd[0] = init_cmd(data);
			travel_tree(data->tree,  0, data);
			free_tree(data->tree);
			free_tok(data->tok_list);
			free(input);
		}
		free(data);
		rl_clear_history();
	}

	exit (0);
}


