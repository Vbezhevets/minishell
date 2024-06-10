#include "minishell.h"

int quoted(char *s)
{
	char q;
	int i;

	i = 1;
	q = *s;
	s++;
	while (*s && *s != q)
	{
		s++;
		i++;
	}
	if (*s == '\0')
		error("paraanteses error");
	return (i + 1);
}
int tok_detect(char *token_value)
{
	if (token_value[0] == '>')
	{
		if (token_value[1] && token_value[1] == '>')
			return (LRLR);
		else
			return (LR);
	}
	else if (token_value[0] == '<')
	{
		if (token_value[1] && token_value[1] == '<')
			return (RLRL);
		else
			return (RL);
	}
	else if (token_value[0] == '|')
		return (PIPE);
	else
		return (WORD);
}

int char_detect(char *s)
{
	if (*s == 34 || *s == 39)
		return (quoted(s));
	if (tok_detect(s) == RLRL || tok_detect(s) == LRLR)
		return (2);
	return (1);
}

static int	ft_length(char *s)
{
	char *point;
	
	point = s;
	while (*s && !ft_strchr(DELIM, *s))
		s += char_detect(s);
	return (s - point);
}


int precedence(t_token *token) 
{
	if (token->type == PIPE)
		return 3;
	else if (token->type == LR || token->type == LRLR 
		|| token->type == RLRL || token->type == RL)
		return 2;
	else if (token->type == WORD)
		return 1;
	return 0;
}

t_token *tok_create(char *input_str)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	// if (!token->value)
	// 	return (free_tok(token), exit(1), NULL); //handle exit in error.c
	token->length = ft_length(input_str);
	token->value = (char *)malloc((token->length + 1) * sizeof(char));
	// if (token->value == NULL)
	// 	return (free_tok(token), exit(1), NULL); //handle exit
	ft_strlcpy(token->value, input_str, token->length + 1);
	token->type = tok_detect(token->value);
	token->next = NULL;
	token->prev = NULL;
	token->P = precedence(token);
	return (token);
}

void	tokenizer(char *input_str, t_data *data)
{
	t_token	*token;

	while (*input_str)
	{
		while (*input_str && ft_strchr(DELIM, *input_str))
			input_str++;
		if (*input_str == '\0')
			return;
		if (data->tok_qty == 0)
		{
			data->tok_list = tok_create(input_str);
			token = data->tok_list;
		}
		else if (*input_str != '\0')
		{
			token->next = tok_create(input_str);
			token->next->prev = token;
			token = token->next;
		}
		else
			return;
		input_str = input_str + token->length;
		data->tok_qty++;
	}
}
