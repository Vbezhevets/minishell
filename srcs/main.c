#include "minishell.h"
#include <stdio.h>


t_data *init_data(t_data *data, char **sys_envp)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1); //
	data->var = (t_var *)malloc(sizeof(t_var));
	if (!data->var)
		return(free(data), exit(1), NULL);
	data->var->next = NULL;
	data->envpc = envpcpy(data, sys_envp, &data->envp, data->var);
	data->tok_quantity = 0;
	data->cmd_qty = 0;
	data->tok_list = NULL;
	data->cmd_list = NULL;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
 	if (data->std_out < 0 || data->std_in < 0)
		return(free(data), free(data->var), exit(1), NULL);
	
	return(data);
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;

	data = init_data(data, envp);
	while (1)
	{
		// if (isatty(fileno(stdin)))
			input = readline("Slava Ukraini! 🇺🇦 >");
	// 	else
	// {
	// 	char *line;
	// 	line = get_next_line(fileno(stdin));
	// 	input = ft_strtrim(line, "\n");
	// 	free(line);
	// }

		if (input)
		{
			data->tok_list = tokenizer(input, data);
			parser(data);
			travel_tree(data->tree,  0, data);
			if(data->cmd_list)
				handle_cmd(data, data->cmd_list);
			free_all(data);
			data->cmd_qty = 0;
		}


	}
		free(data);

	exit (0);
}