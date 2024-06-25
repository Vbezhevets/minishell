#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"

# define DELIM " \n\t"

typedef enum s_type
{
	WORD, 	//0
	LR,		//1
	RL,		//2
	LRLR,	//3
	RLRL,	//4
	FIELD,	//5
	EXP_FIELD,//6
	RDRCT_NODE,//7
	CMD,	//8
	ARG,	//9
	PIPE,	//10
	TO_FILE,//11
	FROM_FILE,//12
	TO_TO_FILE,//13
	HEREDOC,//14
	CMD_NODE//15
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

typedef struct s_cmd
{
	int		in;
	int		out;
	t_token	*to_file; //to
	t_token	*to_to_file; //to
	t_token	*from_file; //from
	t_token	*args;
	char	*her_doc; //from
}	t_cmd;

typedef struct s_data
{
	int		tok_quantity;
	int		cmd_qty;
	int		cmd_num;
	t_token	*tok_list;
	t_node	*tree;
	t_cmd	**cmd;
	int		pipe[2];
}	t_data;



void	tokenizer(char *input_str, t_data *data);
void 	parser(t_data *data);
void	error(char *str);
void	free_tree(t_node *node);
void	free_tok(t_token *token);
void 	travel_tree(t_node *node,  int depth, t_data *data);
t_token	*create_tok(char *input_str);
t_cmd	*init_cmd(t_data *data);



// t_node* token_to_node(t_token *token);
// void print_tokens(t_token *tok);
// testing: 



#endif