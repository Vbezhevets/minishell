 #include "minishell.h"
#include <stdio.h>
#include <sys/types.h>


t_data *init_data(t_data *data, char **sys_envp)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1); //d
	data->var = var_init();
	if (!data->var)
		return (free(data), exit(1), NULL);
	data->envpc = envpcpy(data, sys_envp, &data->envp, data->var);
	if (!data->envpc)
		return (free(data->var), free(data), exit(1), NULL);
	data->tok_quantity = 0;
	data->cmd_qty = 0;
	data->tok_list = NULL;
	data->cmd_list = NULL;
	data->tree = NULL;
	data->temp = NULL;
	data->next_pipe[0] = -1;
	data->next_pipe[1] = -1;
	data->prev_pipe[0] = -1;
	data->prev_pipe[1] = -1;
	data->ex_stat = 0;
	data->std_in = 0;
 	data->std_out = 0;
	data->f = 0;
	data->fds_c = 3;
	return(data);
}

int  main_loop(t_data *data, char  *input)
{
	data->tok_list = tokenizer(input, data, NULL, 1);
	if (!data->tok_list)
		return (free_all(data), 1);
	if (!parser(data))
		return (free_all(data), 1);
	if (data->tree)
		travel_tree(data->tree,  0, data);
	if (data->cmd_list)
		handle_cmd(data, data->cmd_list);
	free_all(data);
	data->cmd_qty = 0;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_data			*data;
	char			*input;

	data = init_data(data, envp);
	while (1)
	{
		if (isatty(fileno(stdin)))
			input = readline("Slava Ukraini! 🇺🇦 >");
		else
		{
			char	*line = get_next_line(0);
			if (!line)
				return 1;
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!input)
		 	break;
		if (is_empty(input))
			continue;
		if (input)
			main_loop(data, input);
	}
	my_exit(data);
}

int my_exit(t_data *data)
{
	int		ex_stat;

	ex_stat = data->ex_stat;
	free_all(data);
	if (data->var)
		free_var(data->var);
	free_and_null_(data->envp);
	free(data->envp);
	while (data->fds_c > 3)
	{
		close(data->fds[data->fds_c - 1]);
		data->fds_c--;
	}
	free(data);
 	exit(ex_stat);
}