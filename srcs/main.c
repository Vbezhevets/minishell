#include "minishell.h"

//int read_from_u

void envpcpy(t_data *data, char **src_envp)
{
	int	i;

	data->envp = (char **)malloc(sizeof(char *));
	// if (!data->envp)
	// 	exit(1);
	i = 0;
	while (src_envp[i])
	{
		data->envp[i] = (char *)malloc(sizeof(char) * (ft_strlen(src_envp[i]) + 1));
		// if (!data->envp[i])
		// 	exit(1);
		ft_strlcpy(data->envp[i], src_envp[i], ft_strlen(src_envp[i]) + 1);
		i++;
	}
}

t_data *init_data(t_data *data, char **envp)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	// envpcpy(data, envp);
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
	
	while (1)
	{
		data = init_data(data, envp);
		
		input = readline("Slava Ukraini! 🇺🇦 >"); 
		if (input)
		{
			tokenizer(input, data);
			parser(data);
			travel_tree(data->tree,  0, data);
			
			int i = 0;
			while(i < data->cmd_list->args_qty)
			{
				printf("%s\n", data->cmd_list->args[i]);
				i++;
			}
			free_tree(data->tree);
			free_tok(data->tok_list);
		}


		free(data);
	}

	exit (0);
}