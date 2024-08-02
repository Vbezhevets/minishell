#include "../minishell.h"


t_var *var_init()
{
	t_var	*var;
	
	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		return (error("alloc error", NULL, NULL, 2), NULL);
	var->next = NULL;
	var->value = NULL;
	var->key = NULL;
	return (var);
}

int add_env_var(t_var **var, char *add_str)
{
	char	**temp;
	int		i;

	temp = ft_split(add_str, '=');
	if (!temp)
		return (printf("%s wrong variable\n", add_str), 1);
	i = 0;
	(*var)->key = allocpy(temp[0]);
	if (temp[1])
		(*var)->value = allocpy(temp[1]); 
	else
		(*var)->value = allocpy("\0");
	(*var)->next = var_init();
	*var = (*var)->next;
	free_and_null_(temp);
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
		add_env_var(&var, src_envp[i]);
		(*dst_envp)[i] = (char *)malloc(sizeof(char) * (ft_strlen(src_envp[i]) + 1));
		// if 
		ft_strcpy((*dst_envp)[i], src_envp[i]);
		i++;
	}
	(*dst_envp)[i] = NULL;
	// if (var)
	// {
	// 	free(var);
	// 	var = NULL;
	// }
	return (i);
}
