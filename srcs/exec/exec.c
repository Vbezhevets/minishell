#include "../minishell.h"
int		exec(t_data *data, t_cmd *cmd)
{
	if (execve(cmd->path, cmd->args, data->envp) == -1)
    {
		perror("execve error");
        return (1);
    }
    return (0);
}