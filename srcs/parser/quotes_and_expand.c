#include "../minishell.h"
#include <stdlib.h>


char *exp_var(char *var_name, t_data *data)
{
	int	i;
	t_var	*var;

	i = 0;
	var = data->var;
	
	while (var)
	{
		if (strnlcmp(var->key, var_name))
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
			var_name = ft_substr(unq, i, k - 1);
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
		unq = (unq + k);
		i = 0;
	}
	return (new);
}

// есть смысл все раскрыть в одну строку а затем ее пропустить еще раз через токенайзер? и прицепить все токены к текущему?
t_token *expand_tokens(t_token **in_token)
{
	t_token	*next;
	t_token	*expanded_tokens;
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
	 	expanded_tokens = tokenizer(expand_var((*in_token)->value, data), data);
	if (!expanded_tokens)
		expanded_tokens = create_tok("", data);
	if ((*in_token)->prev) // means not first
	{
		(*in_token)->prev->next = expanded_tokens;
		expanded_tokens->prev = (*in_token)->prev;
	}
	else
		data->tok_list = expanded_tokens;
	if ((*in_token)->next)
	{
		(*in_token)->next->prev = expanded_tokens;
		next = expanded_tokens;
		while (next->next)
			next = next->next;
		next->next = (*in_token)->next;
	}
	// free((*in_token)->value);
	// 	(*in_token)->value = NULL;
	free(*in_token);
		*in_token = NULL;
	return (expanded_tokens);
}

// сначала проверяет существование всех входящих файлов в редиректах 
// потом 