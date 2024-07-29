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

int no_extr_need(char *str, char q)
{
	int	i;
	int	k;
	int	qcount;

	if (!ft_strchr(str, '$'))
		return (0);
	i = 0;
	while (str[i] && str[i] != '$')
			i++;
	k = 0;
	qcount = 0;
	while (k <= i)
	{
		if (str[k] == q)
			qcount++;
		k++;
	}
		return (qcount % 2);
}

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
	unq = expand_str(str, NULL);
	new = NULL;
	res = NULL;
	temp = NULL;

	
	while(unq[i])
	{
		if (no_extr_need(unq, '\"'))
			return(unq);
		while (unq[i] && unq[i] != '$')
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




void connect_tok_list(t_token **expanded, t_token *in_token, t_data *data)
{
	t_token	*next;

	if ((in_token)->prev) // means not first
		{
			(in_token)->prev->next = *expanded;
			(*expanded)->prev = (in_token)->prev;
		}
	else
		data->tok_list = *expanded;
	if ((in_token)->next)
	{
		(in_token)->next->prev = *expanded;
		next = *expanded;
		while (next->next)
			next = next->next;
		next->next = (in_token)->next;
	}
}

t_token *expand_tokens(t_token **in_token)
{
	t_token	*expanded_tok;
	t_data	*data; 

	data = (*in_token)->data;
	if (!(*in_token)->exp || !ft_strset((*in_token)->value, "$\"\'")) //
		return (*in_token);
	else if (no_extr_need((*in_token)->value, '\''))
	{
		(*in_token)->value = expand_str((*in_token)->value, *in_token);
		(*in_token)->exp = 0;
		return (*in_token);
	}
	else
	 	expanded_tok = tokenizer(expand_var((*in_token)->value, data), data);
	if (!expanded_tok)
		expanded_tok = create_tok("", data);
	connect_tok_list(&expanded_tok, *in_token, data);
	free(*in_token);
		*in_token = NULL;
		expanded_tok->exp = 0; //and
	return (expanded_tok);
}
 