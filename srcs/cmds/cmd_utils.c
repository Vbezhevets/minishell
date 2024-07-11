#include "../minishell.h"

char **add_cmd_arg(char **old, int *qty, char *str)
{
	int i;
	
	char **new_a;

	new_a = (char **)malloc((*qty + 1) * sizeof(t_cmd*));
    // if
	i = 0;
	while (i < *qty)
	{
		new_a[i] = (char *)malloc(sizeof(char) * (ft_strlen(old[i]) + 1));
		ft_strcpy(new_a[i], old[i]);
		// free(old[i]);
		// old[i] = NULL;
		i++;
	}
	if(old)
		free(old);
	new_a[i] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	//if
	ft_strcpy(new_a[i], str);
	new_a[i + 1] = (char *)malloc(sizeof(char));
	new_a[i + 1] = NULL;
    *qty = *qty + 1;
	return (new_a);
}

char *del_quotes(char *str, char q)
{
	char	*b;
	int		c;
	char	*res;

	c = 0;
	b = str;
	while (*b)
	{
		if (*b == q)
			c++;
		b++;
	}
	b = (char *)malloc(sizeof(ft_strlen(str) - c + 1 ));
	//if
	res = b;
	while (*str)
	{
		if (*str != q)
		{
			*res = *str;
			res++;
		}
		str++;
	}
	return b;
}
//copy just symbls <- выделаить память: <- посчитать сколько <- 

char *handle_quotes(char *str)
{
	char	q1 = '\'';
	char	q2 = '\"';
	char	*res;

	if (str[0] == q1 || (str[0] == q2 && !ft_strchr(str, '$')))
		res = del_quotes(str, str[0]);
	else
	 	return str;
}

void handle_cmd_args(t_node *node, t_cmd *cmd)
{
	char 	*arg;
	
	ft_strchr(node->value, '=');
	arg = handle_quotes(node->value);
	
	// if (node->quot == 1 || (node->quot == 2 && !ft_strchr(node->value, '$')))
	// {
	// 	arg = ft_strtrim(node->value, str); printf("arg:%s\n", arg);
	// 	cmd->interp = 0;
	// }
	
	// else if (node->quot == 2)
	// {

	// }
    cmd->args = add_cmd_arg(cmd->args, &cmd->args_qty, arg);
}


// сначала проверяет существование всех входящих файлов в редиректах 
// потом 