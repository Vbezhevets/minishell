#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"

# define DELIM "/t "

typedef enum s_type
{
	WORD,
	CMD,
	ARG,
	LR,
	RL,
	LRLR,
	RLRL,
	PIPE,
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	int 			length;
	int				P;//recedence
	struct	s_token	*next;
	struct	s_token	*prev;
}	t_token;

typedef struct s_node
{
	t_type			type;
	char			*value;
	struct	s_node	*left;
	struct	s_node	*right;
	int				P;
}	t_node;

typedef struct s_data
{
	int		tok_qty;
	t_token	*tok_list;
	t_node	*low_left_node;
}	t_data;


void	tokenizer(char *input_str, t_data *data);
void 	parser(t_data *data);
int		error(char *str);
// t_node* token_to_node(t_token *token);
void print_tokens(t_token *tok);
t_node *climb_test(t_token *token, int min_precedence);



#endif