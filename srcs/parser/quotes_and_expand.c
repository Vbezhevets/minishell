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

char *add_str(char *res, char *beg, char *var)
{
	char	*new;

	new = ft_str3join(res, beg, var);
	if (res)
	{
		free (res);
		res = NULL;
	}
	if (beg)
	{
		free (beg);
		beg = NULL;
	}
	if (strnlcmp(var, "$"))
	{
		free (var);
		var = NULL;
	}
	return (new);
}

char *expand_str(char *str, t_data *data)
{
	char	*res;
	char	*unq;
	char	*var_name;
	char	*var_val;
	char 	*beg;
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	unq = get_rid_q(str, NULL);
	res = NULL;
	beg = NULL;
	
	while(unq[i])
	{
		if (no_extr_need(unq, '\"'))
			return(unq);
		while (unq[i] && unq[i] != '$')
			i++;
		beg = ft_substr(unq, 0, i);
		if (unq[i] == '$')
		{
			i++;
			k = i;
			while (unq[k] && (ft_isalnum(unq[k]) || unq[k] == '_'))
				k++;
			if (unq[i] == '?')
			{
				var_val = ft_itoa(data->ex_stat);
				k++;
			}
			else if (k > i)
			{
				var_name = ft_substr(unq, i, k - i);
 				var_val = exp_var(var_name, data);
				free(var_name);
			}
			else
				var_val = allocpy("$");
			res = (add_str(res, beg, var_val));
		}
		else 
			return(add_str(res, beg, NULL));
		unq = unq + k;
		i = 0;
	}
	return (res);
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
		(*in_token)->value = get_rid_q((*in_token)->value, *in_token);
		(*in_token)->exp = 0;
		return (*in_token);
	}
	else
		(*in_token)->value = expand_str((*in_token)->value, data);
	/*	expanded_tok = tokenizer(expand_str((*in_token)->value, data), data);
	if (!expanded_tok)
		expanded_tok = create_tok("", data);
	connect_tok_list(&expanded_tok, *in_token, data);
	free(*in_token);
		*in_token = NULL;	
		expanded_tok->exp = 0; 

	return (expanded_tok); */
	return (*in_token);
}
 