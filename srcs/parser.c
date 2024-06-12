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
	{
		node->value = (char *)malloc((4) * sizeof(char));
		node->value = "CMD\0";
	}
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


t_node *parse_cmd(t_token **token, t_node *right)
{
	t_node *cmd_node;

	cmd_node = create_node(CMD);
	cmd_node->left = tok_to_nod(*token);
printf("%s : left<-CMD\n", cmd_node->left->value);
	*token = (*token)->next;
	while((*token) && (*token)->type == WORD)
	{
		if (!right)
		{
			cmd_node->right = tok_to_nod(*token);
			right = cmd_node->right;
		}
		else
		{
			right->right = tok_to_nod(*token); // вызвать специальную функцию для обработки слов и кавыяе
			right = right->right;
		}
printf("		CMD->right : %s\n", right->value);
		*token = (*token)->next;
	}
	if (*token && (*token)->P == 2 && (*token)->next->type == WORD)
	{
		cmd_node->left->left = tok_to_nod(*token);
		*token = (*token)->next;
		cmd_node->left->left->right = tok_to_nod(*token);
		*token = (*token)->next;
	}
	return (cmd_node);
}

t_node *parse_loop(t_token **token, t_node *cmd_node)
{
	t_node *pipe_node;

	while (token)
	{
		if ((*token)->type == WORD)
			cmd_node = parse_cmd(token, NULL);
		if (*token && (*token)->type == PIPE)
		{
			if (!cmd_node)
				return (error("wrong input"), NULL);
			pipe_node = tok_to_nod(*token);
			pipe_node->left = cmd_node;
printf("%s <-CMD <-|\n", cmd_node->left->value);

			*token = (*token)->next;
			if (!*token || (*token)->type != WORD)
				return (error("wrong input"), NULL);
			pipe_node->right= parse_loop(token, NULL); // что вернет ? тоже надо брать адрес с указателя?
printf("|-> %s\n", pipe_node->right->left->value);
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
	while (i > 0)
	{
		printf("-\t");
		i--;
	}
	printf("%s\n", node->value);
	if (node->left)
	{	
		printf("left");
		print_tree(node->left, intent + 1);
	}
	if (node->right)
	{
		printf("right");
		print_tree(node->right, intent + 1);
	}

}


void parser(t_data *data) 
{
	data->tree = parse_loop(&data->tok_list, NULL);
	// printf("TYPE: %d\n", data->tree->type);
	// printf("VALUE: %s\n", data->tree->left->left->value );
	print_tree(data->tree, 0);
	printf("!\n");
}