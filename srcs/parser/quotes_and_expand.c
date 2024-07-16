#include "../minishell.h"

char *del_quotes(char *str, char q)
{
	char	s;
	char	*res;
	char	*b;
	
	res = (char *)malloc(sizeof(ft_strlen(str) - 1 ));
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

	
	if (input[0] == q1 || (input[0] == q2 && !ft_strchr(input, '$')))
		res = del_quotes(input, input[0]);
	if (res == input)
		return (input);
	else 
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

	i = 0;
	/*
	while (data->var[i].key)
	{
		if (!ft_strncmp(data->var[i].key, var_name, ft_strlen(var_name)))
			return (data->var[i].value);
		i++;
	}
	printf ("%s is ", var_name);
	error("wrong var name"); */
	return (NULL);
}

char *expand_var(char *str, t_data *data)
{
	char	*res;
	char	*unq;
	char	*var_name;
	char	*var_val;
	char	*new;
	int		i;
	
	i = 0;
	unq = expand_str(str);
	res = NULL;
	while(*unq)
	{
		if (unq[i] == '$')
		{
			i++;
			while (unq[i] && (ft_isalnum(unq[i]) || unq[i] == '_'))
				i++;
			var_name = ft_substr(unq, 0, i);
			var_val = exp_var(var_name, data);
			res = ft_strjoin(res, var_val);
			free(var_name);
			free(var_val);
		}
		unq++;
	}
	return (res);
}

// есть смысл все раскрыть в одну строку а затем ее пропустить еще раз через токенайзер? и прицепить все токены к текущему?
t_token *expand_tokens(t_token **in_token)
{
	t_token	*next;
	t_token	*expanded_tokens_list;

	if (!ft_strset((*in_token)->value, "$\"\'"))
		return (*in_token);
	else if (!ft_strchr((*in_token)->value, '$'))
	{
		(*in_token)->value = (expand_str((*in_token)->value));
		return (*in_token);
	}
	else
	 	expanded_tokens_list = tokenizer(expand_var((*in_token)->value, (*in_token)->data), (*in_token)->data);
	if ((*in_token)->prev)
		(*in_token)->prev->next = expanded_tokens_list;
	expanded_tokens_list->prev = (*in_token)->prev;
	next = expanded_tokens_list;
	while (next->next)
		next = next->next;
	next->next = (*in_token)->next;
	free((*in_token)->value);
		(*in_token)->value = NULL;
	free(*in_token);
		*in_token = NULL;
	return (expanded_tokens_list);
}

// сначала проверяет существование всех входящих файлов в редиректах 
// потом 