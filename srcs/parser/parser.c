#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell.h"


t_node	*create_node(t_type type)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		error("alloc error");
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == CMD_NODE)
		node->value = "CMD_NODE"; //
	if (type == RDRCT_NODE)
		node->value = "RDRCT_NODE"; //
	return(node);
}


t_node* tok_to_nod(t_token *token)
{
	t_node *node;

	node = create_node(token->type);
	node->P = token->P;
	if (token->type > 2)
		node->quot = 0;
	else
	 	node->quot = token->type;
	node->value = token->value;
 	return node;
}

void *parse_redir(t_token **token, t_node *left)
{
	t_node	*rdr_node;
 
	*token = expand_tokens(token);
	if (!(*token)->next || (*token)->next->type > 2)
		error("wrong redirect");
	while(left && left->left)
		left = left->left;
	rdr_node = create_node(RDRCT_NODE);
	rdr_node->left = tok_to_nod((*token)->next);
	rdr_node->left->type = (*token)->type + 10; // assign type of redirect to file-token;
	rdr_node->left->left = tok_to_nod(*token);
	*token = (*token)->next;
	*token = (*token)->next;
	if (*token && (*token)->P == 2) // also "$"
		rdr_node->right = parse_redir(token, left); // return
	return rdr_node;
}

void parse_cmd(t_token **token, t_node **right)
{
	t_node *temp;

	while((*token) && ((*token)->type < 3))
	{
		*token = expand_tokens(token);
		if (!*right)
		{
			*right = tok_to_nod(*token);
			(*right)->type = CMD;
		}
		else
		{
			temp = tok_to_nod(*token);
			temp->type = ARG;
			temp->right = *right;
			(*right) = temp;
		}
		*token = (*token)->next;
	}
}

t_node *parse_cmd_node(t_token **token, t_node *cmd_node)
{	
	t_node	*left;

	if ((*token && (*token)->type == PIPE) || !*token)
		return cmd_node;
	if (*token && (*token)->P == 2) // rdr
	{	
		left = cmd_node;
		while (left && left->left)
			left = left->left;
		left->left = parse_redir(token, cmd_node->left);
	}
	else if (*token && (*token)->P == 1) // word
		parse_cmd(token, &cmd_node->right);
	else 
		error("wrong input!!");
	return (cmd_node);
	// parse_cmd_node(token, cmd_node);
}

t_node *parse_loop(t_token **token, t_node *cmd_node, t_node *pipe_node)
{
	while (*token)
	{
		*token = expand_tokens(token);
		if (*token && (*token)->P < 3)
		{
			cmd_node = create_node(CMD_NODE);
			cmd_node = parse_cmd_node(token, cmd_node);
		}
		if (*token && (*token)->type == PIPE)
		{
			if (!cmd_node)
				return (error("wrong input!!!"), NULL);
			pipe_node = tok_to_nod(*token);
			pipe_node->left = cmd_node;
			*token = (*token)->next;
			if (!*token || ((*token)->P != 1 && (*token)->P != 2))
				return (error("wrong input"), NULL);
			pipe_node->right = parse_loop(token, NULL, NULL);
			return(pipe_node);
		}
		else
			return cmd_node;
	}
	return (NULL);
}


void parser(t_data *data) 
{
	t_token *start;

	start = data->tok_list;
	data->tree = parse_loop(&start, NULL, NULL);
	
	print_tree(data->tree, 0);
}