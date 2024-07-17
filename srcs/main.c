#include "minishell.h"

int read_from_u

void add_env_var(t_var *var, char **add_var)
{
	char	**temp;
	
	temp = ft_split(src_envp[i], '=');
		if (!temp)
			break; //error? освободить все вышезаписанное
		// free_and_null_(temp);
		free(temp);

	var->key = ft_strdup(add_var[0]);
	var->value = ft_strdup(add_var[1]);
	// плюс пересобрать data->envp
}

int envpcpy(t_data *data, char **src_envp, char ***dst_envp)
{
	int		i;
	
	i = 0;
	while(src_envp[i])
		i++;
	*dst_envp = (char **)malloc((sizeof(char *) * (i + 1)));
	// if (!data-> error? освободить все вышезаписанное
	i = 0;
	while (src_envp[i])
	{
		(*dst_envp)[i] = (char *)malloc(sizeof(char) * (ft_strlen(src_envp[i]) + 1));
		ft_strcpy((*dst_envp)[i], src_envp[i]);
		i++;
	}
	(*dst_envp)[i] = NULL;
	return (0);
}

t_data *init_data(t_data *data, char **sys_envp)
{
	int	i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	i = 0;
	while(sys_envp[i])
		i++;
	data->envpc = envpcpy(data, sys_envp, &data->envp);
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