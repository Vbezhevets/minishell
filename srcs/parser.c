#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"




t_node* tok_to_nod(t_token *token)
{
	t_node *node = (t_node *)malloc(sizeof(t_node));
	node->type = token->type;
	node->P = token->P;
	node->value = (token->value);
	node->left = NULL;
	node->right = NULL;

	return node;
}



// t_node *cmd_parse_loop(t_token *token)
// {
	
// 	t_node *node_cmd;
// 	t_node *args;

// 	if (token->P != WORD)
// 		return( error("bad token type"), NULL);
// 	node_cmd = tok_to_nod(token);
// 	if (token->next)
// 		token = token->next;
// 	while  (token && token->type == 1)
// 	{
// 		args = tok_to_nod(token);
// 		if (token->next)
// 			token = token->next
// 	}
// 	return node_cmd;
// }

t_node *parse_cmd(t_token **token)
{
	t_node *cmd_node;
	t_node *right;

	right = NULL;
	cmd_node->left = tok_to_nod(*token);
	cmd_node->right = right;

	while((*token) && (*token)->P == 1)
	{
		*token = (*token)->next;
		right = tok_to_nod(*token);
		right = right->right;
	}
	return (cmd_node);
}

t_node *parse_loop(t_token *token, t_node *cmd_node)
{
	t_node *pipe_node;

	while (token)
	{
		if (token->type == WORD)
			cmd_node = parse_cmd(&token);
		if (token && token->type == PIPE)
		{
			if (!cmd_node)
				return (error("wrong input"), NULL);
			pipe_node = tok_to_nod(token);
			pipe_node->left = cmd_node;
			if (!token->next || token->next->type != WORD)
				return (error("wrong input"), NULL);
			pipe_node->right= parse_loop(token->next, NULL); // что вернет ?
			return(pipe_node);
		}
		else 
			return cmd_node;
	}
}



/*
t_node *parse(t_node *prev_node, t_token *token)
{
	t_node *new_node;

	if (prev_node == NULL)
		new_node = tok_to_nod(token); //check if command
	else
	{
		if (token->P >= prev_node->P)
		{
			new_node = tok_to_nod(token);
			new_node->left = prev_node;
		}
		else
		{	
			new_node = prev_node;
			prev_node->right = parse();
		}
	}
	if (token->next)
		parse(new_node, token->next);
	else
		return(new_node);
}
*/

void parser(t_data *data) 
{
	data->low_left_node = parse_loop(data->tok_list);

}

/*
int parse_expression(const char **expr, int min_precedence) {
	
	int left_operand = parse_primary(expr);
	
	while (1) {
		const char* expr_snapshot = *expr;
		Token token = get_next_token(&expr_snapshot);
		int token_precedence = precedence(token.type);     
		
		if (token_precedence < min_precedence)
		
			break;  //return(left);

		*expr = expr_snapshot;
		int right_operand = parse_expression(expr, token_precedence + 1);
		
		
		switch (token.type) {
			case ADD: left_operand += right_operand; break;
			case SUBTRACT: left_operand -= right_operand; break;
			case MULTIPLY: left_operand *= right_operand; break;
			case DIVIDE: left_operand /= right_operand; break;
			default: break;
		}
		new node = new_node.left = left; new_node  = right;
	}
	
	return left_operand;
}

*/
















// t_node *build_tree (t_token *token)
// {
// 	t_node *node;
// 	t_node *new_node;
// 	t_node *root;
// 	int     max_prec;

// 	if (token)
// 		node = token_to_node(token);
// 	else
// 		return (NULL);
// 	while (token)
// 	{
// 		new_node = token_to_node(token->next);
// 		if (token->next && precedence(token->next) > precedence(token))
// 		{
// 			new_node->left_node = node;
// 			while(node->prec > node->up->prec)
// 			{
// 				node = node->up;
// 				node
// 			}
// 		}
// 		else if (precedence(token->next) <= precedence(token))
// 		{
// 			node->right_node = new_node;
// 			new_node->up = node;
// 		}
// 		node = new_node;
// 		token = token->next;
// 	}
// }




// сделать while выше двигаемся по узлам вверх
// если выше уже нет делаем рут
//   2
//  / \
// 1   1n

// while (node->up->prec < node->prec) 
// {
// 	node->left = node->up->left;
// 	node->right = node->up->right;
// 	if (node->up->up)
// 		node->up = node->up->up;
// 	node

// 	node = node->up;


 