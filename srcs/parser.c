#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"


t_node* create_node(t_type type) //CMD
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		error("alloc error");
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == CMD)
		node->value = "CMD";
	if (type == RDRCT)
		node->value = "RDRCT";
	return(node);
}


t_node* tok_to_nod(t_token *token)
{
	t_node *node;

	node = create_node(token->type);
	node->P = token->P;
	node->value = token->value;
 	return node;
}

t_node *parse_redir(t_node *left, t_token **token)
{
	t_node *rdr_node;
	t_node *temp;

	temp = left;
	if (!(*token)->next || (*token)->next->type != WORD)
		error("wrong redirect");
	while(temp && temp->left)
		temp = temp->left;
	rdr_node = create_node(RDRCT);
	rdr_node->left = tok_to_nod((*token)->next);
	rdr_node->left->left = tok_to_nod(*token);
	*token = (*token)->next;
	*token = (*token)->next;
	if (*token && (*token)->P == 2)
		rdr_node->right = parse_redir(left, token); // return
	if (temp)
		temp->left = rdr_node;
	return (rdr_node);
}
// void consume(t_token **token)
// {
// 	t_token *temp;

// 	temp = tok_to_nod(*token);
// 	*token = (*token)->next; 
// }

t_node *parse_cmd(t_token **token, t_node *right)
{
	t_node *cmd_node;
	t_node *temp;

	cmd_node = create_node(CMD);
	if (*token && (*token)->P == 2)
		cmd_node->left = parse_redir(NULL, token);
	// if ((*token) && (*token)->type != WORD)
	// 	error("wrong command");
	while((*token) && (*token)->type == WORD)
	{
		if (!right)
		{
			cmd_node->right = tok_to_nod(*token);
			right = cmd_node->right;
		}
		else
		{
			temp = tok_to_nod(*token);
			temp->right = cmd_node->right;
			cmd_node->right = temp;
		}
		*token = (*token)->next;
	}
	if (*token && (*token)->P == 2)
		parse_redir(cmd_node->left, token);
	return (cmd_node);
}

t_node *parse_loop(t_token **token, t_node *cmd_node)
{
	t_node *pipe_node;
	
	while (*token)
	{
		if (*token && (*token)->P < 3)
			cmd_node = parse_cmd(token, NULL);
		if (*token && (*token)->type == PIPE)
		{
			if (!cmd_node)
				return (error("wrong input"), NULL);
			pipe_node = tok_to_nod(*token);
			pipe_node->left = cmd_node;
			*token = (*token)->next;
			if (!*token || ((*token)->P != 1 && (*token)->P != 2))
				return (error("wrong input"), NULL);
			pipe_node->right = parse_loop(token, NULL); 
			return(pipe_node);
		}
		else 
			return cmd_node;
	}
	return (NULL);
}

void print_tree(t_node *node, int intent)
{
	if (!node)
		return;
	int i = intent;


	if (node->left)
	{	
		print_tree(node->left, intent + 1);
	}

	while (i > 0)
	{
		printf("+---");
		i--;
	}
	printf("%s\n", node->value);

	if (node->right)
	{
		// printf("right");
		print_tree(node->right, intent + 1);
	}


}


void parser(t_data *data) 
{
	t_token *start;

	start = data->tok_list;
	data->tree = parse_loop(&start, NULL);
	
	print_tree(data->tree, 0);
}