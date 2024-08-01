 #include "minishell.h"
#include <stdio.h>


t_data *init_data(t_data *data, char **sys_envp)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1); //d
	data->var = (t_var *)malloc(sizeof(t_var));
	//if
	data->envpc = envpcpy(data, sys_envp, &data->envp, data->var);
	data->tok_quantity = 0;
	data->cmd_qty = 0;
	data->tok_list = NULL;
	data->cmd_list = NULL;
	data->tree = NULL;
	data->next_pipe[0] = -1;
	data->next_pipe[1] = -1;
	data->prev_pipe[0] = -1;
	data->prev_pipe[1] = -1;
	data->ex_stat = 0;
	data->std_in = 0;
 	data->std_out = 0;
	data->f = 0;
	return(data);
}

int main(int argc, char **argv, char **envp)
{
	t_data			*data;
	char			*input;
	unsigned int	ex_stat;

	data = init_data(data, envp);
	while (1)
	{
		// if (1)
			input = readline("Slava Ukraini! 🇺🇦 >");
		// else
		// {
		// 	char	*line = get_next_line(0);
		// 	if (!line)
		// 		return 1;
		// 	input = ft_strtrim(line, "\n");
		// 	free(line);
		// }
		if (!input)
			break;
		if (input)
		{
			data->tok_list = tokenizer(input, data, NULL);
			if ((!data->tok_list) || (!parser(data)))
			{
				free_all(data);
				break;
			}	
			if (data->tree)
				travel_tree(data->tree,  0, data);
			if(data->cmd_list)
				handle_cmd(data, data->cmd_list);
			if (!data->f)
				free_all(data);
			data->cmd_qty = 0;
		}
	}
	my_exit(data);
}

int my_exit(t_data *data)
{
	int		ex_stat;

	ex_stat = data->ex_stat;
	if (!data->f)
		free_all(data);
	if (data->var)
		free_var(data->var);
	free_and_null_(data->envp);
	free(data);
 	exit(ex_stat);

}