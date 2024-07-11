#include "../minishell.h"

int echo(char **args, int i)
{
	if (!args[1] || !args[1][0])
		return (printf("\n"), 0);
	while (args[++i])
		printf("%s ", args[i]);
	printf("\n");

	// if (args[1] = "-n")
	// while(args[i])

	return (0);
}

int builtin(t_cmd *cmd, t_data *data)
{
	// if (!from_rdr(cmd) || !to_rdr(cmd))
	// 	return (1);

	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")))
		return(echo(cmd->args, 0));
	return (1);
}