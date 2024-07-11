#include "../minishell.h"
int		exec(t_data *data, t_cmd *cmd)
{
	// if (access(cmd->path, F_OK) == -1) 
	// {
	// 	perror("File does not exist");
	// 	return 1;
	// }
	// printf("1\n");
	if (execve(cmd->path, cmd->args, data->envp) == -1)
	{
		perror("execve error");
		return (1);
	}
	return (1);
}