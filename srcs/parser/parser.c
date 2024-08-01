#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell.h"


t_node	*create_node(t_type type, t_data *data)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (error("alloc error", NULL, NULL, 2), NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == CMD_NODE)
		node->value = "CMD_NODE"; //
	else if (type == RDRCT_NODE)
		node->value = "RDRCT_NODE"; //
	else 
		node->value = NULL;
	return(node);
}


t_node* tok_to_nod(t_token *token)
{
	t_node *node;

	node = create_node(token->type, token->data);
	node->P = token->P;
	if (token->type > 2)
		node->quot = 0;
	else
	 	node->quot = token->type;
	node->value = token->value;
	node->value = (char *)malloc(sizeof(char) * (token->length + 1));
	// if
	ft_strcpy(node->value, token->value);
	node->exp = token->exp;
 	return node;
}

void *parse_redir(t_token **token, t_node *left)
{
	t_node	*rdr_node;
 
	*token = expand_tokens(token);
	if (!(*token)->next || (*token)->next->type > 2)
		error("wrong redirect", NULL, (*token)->data, 2);
	while(left && left->left)
		left = left->left;
	rdr_node = create_node(RDRCT_NODE, (*token)->data);
	rdr_node->left = tok_to_nod((*token)->next);
	rdr_node->left->type = (*token)->type + 10; // assign type of redirect to file-token;
	rdr_node->left->left = tok_to_nod(*token);
	*token = (*token)->next;
	*token = (*token)->next;
	if (*token && (*token)->P == 2)
		rdr_node->right = parse_redir(token, left); // return
	return rdr_node;
}

void parse_cmd(t_token **token, t_node **right)
{
	t_node *temp;

	while((*token) && ((*token)->type < 3)) // word or feilds in quotes
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
	{
		error("wrong input!!", NULL, (*token)->data, 2);
		return (NULL);
	}
	parse_cmd_node(token, cmd_node); 
	return (cmd_node);
}

t_node *parse_loop(t_token **token, t_node *cmd_node, t_node *pipe_node)
{
	t_data* data;

	data = (*token)->data;
	while (*token)
	{
		*token = expand_tokens(token); //tok_detect?
		if (*token && (*token)->P < 3)
		{
			cmd_node = create_node(CMD_NODE, (*token)->data);
			cmd_node = parse_cmd_node(token, cmd_node);
		}
		if (*token && (*token)->type == PIPE)
		{
			if (!cmd_node)
				return (error("wrong input!!!", NULL, data, 2), NULL);
			pipe_node = tok_to_nod(*token);
			pipe_node->left = cmd_node;
			*token = (*token)->next;
			if (!*token || ((*token)->P != 1 && (*token)->P != 2))
				return (error("wrong input", NULL, data, 2), NULL);
			pipe_node->right = parse_loop(token, NULL, NULL);
			return(pipe_node);
		}
		else
			return cmd_node;
	}
	return (NULL);
}


int parser(t_data *data) 
{
	t_token *start;

	start = data->tok_list;
	data->tree = parse_loop(&start, NULL, NULL);
	if (!data->tree)
		return (0);
	return (1);
	// print_tree(data->tree, 0);
}