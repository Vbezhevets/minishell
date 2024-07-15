#include "../minishell.h"

char *del_quotes(char *str, char q)
{
	char	s;
	char	*res;
	char	*b;
	
	res = (char *)malloc(sizeof(ft_strlen(str) - 1 ));
	// if (!res)
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

char *handle_quotes(char *str)
{
	char	q1 = '\'';
	char	q2 = '\"';
	char	*res;

	if (str[0] == q1 || (str[0] == q2 && !ft_strchr(str, '$')))
		res = del_quotes(str, str[0]);
	else
	 	return str;
}
char *expand_str(char *input)
{
	char *res;

	res = handle_quotes(input);
	
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
				return (i);
			i++;
		}	
		set++;
		i = 0;
	}
	return i;
}
char *expand_var(char *str, t_data *data)
{
	char	*res;
	char	*new;
	int		i;
	int		count;
	
	i = 0;
	res = expand_str(str);
	while(*res)
	{
		if (*res == '$')
			while (res[i] && (ft_isalnum(res[i]) || res[i] == '_'))
				i++;
		data_
		*new = *res;
		new++;
		res++;
	}
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