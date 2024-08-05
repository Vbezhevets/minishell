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
	// if (token->type > 2)
	// 	node->quot = 0;
	// else
	//  	node->quot = token->type;
	// node->value = token->value;
	node->value = (char *)malloc(sizeof(char) * (token->length + 1));
	// if
	ft_strcpy(node->value, token->value);
	// if (!token->exp)
	// 	free(token->value);
	// token->value = NULL;
	node->exp = token->exp;
 	return node;
}

void *parse_redir(t_token **token, t_node *left)
{
	t_node	*rdr_node;
	t_token	*file_token;
 
	*token = expand_tokens(token);
	file_token = (*token)->next;
	if (!file_token || file_token->type > 2)
		error("wrong redirect", NULL, (*token)->data, 2);
	while(left && left->left)
		left = left->left; // go to the edge to write on last leaf of brench to begin redirect from this
	rdr_node = create_node(RDRCT_NODE, (*token)->data);
	rdr_node->left = tok_to_nod(expand_tokens(&file_token)); //expand or just get rid q?
	rdr_node->left->type = (*token)->type + 10; // assign type of redirect to file-token;
	rdr_node->left->left = tok_to_nod(*token); //
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
	else if (*token && (*token)->P < 3) // word == 1
		parse_cmd(token, &cmd_node->right);
	else 
	{
		error("wrong input!!", NULL, (*token)->data, 2);
		return (NULL);
	}
	parse_cmd_node(token, cmd_node); 
	return (cmd_node);
}

t_node *parser_error(t_data *data)
{
	error("wrong input", NULL, data, 2);
	return create_node(ERROR, data);
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
		if (*token && (*token)->type == PIPE && (*token)->exp == 1)
		{
			if (!cmd_node)
				pipe_node->right = parser_error(data);
			else
			{
				pipe_node = tok_to_nod(*token);
				pipe_node->left = cmd_node;
				*token = (*token)->next;
				if (!*token || ((*token)->P != 1 && (*token)->P != 2))
					pipe_node->right = parser_error(data);
				else 
					pipe_node->right = parse_loop(token, NULL, NULL);
			return(pipe_node);
			}
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
	// print_tree(data->tree, 0);
	if (!data->tree)
		return (0);
	return (1);
}