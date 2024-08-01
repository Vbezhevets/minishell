/*
/bin/echo '"$USER"'
quotes error 


/bin/echo '"'"$USER"'"'
'"'

/bin/echo ''$?''"42"


он открывает за одну проходку вариативность кавычек 
если одни в других - их не трогает
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
	while (prev->prev)
		prev = prev->prev;
	chunk = prev;
	next = chunk;
	while (next)
	{
		res = (free_join(res, next->str));
		free(chunk->prev);
		next->prev = NULL;
		next = next->next;
	}
	// free(next->str);
	free(next);
	if (!ft_strlen(res))
		return (allocpy("\0"));
	return (res);
}
/*
char *del_quotes(char *str, char q, int i, int f)
{
	char	*res;
	int		start;
	t_str	*chunk;
	int		end;

	res = NULL;
	while (str[++i])
		// if (i > 0 && str[i] == q)
		// {
		// 	chunk = add_chunk(NULL, str, 0, i++);
		// 	break;
		// }
	while (str[i])
	{
		if (str[i] == q)
		{
			i++;
			if (f == 0)
			{
				start = i;
				f = 1;
			}
			else
			{
				chunk = add_chunk(chunk, str, start, i);
				f = 0;
				end = i;
			}
		}
		i++;
		if (!str[i] && i > end)
			chunk = add_chunk(chunk, str, end, i);
	}
	res = (sum_str(chunk));
	if (!res)
		return (allocpy("\0")); //need free
	return res;
} */

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

// char	*get_rid_q(char *input, t_token *token)
// {
// 	char	*res;
// 	int		i;
// 	char	q;
// 	char    Q;

// 	q = '\'';
// 	Q = '\"';
// 	if (token)
// 		token->exp = 0;
// 	i = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == q || input[i] == Q)
// 			break;
// 		i++;
// 	}
// 	if (input[i] == q || (input[i] == Q))
// 	{
// 		res = del_quotes(input, input[i], 0, -1);
// 		if (strcmp(res, input))
// 			free(input);
// 	}
// 	else
// 		return (input);
// 	return (res);
// }

