#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define DELIM " \n\t"

typedef enum s_type
{
	WORD, 	//0
	FIELD,	//1
	EXP_FIELD,//2
	LR,		//3
	RL,		//4
	LRLR,	//5
	RLRL,	//6
	RDRCT_NODE,//7
	PIPE,	//8
	CMD_NODE,//9
	EMPTY,	//10
	CMD,	//11
	ARG,	//12
	TO_FILE,//13
	FROM_FILE,//14
	TO_TO_FILE,//15
	HEREDOC,//16
}	t_type;

static const char *const builtins[] = {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit"
};


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
	int				quot;
}	t_node;


// typedef struct s_builtins
// {
// 	char			*echo;
// }	t_builtins

typedef struct s_cmd

{
	int		bi;
	int		pid;
	int		from_fd;
	int		to_fd;
	int		num;
	int		args_qty;
	int		interp;
	char	**args;
	char	*path;
	t_token	*to_file; //to
	// t_token	*to_to_file; //to
	t_token	*from_file; //from
	char	*her_doc; //from
	struct s_cmd	*next;
	struct s_cmd	*prev;

}	t_cmd;

typedef struct s_data
{
	int		tok_quantity;
	int		cmd_qty;//
	// int		cmd_num;
	t_cmd	*cmd_list;
	t_token	*tok_list;
	t_node	*tree;
	int		pipe[2];
	char	**envp;
}	t_data;



void	tokenizer(char *input_str, t_data *data);
void 	parser(t_data *data);
void 	travel_tree(t_node *node,  int depth, t_data *data);
t_token	*create_tok(char *input_str);
t_cmd	*init_cmd(t_data *data, t_cmd *prev);
void 	handle_cmd_args(t_node *node, t_cmd *cmd);
int		handle_cmd(t_data *data, t_cmd *cmd);
int		exec(t_data *data, t_cmd *cmd);
int 	builtin(t_cmd *cmd, t_data *data);

void	error(char *str);
void	free_all(t_data *data);
void	free_and_null_(char **a);

void print_cmd_fields(t_cmd **cmd_array, int cmd_count); //remove





// t_node* token_to_node(t_token *token);
// void print_tokens(t_token *tok);
// testing: 



#endif