#include "minishell.h"

//int read_from_u

void add_env_var(t_var *var, char **add_var)
{
	var->key = ft_strdup(add_var[0]);
	var->value = ft_strdup(add_var[1]);
}

int envpcpy(t_var **var, char **src_envp, int add, char **add_var)
{
	char	**temp;
	int		i;

	i = 0;
	while(src_envp[i])
		i++;
	var = (t_var **)malloc(sizeof(t_var *) * (i + add + 1));
	// if (!data-> error? освободить все вышезаписанное
	i = 0;
	while (src_envp[i])
	{
		temp = ft_split(src_envp[i], '=');
		if (!temp)
			break; //error? освободить все вышезаписанное
		var[i] = (t_var *)malloc(sizeof(t_var));
		var[i]->key = temp[0];
		var[i]->value = temp[1];
		// free_and_null_(temp);
		free(temp);
		i++;
	}
	if (add_var)
		add_env_var(var[i], add_var);
	var[i + add] = NULL;
}

t_data *init_data(t_data *data, char **envp)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->envpc = envpcpy(data->var, envp, 0, NULL);
	data->tok_quantity = 0;
	data->cmd_qty = 0;
	data->tok_list = NULL;
	data->cmd_list = NULL;
	return(data);
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;

	data = NULL;
	while (1)
	{
		data = init_data(data, envp);

		if (isatty(fileno(stdin)))
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
			// free_all(data);
		}


		free(data);
	}

	exit (0);
}