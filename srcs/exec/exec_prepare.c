#include "../minishell.h"
#include <complex.h>
#include <stdio.h>

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
		if (!access(path, F_OK)) //success
			return (free_and_null_(pathes), free(pathes), path);
		free(path);
		i++;
	}
	free_and_null_(pathes);
	free(pathes);
	return (NULL);
}

int is_bltin(t_cmd *cmd)
{
	int i;

	i = 6;
	while (i >= 0)
	{
		if (strnlcmp(cmd->args[0], (char *)builtins[i]))
			{
				cmd->bi = 1;
				return i + 1;
			}
		i--;
	}
	return (0);
}

int check_cmd(t_cmd **cmd, t_data *data)
{
	if (!is_bltin(*cmd) && !((*cmd)->path = get_path(data->envp, (*cmd)->args[0])))
	{
		printf("\"%s\" is wrong command\n", (*cmd)->args[0]);
		*cmd = (*cmd)->next;
		return (0);
	}
	else
		return (1);
}



int	handle_cmd(t_data *data, t_cmd *cmd)
{
	char	cwd[8192];

    if (getcwd(cwd, sizeof(cwd)) == NULL)       
        return (perror("getcwd error"), 1);
	while(cmd)
	{
		//pipe create/connnect;
		if (!check_cmd(&cmd, data))
			continue;
		if (cmd->bi)
			builtin(cmd, data);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				if (rdr(cmd->from_file, cwd, cmd, 0) && rdr(cmd->to_file, cwd, cmd, 1))
					exec(data, cmd);
			}
				waitpid(-1, NULL, 0);
		}
		cmd = cmd->next;
	}
		return 0;
 }