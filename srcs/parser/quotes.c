/*
/bin/echo '"$USER"'
quotes error 


/bin/echo '"'"$USER"'"'
'"'

/bin/echo ''$?''"42"

*/
#include "../minishell.h"

t_str *add_chunk( t_str *prev, char *str, int start, int end)
{
	t_str	*chunk;
	
	chunk = (t_str *)malloc(sizeof(t_str));
	chunk->str = ft_substr(str, start, end - start);
	if (prev)
	{
		prev->next = chunk;
		chunk->prev = prev;
	}
	else
		chunk->prev = NULL;
	chunk->next = NULL;
	return (chunk);
}

char *sum_str(t_str *chunk)
{
	t_str	*prev;
	t_str	*next;
	char 	*res;

	res = NULL;
	prev = chunk;
	while (prev && prev->prev)
		prev = prev->prev;
	next = prev;
	while (next)
	{		
		res = free_join(res, next->str); //leak ""
		free(next->str);
		next->str = NULL;
		prev = next;
		next = next->next;
		free(prev);
	}
	return (res);
}


char is_q(char c)
{
		if (c == Q)
			return (Q);
		if (c == QQ)
			return (QQ);
		else
			return (0);
}

char	*get_rid_q(char *str, t_token *token)
{
	char	*res;
	int		i = 0;
	int 	start = 0;
	char	q;
	t_str	*chunk;

	// if (!ft_strset(str, "\' \""))
	// 	return(allocpy(str));
	chunk = NULL;
	if (token)
		token->exp = 0;
	while (str[i])
	{
		while (str[i] && !is_q(str[i]))
			i++;
		if(i > 0 && str[i - 1] == '=')
			return (str);
		chunk = add_chunk(chunk, str, start, i);
		if (!str[i])
			break;
		if (is_q(str[i]))
		{
			q = str[i];
			i++;
			start = i;
			while (str[i] && str[i] != q)
				i++;
		}
		chunk = add_chunk(chunk, str, start, i);
		i++;
		start = i;
	}
	return (sum_str(chunk));
}

