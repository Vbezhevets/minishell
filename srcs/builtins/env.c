#include "../minishell.h"

int add_env_var(t_var **var, char *add_str)
{
	char	**temp;
	int		i;

	temp = ft_split(add_str, '=');
	// if (!temp)
		//printf("wrong variable arguments\n"); exit
	i = 0;
	(*var)->key = temp[0];
	(*var)->value = temp[1];
	(*var)->next = (t_var *)malloc(sizeof(t_var));
	*var = (*var)->next;
	free(temp); //?
	return (0);
}

int envpcpy(t_data *data, char **src_envp, char ***dst_envp, t_var *var)
{
	int		i;
	
	i = 0;
	while(src_envp[i])
		i++;
	*dst_envp = (char **)malloc((sizeof(char *) * (i + 1)));
	// if
	i = 0;
	while (src_envp[i])
	{
		// if (var && var->next) // why??????
		// 	var = var->next;
		// else
		add_env_var(&var, src_envp[i]);
		(*dst_envp)[i] = (char *)malloc(sizeof(char) * (ft_strlen(src_envp[i]) + 1));
		// if 
		ft_strcpy((*dst_envp)[i], src_envp[i]);
		i++;
	}
	(*dst_envp)[i] = NULL;
	if (var)
		var = NULL;
	return (i);
}
