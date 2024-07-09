#include "minishell.h"

int echo(char **args)
{
    printf("echo!\n");
    return (0);
}

int builtin(t_cmd *cmd, t_data *data)
{
    if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
        return(echo(cmd->args));
    return (0);
}