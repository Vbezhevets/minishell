#include "../minishell.h"

int strnlcmp(char *str1, char *str2)
{
    if (!str1 || !str2)
        return(-1);
	if ((ft_strlen(str1) == ft_strlen(str2)) && 
    !ft_strncmp(str1, str2, ft_strlen(str2)))
        return (1);
    return 0;
}


char *del_quotes(char *str, char q)
{
	char	s;
	char	*res;
	int		i;
	int		k;

	i = 0;
	while (str[i] && str[i] != q)
		i++;	
	res = (char *)malloc(sizeof(char) * (i) + 1);
	// if (!res)`
	i = 0;
	k = -1;
	while (str[i])
	{
		if(str[i] != q)
			res[++k] = str[i];
		i++;
	}
	free(str);
	str = NULL;
	res[++k] = '\0';
	return res;
}
//copy just symbls <- выделаить память: <- посчитать сколько <- 


char *expand_str(char *input)
{
	char *res;

	char	q1 = '\'';
	char	q2 = '\"';

	
	if (input[0] == q1 || (input[0] == q2))// && !ft_strchr(input, '$')))
		res = del_quotes(input, input[0]);
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