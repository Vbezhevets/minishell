/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:31:12 by ggero             #+#    #+#             */
/*   Updated: 2024/08/20 11:57:34 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "../libft/libft.h"

# define DELIM " \t\n"
# define DELIMQ " \n\t\"\'"
# define Q '\''
# define QQ '\"'

# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

extern int	g_quit;

typedef enum s_type
{
	WORD,
	FIELD,
	EXP_FIELD,
	LR,
	RL,
	LRLR,
	RLRL,
	RDRCT_NODE,
	PIPE,
	CMD_NODE,
	ERROR,
	CMD,
	ARG,
	TO_FILE,
	FROM_FILE,
	TO_TO_FILE,
	HEREDOC,
}	t_type;

struct		s_data;

typedef struct s_token
{
	t_type			type;
	char			*value;
	int				length;
	int				p;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_data	*data;
	int				exp;
}	t_token;

typedef struct s_cmd_field
{
	t_type				type;
	char				*value;
	int					length;
	int					p;
	struct s_cmd_field	*next;
	struct s_cmd_field	*prev;
}	t_cmd_field;

typedef struct s_node
{
	t_type			type;
	char			*value;
	struct s_node	*left;
	struct s_node	*right;
	int				p;
	int				quot;
	int				exp;
}	t_node;

// typedef struct s_BUILTINS
// {
// 	char			*echo;
// }	t_BUILTINS

typedef struct s_cmd
{
	int				bi;
	int				pid;
	int				ex_stat;
	int				from_fd;
	int				to_fd;
	int				num;
	int				args_qty;
	int				interp;
	char			**args;
	char			*path;
	t_cmd_field		*to_file;
	t_cmd_field		*to_to_file;
	t_cmd_field		*from_file;
	char			**her_doc;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				ok;
}	t_cmd;

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_str
{
	char			*str;
	struct s_str	*next;
	struct s_str	*prev;
}	t_str;

typedef struct s_data
{
	int		tok_quantity;
	int		cmd_qty;
	t_cmd	*cmd_list;
	t_token	*tok_list;
	t_node	*tree;
	int		std_in;
	int		std_out;
	int		prev_pipe[2];
	int		next_pipe[2];
	int		pipe[2];
	int		ex_stat;
	char	**envp;
	char	cwd[8192];
	int		envpc;
	t_var	*var;
	int		f;
	char	*temp;
	int		fds[1024];
	int		fds_c;
	int		ok;
	int		hd;
	int		prev_s;
	char	**temp_envp;
	char	**temp_exists;
	char	**temp_arr;
	char	*builtins[8];
}	t_data;

int			parser(t_data *data);
t_node		*parse_loop(t_token **token, t_node *cmd_node,
				t_node *pipe_node, t_data *data);
void		travel_tree(t_node *node, int depth, t_data *data);
t_cmd		*init_cmd(t_data *data, t_cmd *prev);
void		handle_cmd_args(t_node *node, t_cmd *cmd);
void		handle_cmd(t_data *data, t_cmd *cmd);
int			exec(t_data *data, t_cmd *cmd);
int			builtin(t_cmd *cmd, t_data *data);
t_cmd_field	*create_field(char *input_str, int type);

t_token		*tokenizer(char *input_str, t_data *data,
				t_token *tok_list, int expanded);

t_token		*expand_tokens(t_token **in_token);

t_token		*create_tok(char *input_str, t_data *data, int expanded);

void		zeroing_data(t_data *data);

int			redirect(t_cmd **cmd, t_data *data);
//int		rdr(t_cmd_field *file, t_data *data, int drct);

int			envpcpy(char **src_envp, char ***dst_envp, t_data *data);
int			exp0rt(char *arg, t_data *data);
t_var		*var_init(char *name);
char		*exp_var(char *var_name, t_data *data, char **str);
int			unset(char *var_name, t_data *data, int i, int k);
int			check_var_name(char *name);
int			del_var(char *var_name, t_var *var, t_data *data, int *k);
int			add_env_var(char *add_str, t_data *data, char *temp_str, int i);

int			strnlcmp(char *str1, char *str2);
char		*get_rid_q(char *input, int i, int start, t_str *chunk);
int			ft_strset(char *str, char *set);
char		**add_str_arr(char **old, char *str);
int			is_empty(char *str);
int			chr_mlc(char ***arr, int i);
int			splt_mlc(char ***splited, char *to_split, char delim);

void		error(char *s1, char *s2, t_data *data, int e_number);
void		free_all(t_data *data);
void		free_and_null_(char **a);
void		f_till(char **a, int c);
void		free_var(t_var *var);
void		free_tok(t_token *token);
int			my_exit(t_data *data, char *error_msg);
int			check_var_name(char *name);
void		ch3to_null(char **one, char **two, char **three);
void		fnl(void *pntr);

int			del_temp_hd(t_data *data);

void		print_tree(t_node *node, int intent);
void		print_cmd_fields(t_cmd **cmd_array, int cmd_count); //remove

void		handle_heredoc(char *delim, t_data *data);
void		free_tree(t_node *node);
char		*expand_str(char *str, t_data *data, char *res, char *beg);
int			no_extr_need(char *str, char q);
t_node		*create_node(t_type type);
t_node		*tok_to_nod(t_token *token);
t_node		*parse_cmd_node(t_token **token, t_node *cmd_node);
int			precedence(t_token *token);
int			ft_length(char *s);
int			tok_detect(char *token_value, int exp);
int			reset_descrpt(t_data *data);
int			check_cmd(t_cmd **cmd, t_data *data);
void		assign_fild(t_node *node, t_cmd *cmd);
void		add_cmd(t_cmd *cmd, t_data *data);
char		*heredoc_prompt(const char *const delim);
int			add_envp_str_and_var(char *new_var_str, t_data *data, int i);
int			cd(char *n, t_data *data);
int			pwd(void);
int			env(t_data *data);
#endif