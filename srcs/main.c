#include "minishell.h"


int add_env_var(t_var **var, char *add_str)
{
	char	**temp;
	int		i;

	temp = ft_split(add_str, '=');
	// if (!temp)
		//printf("wrong variable arguments\n"); exit
	i = 0;

	// while (temp[0][i])
	// {
		// if (!ft_isalnum(temp[0][i]) && temp[0][i] != '_')
			// return (printf("%s is wrong variable name\n", temp[0]), 1);
		// i++;
	// 
	// }
	
	(*var)->key = temp[0];
	(*var)->value = temp[1];
	(*var)->next = (t_var *)malloc(sizeof(t_var));
	*var = (*var)->next;
	free(temp);
	return (0);
}

int envpcpy(t_data *data, char **src_envp, char ***dst_envp, t_var *var)
{
	int		i;
	
	i = 0;
	while(src_envp[i])
		i++;
	*dst_envp = (char **)malloc((sizeof(char *) * (i + 1)));
	// if
	i = 0;
	while (src_envp[i])
	{
		if (var)
			add_env_var(&var, src_envp[i]);
		(*dst_envp)[i] = (char *)malloc(sizeof(char) * (ft_strlen(src_envp[i]) + 1));
		// if 
		ft_strcpy((*dst_envp)[i], src_envp[i]);
		i++;
	}
	(*dst_envp)[i] = NULL;
	if (var)
		var = NULL;
	return (i);
}

t_data *init_data(t_data *data, char **sys_envp)
{
	int	i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1); //
	data->var = (t_var *)malloc(sizeof(t_var));
	// if (!data->var)
	data->envpc = envpcpy(data, sys_envp, &data->envp, data->var);
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
	data = init_data(data, envp);
	while (1)
	{

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