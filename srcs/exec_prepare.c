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

int exec_prepare(t_data *data, t_cmd *cmd, char **envp)
{
    	cmd->path = get_path(envp, cmd->args[0]);
		if (!cmd->path)
		{
			ft_printf("command error!\n");
			free_and_null_(cmd->args);
			// free everything and exit
		}
	return(0);
}