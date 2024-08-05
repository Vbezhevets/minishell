#include "../minishell.h"

int quoted(char *s)
{
	char q;
	int i;

	i = 1;
	q = *s;
	s++;

	while (1)
	{
		if (*s == '\0')
			return (error("quotes error", NULL, NULL, 1), -1);
		if (*s == q && *(s - 1) != '\\')
			break;
		s++;
		i++;
	}
	return (i + 1);
}

int tok_detect(char *token_value, int exp)
{
	if (exp == 0)
		return (WORD);
	if (token_value[0] == '>') 
	{
		if (ft_strlen(token_value) > 1 && token_value[1] == '>')
			return (LRLR);
		else
			return (LR);
	}
	if (token_value[0] == '<')
	{
		if (ft_strlen(token_value) > 1 && token_value[1] == '<')
			return (RLRL);
		else
			return (RL);
	}
	if (token_value[0] == '|')
		return (PIPE);
	if (token_value[0] == '"')
		return (EXP_FIELD);
	if (token_value[0] == '\'')
		return (FIELD);
	return (WORD);
}

int quot_detect(char *s)
{
	if (*s == 34 || *s == 39 )
		return (quoted(s));
	return (1);
}

static int	ft_length(char *s)
{
	char	*start;
	int		rdr_l;
	int		shift;

	rdr_l = 0;
	start = s;
	while (*s && !ft_strchr(DELIM, *s))
	{
		if (tok_detect(s, 1) == RLRL || tok_detect(s, 1) == LRLR)
			rdr_l = 2;
		else if (tok_detect(s, 1) == RL || tok_detect(s, 1) == LR || tok_detect(s, 1) == PIPE)
			rdr_l = 1;
		if (rdr_l != 0 && !(s - start)) // возрашаем значение редиректа
			return (rdr_l);
		if (rdr_l != 0 && (s - start)) //  был сдвиг до встречи редиректа, возврашаем значение перед редиерктом
			return (s - start);
		shift = quot_detect(s);
		if (shift < 0)
			return (-1);
		else
			s += quot_detect(s);
	}
	return (s - start);
}


int precedence(t_token *token) 
{
	if (token->type == PIPE)
		return 3;
	else if (token->type == LR || token->type == LRLR 
		|| token->type == RLRL || token->type == RL)
		return 2;
	else if (token->type == WORD || token->type == EXP_FIELD || token->type == FIELD)
		return 1;
	return 0;
} 

t_token *create_tok(char *input_str, t_data *data, int exp)
{
	t_token *token;
	if (ft_length(input_str) >= 0)
		token = (t_token *)malloc(sizeof(t_token));
	else
		return (NULL);
	// if (!token->value)
	// 	return (free_tok(token), exit(1), NULL); //handle exit in error.c
	token->length = ft_length(input_str);
	token->value = (char *)malloc((token->length + 1) * sizeof(char));
	// if (token->value == NULL)
	// 	return (free_tok(token), exit(1), NULL); //handle exit
	ft_strlcpy(token->value, input_str, token->length + 1);
	token->type = tok_detect(token->value, exp);
	token->next = NULL;
	token->prev = NULL;
	token->P = precedence(token);
	token->data = data;
	token->exp = exp; //and
	return (token);
}

/*
t_token	*tokenizer(char *input_str, t_data *data, t_token *token)
{
	while (*input_str)
	{
		while (*input_str && ft_strchr(DELIM, *input_str))
			input_str++;
		if (*input_str == '\0')
			break;
		if (!token)
			token = create_tok(input_str, data);
		else
		{
			token->next = create_tok(input_str, data);
			token->next->prev = token;
			token = token->next;
		}
		if (!token)
			return(NULL);
		input_str = input_str + token->length;
	}
	return (token);
} */

t_token	*tokenizer(char *input_str, t_data *data, t_token *tok_list, int exp)
{
	t_token	*token;

	while (*input_str)
	{
		while (*input_str && ft_strchr(DELIM, *input_str))
			input_str++;
		if (*input_str == '\0')
			break;
		if (!tok_list)
		{
			tok_list = create_tok(input_str, data, exp);
			token = tok_list;
		}
		else
		{
			token->next = create_tok(input_str, data, exp);
			token->next->prev = token;
			token = token->next;
		}
		if (token)
			input_str = input_str + token->length;
		else
			return (NULL);
	}
	return (tok_list);
}
