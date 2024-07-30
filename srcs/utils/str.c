#include "../minishell.h"
#include <string.h>

char	*allocpy(char *str)
{
	return (ft_substr(str, 0, ft_strlen(str)));
}

int strnlcmp(char *str1, char *str2)
{
    if (!str1 || !str2)
        return(-1);
	if ((ft_strlen(str1) == ft_strlen(str2)) && 
    !ft_strncmp(str1, str2, ft_strlen(str2)))
        return (1);
    return 0;
}
char *del_quotes(char *str, char q, int i)
{
	char **temp;
	char *res;

	res = NULL;
	temp = ft_split(str, q);

	while (temp[i])
	{
		res = free_join (res, temp[i]);
		i++;
	}
	return res;
}

char	*get_rid_q(char *input, t_token *token)
{
	char *res;

	char	q1 = '\'';
	char	q2 = '\"';
	int		i;
	
	if (token)
		token->exp = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == q1 || input[i] == q2)
			break;
		i++;
	}
	if (input[i] == q1 || (input[i] == q2))// && !ft_strchr(input, '$')))
	{
		res = del_quotes(input, input[i], 0);
		if (strcmp(res, input))
			free(input);
	}
	else
		return (input);
	return (res);
}

int ft_strset(char *str, char *set)
{
	char	*b;
	int		i;

	i = 0;
	while (*set)
	{
		while (str[i])
		{
			if (str[i] == *set)
				return (1);
			i++;
		}	
		set++;
		i = 0;
	}
	return i;
}

char **add_str_arr(char **old, char *str)
{
	int		i;
	char 	**new;
	
	i = 0;
	while (old[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	//if
	i = 0;
	while (old[i])
	{
		new[i] = malloc(sizeof(char *) * (ft_strlen(old[i]) + 1));
		//if free_and_null_(new);
		ft_strcpy(new[i], old[i]);	
		i++;
	}
	new[i] = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	new[i + 1] = NULL;
	free_and_null_(old);
	free(old);
	return(new);
}
