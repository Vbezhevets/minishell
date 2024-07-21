#include "../minishell.h"
#include <stdlib.h>

char *del_quotes(char *str, char q)
{
	char	s;
	char	*res;
	char	*b;
	
	res = (char *)malloc(sizeof(ft_strlen(str) + 1 ));
	// if (!res)`
	b = res;
	str++;
	while (*(str + 1))
	{
		*res = *str;
		res++;
		str++;
	}
	*res = '\0';

	return b;
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
	return (free(input), input = NULL, (res));
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

char *exp_var(char *var_name, t_data *data)
{
	int	i;
	t_var	*var;

	i = 0;
	var = data->var;
	
	while (var)
	{
		if (!ft_strncmp(var->key, var_name, ft_strlen(var_name)) &&
			 (ft_strlen(var_name) == (ft_strlen(var->key))))
			return (var->value);
		var = var->next;
	}
	// printf ("%s is ", var_name);
	// error("wrong var name"); 
	return (NULL);
}
/// сделать сплит который оставит $
/// раскрыть $ в отдельный массив строк
/// последовательно склеить

char *expand_var(char *str, t_data *data)
{
	char	*res;
	char	*unq;
	char	*var_name;
	char	*var_val;
	char	*new;
	char 	*temp;
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	unq = expand_str(str);
	new = NULL;
	res = NULL;
	temp = NULL;

	
	while(unq[i])
	{
		while (unq[i] != '$')
			i++;
		temp = ft_substr(unq, 0, i);
		if (unq[i] == '$')
		{
			i++;
			k = i;
			while (unq[k] && (ft_isalnum(unq[k]) || unq[k] == '_'))
				k++;
			var_name = ft_substr(unq, i, k);
	 		var_val = exp_var(var_name, data);
			free(var_name);
			res = new;
			new = ft_str3join(res, temp, var_val);
			if (res)
				free(res);
			if (temp)
				free(temp);
			// free(var_val);
		}
		unq = (unq + i + k);
		i = 0;
	}
	return (new);
}

// есть смысл все раскрыть в одну строку а затем ее пропустить еще раз через токенайзер? и прицепить все токены к текущему?
t_token *expand_tokens(t_token **in_token)
{
	t_token	*next;
	t_token	*expanded_tokens_list;
	t_data	*data; 

	data = (*in_token)->data;
	if (!ft_strset((*in_token)->value, "$\"\'"))
		return (*in_token);
	else if (!ft_strchr((*in_token)->value, '$'))
	{
		(*in_token)->value = (expand_str((*in_token)->value));
		return (*in_token);
	}
	else
	 	expanded_tokens_list = tokenizer(expand_var((*in_token)->value, data), data);
	if ((*in_token)->prev) // means not first
	{
		(*in_token)->prev->next = expanded_tokens_list;
		expanded_tokens_list->prev = (*in_token)->prev;
	}
	else
		data->tok_list = expanded_tokens_list;
	next = expanded_tokens_list;
	while (next->next)
		next = next->next;
	next->next = (*in_token)->next;
	// free((*in_token)->value);
	// 	(*in_token)->value = NULL;
	free(*in_token);
		*in_token = NULL;
	return (expanded_tokens_list);
}

// сначала проверяет существование всех входящих файлов в редиректах 
// потом 