#include "../minishell.h"

void	connect_tok_list(t_token **expanded, t_token *in_token, t_data *data)
{
	if (!*expanded)
		return ;
	if ((in_token)->prev)
	{
		(in_token)->prev->next = *expanded;
		(*expanded)->prev = (in_token)->prev;
	}
	else
		data->tok_list = *expanded;
	if ((in_token)->next)
	{
		(in_token)->next->prev = *expanded;
		(*expanded)->next = (in_token)->next;
		(*expanded)->exp = 0;
	}
}

t_token	*exp_(char *tok_value, t_token **in_token, t_data *data, char *unquot)
{
	char	*expanded_str;
	t_token	*expanded_tok;

	expanded_str = NULL;
	unquot = NULL;
	unquot = get_rid_q(tok_value, 0, 0, NULL);
	if (!unquot)
		expanded_tok = create_tok("", data, 0);
	else
	{
		expanded_str = expand_str(unquot, data, NULL, unquot);
		if (ft_strlen(expanded_str))
			expanded_tok = tokenizer(expanded_str, data, NULL, 0);
		else
			expanded_tok = create_tok("", data, 0);
	}
	free(expanded_str);
	connect_tok_list(&expanded_tok, *in_token, data);
	if (unquot && unquot[0] && unquot[0] != '$' && unquot[1])
		expanded_tok->exp = 0;
	if (tok_value != unquot)
		free(unquot);
	free((*in_token)->value);
	free((*in_token));
	return (expanded_tok);
}

t_token	*expand_tokens(t_token **in_token)
{
	t_token	*expanded_tok;
	t_data	*data;
	char	*tok_value;

	tok_value = (*in_token)->value;
	data = (*in_token)->data;
	if (!(*in_token)->exp || !ft_strset(tok_value, "$\"\'"))
		return (*in_token);
	else if (no_extr_need((*in_token)->value, '\''))
	{
		(*in_token)->value = get_rid_q(tok_value, 0, 0, NULL);
		free(tok_value);
		(*in_token)->exp = 0;
		return (*in_token);
	}
	else
	{
		expanded_tok = exp_(tok_value, in_token, data, NULL);
		return (expanded_tok);
	}
	return (NULL);
}

char	*exp_var(char *var_name, t_data *data, char **str)
{
	t_var	*var;
	char	*beg;

	if (str)
		beg = *str;
	var = data->var;
	if (str)
	{
		while ((**str) && (ft_isalnum(**str) || **str == '_'))
			(*str)++;
		if (*str > beg)
			var_name = ft_substr(beg, 0, (*str) - beg);
		else
			return ("$");
	}
	while (var)
	{
		if (strnlcmp(var->key, var_name))
			return (free(var_name), var->value);
		var = var->next;
	}
	free(var_name);
	return (NULL);
}

int	no_extr_need(char *str, char q)
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

char	*add_str(char *res, char *beg, char *var, t_data *data)
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
	if (data->temp)
	{
		free(data->temp);
		data->temp = NULL;
	}
	return (new);
}

char	*get_error_num(t_data *data, char **str)
{
	data->temp = ft_itoa(data->ex_stat);
	*str = *str + 1;
	return (data->temp);
}

char	*expand_str(char *str, t_data *data, char *res, char *beg)
{
	char	*var_val;

	while (*str)
	{
		while (*str && *str != '$')
			str++;
		beg = ft_substr(beg, 0, str - beg);
		if (*str == '$')
		{
			str++;
			if (*str == '?')
				var_val = get_error_num(data, &str);
			else
				var_val = exp_var(NULL, data, &str);
			res = (add_str(res, beg, var_val, data));
		}
		else
			return (add_str(res, beg, NULL, data));
		beg = str;
	}
	if (!res)
		res = ft_strdup("\0");
	if (!res)
		return (error("alloc error", NULL, NULL, 2), NULL);
	return (res);
}
