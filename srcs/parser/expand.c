#include "../minishell.h"
#include <stdlib.h>


char *exp_var(char *var_name, t_data *data)
{
	int	i;
	t_var	*var;
	char  	*value;

	i = 0;
	var = data->var;
	while (var)
	{
		if (strnlcmp(var->key, var_name))
			return (free(var_name), var->value);
		var = var->next;
	}
	free(var_name);
	var_name = NULL;
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
		return (1);
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

char *add_str(char *res, char *beg, char *var, t_data *data)
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
	if (data->temp)
	{
		free(data->temp);
		data->temp = NULL;
	}
	return (new);
}

char	*get_error_num(t_data *data, int *k)
{
	data->temp = ft_itoa(data->ex_stat);
	(*k)++;
	return (data->temp);
}

char *expand_str(char *str, t_data *data, int i, int k)
{
	char	*res;
	char	*var_val;
	char 	*beg;
	
	res = NULL;
	beg = NULL;
	if (!str)
		return (NULL);
	while(str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		beg = ft_substr(str, 0, i);
		if (str[i] == '$')
		{
			i++;
			k = i;
			while (str[k] && (ft_isalnum(str[k]) || str[k] == '_'))
				k++;
			if (str[i] == '?')
				var_val = get_error_num(data, &k); 
			else if (k > i)
 				var_val = exp_var(ft_substr(str, i, k - i), data);
			else
				var_val = allocpy("$");
			res = (add_str(res, beg, var_val, data));
		}
		else 
			return(add_str(res, beg, NULL, data)); //kz
		str = str + k;
		i = 0;
	}
	if (!res)
		return (allocpy("\0"));
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
		next = (*expanded)->next;
		while (next->next)
			next = next->next;
		(in_token)->next->prev = *expanded;
		next->next = (in_token)->next;
		(*expanded)->exp = 0;
	}
}

t_token *expand_tokens(t_token **in_token)
{
	t_token	*expanded_tok;
	t_data	*data;
	char 	*tok_value;
	char	*unquot;
	char 	*expanded_str;

	tok_value = (*in_token)->value;
	data = (*in_token)->data;
	if (!(*in_token)->exp || !ft_strset(tok_value, "$\"\'")) //
		return (*in_token);
	else if (no_extr_need((*in_token)->value, '\''))
		return ((*in_token)->value = get_rid_q(tok_value, *in_token), free(tok_value), (*in_token));
	else
	{
		unquot = get_rid_q(tok_value, *in_token);
		expanded_str = (expand_str(unquot, data, 0, 0));
		expanded_tok = tokenizer(expanded_str, data, NULL);
		if (expanded_str)
			free(expanded_str);
		if (!expanded_tok)
			expanded_tok = create_tok("", data);
		connect_tok_list(&expanded_tok, *in_token, data);
		free((*in_token)->value);
		free((*in_token));
		// if (unquot && unquot[0] && unquot[0] != '$' && unquot[1]) // no variable
			expanded_tok->exp = 0;
		free(unquot);
		unquot = NULL;
		return (expanded_tok);
	}
	return (NULL);
}
 