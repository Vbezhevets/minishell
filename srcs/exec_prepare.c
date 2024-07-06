#include "minishell.h"

char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	**pathes;
	char	*path;

	pathes = NULL;
	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) && envp[i])
		i++;
	pathes = ft_split(envp[i] + 5, ':');
	if (!pathes)
		return (ft_printf("split error\n"), NULL);
	i = 0;
	while (pathes[i])
	{
		path = ft_str3join(pathes[i], "/", cmd);
		if (!access(path, F_OK))
			return (free_and_null_(pathes), free(pathes), path);
		free(path);
		i++;
	}
	free_and_null_(pathes);
	free(pathes);
	return (NULL);
}


void ext_cmd(t_data *data, t_cmd *cmd)
{
	cmd->path = get_path(data->envp, cmd->args[0]);
	if (!cmd->path)
	{
		ft_printf("command error!\n");
		free_and_null_(cmd->args);
		// free everything and exit
	}
}

int is_bltin(t_cmd *cmd)
{
	int i;

	i = 6;
	while (i >= 0)
	{
		if (!ft_strncmp(cmd->args[0], builtins[i], ft_strlen(cmd->args[0])))
			return i + 1;
		i--;
	}
	return (0);
}
int	exec(t_data *data)
{
	t_cmd	*cmd;

	if (!data->cmd_qty)
		return 0;
	if (data->cmd_qty == 1)
		cmd = data->cmd_list;
	if (!is_bltin(cmd))
	{
		ext_cmd(data, cmd);
		if (cmd->path)
			printf("%s\n", cmd->path);
	}
 }