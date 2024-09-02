#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "utils/extra.h"

int	g_quit = 0;

void	zeroing_data(t_data *data)
{
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
	data->std_in = 0;
	data->std_out = 1;
	data->ok = 1;
	data->hd = 0;
	data->prev_s = 0;
	data->temp_envp = NULL;
	data->temp_exists = NULL;
	data->temp_arr = NULL;
}

t_data	*init_data(t_data *data, char **sys_envp)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->var = NULL;
	data->envpc = envpcpy(sys_envp, &data->envp, data);
	data->ex_stat = 0;
	data->f = 0;
	data->fds_c = 3;
	zeroing_data(data);
	data->builtins[0] = "export";
	data->builtins[1] = "echo";
	data->builtins[2] = "cd";
	data->builtins[3] = "pwd";
	data->builtins[4] = "export";
	data->builtins[5] = "unset";
	data->builtins[6] = "env";
	data->builtins[7] = "exit";
	return (data);
}

int	main_loop(t_data *data, char *input)
{
	data->tok_list = tokenizer(input, data, NULL, 1);
	if (!data->tok_list || !data->ok)
		return (free_all(data), 1);
	if (!parser(data) || !data->ok)
		return (free_all(data), 1);
	if (data->tree && data->ok)
		travel_tree(data->tree, 0, data);
	if (data->cmd_list)
		handle_cmd(data, data->cmd_list);
	if (data->hd > 0)
		del_temp_hd(data);
	free_all(data);
	data->cmd_qty = 0;
	return (0);
}

int	main(void)
{
	t_data			*data;
	char			*input;

	init();
	data = init_data(NULL, __environ);
	while (1)
	{
		if (g_quit == SIGINT)
		{
			input = readline("");
			g_quit = 0;
		}
		else
			input = readline("Slava Ukraini! 🇺🇦 > ");
		if (!input)
			break ;
		if (is_empty(input))
			continue ;
		if (input)
		{
			add_history(input);
			main_loop(data, input);
		}
	}
	my_exit(data, NULL);
}

int	my_exit(t_data *data, char *error_msg)
{
	int		ex_stat;

	ex_stat = data->ex_stat;
	free_all(data);
	if (data->var)
		free_var(data->var);
	free_and_null_(data->envp);
	free(data->envp);
	while (data->fds_c > 3)
		close(data->fds[--data->fds_c]);
	if (error_msg)
		printf("%s", error_msg);
	close(0);
	close(1);
	close(2);
	free(data);
	exit(ex_stat);
}
