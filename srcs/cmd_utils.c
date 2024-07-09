#include "minishell.h"

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
		free(old[i]);
		old[i] = NULL;
		i++;
	}
	if(old)
		free(old);
	new_a[i] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	//if
	ft_strcpy(new_a[i], str);
    *qty = *qty + 1;
	return (new_a);
}

char **handle_quotes(char *str)
{
	char	q1 = '\'';
	char	q2 = '\"';
	char	*res;

	if (str[0] == q1 || (str[0] == 2 && !ft_strchr(str, '$')))
	{
		res = ft_strtrim(str, &str[0]);
	}

}

void add_cmd_args(t_node *node, t_cmd *cmd)
{
	char 	*arg;
	// char	*quot = "'";

	arg = node->value;
	if (node->quot == 1 || (node->quot == 2 && !ft_strchr(node->value, '$')))
	{
		arg = ft_strtrim(node->value, &node->value[0]);
		cmd->interp = 0;
	}
	// else if (node->quot == 2)
	// {

	// }
    cmd->args = add_cmd_arg(cmd->args, &cmd->args_qty, arg);
}


// сначала проверяет существование всех входящих файлов в редиректах 
// потом 