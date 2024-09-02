/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:59:56 by bvalerii          #+#    #+#             */
/*   Updated: 2024/08/20 11:56:10 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*create_node(t_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (error("all1c error", NULL, NULL, 2), NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == CMD_NODE)
		node->value = "CMD_NODE";
	else if (type == RDRCT_NODE)
		node->value = "RDRCT_NODE";
	else if (type == ERROR)
		node->value = NULL;
	return (node);
}

t_node	*tok_to_nod(t_token *token)
{
	t_node	*node;

	node = create_node(token->type);
	if (!node)
		return (NULL);
	node->p = token->p;
	node->value = malloc(sizeof(char) * (token->length + 1));
	if (!node->value)
	{
		fnl(node);
		return (NULL);
	}
	ft_strcpy(node->value, token->value);
	node->exp = token->exp;
	return (node);
}

void	*parse_redir(t_token **token, t_node *left)
{
	t_node	*rdr_node;
	t_token	*file_token;

	file_token = (*token)->next;
	if (!file_token || file_token->type > 2)
		error("wrong redirect", NULL, (*token)->data, 2);
	while (left && left->left)
		left = left->left;
	rdr_node = create_node(RDRCT_NODE);
	if ((*token)->type + 10 != HEREDOC)
		rdr_node->left = tok_to_nod(expand_tokens(&file_token));
	else
		rdr_node->left = tok_to_nod((*token)->next);
	rdr_node->left->type = (*token)->type + 10;
	rdr_node->left->left = tok_to_nod(*token);
	*token = (*token)->next;
	*token = (*token)->next;
	if (*token && (*token)->p == 2)
		rdr_node->right = parse_redir(token, left);
	return (rdr_node);
}

void	parse_cmd(t_token **token, t_node **right)
{
	t_node	*temp;

	while ((*token) && ((*token)->type < 3))
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

t_node	*parse_cmd_node(t_token **token, t_node *cmd_node)
{
	t_node	*left;

	if ((*token && (*token)->type == PIPE) || !*token)
		return (cmd_node);
	if (*token && (*token)->p == 2)
	{
		left = cmd_node;
		while (left && left->left)
			left = left->left;
		if (cmd_node != NULL)
			left->left = parse_redir(token, (*cmd_node).left);
	}
	else if (*token && (*token)->p < 3 && cmd_node)
		parse_cmd(token, &cmd_node->right);
	else
	{
		error("wrong input!!", NULL, (*token)->data, 2);
		return (NULL);
	}
	parse_cmd_node(token, cmd_node);
	return (cmd_node);
}

t_node	*parser_error(t_data *data)
{
	error("wrong input", NULL, data, 2);
	data->ok = 0;
	return (create_node(ERROR));
}

void	assign_pipe_node(t_token *token, t_node *pipe_node, t_data *data)
{
	if (!token || ((token)->p != 1 && (token)->p != 2))
		pipe_node->right = parser_error(data);
	else
		pipe_node->right = parse_loop(&token, NULL, NULL, data);
}

t_node	*parse_loop(t_token **token, t_node *cmd_node, t_node *pipe_node, t_data *data)
{
	while (*token)
	{
		*token = expand_tokens(token);
		if (*token && (*token)->p < 3)
		{
			cmd_node = create_node(CMD_NODE);
			cmd_node = parse_cmd_node(token, cmd_node);
		}
		if (*token && (*token)->type == PIPE && (*token)->exp == 1)
		{
			if (!cmd_node)
				return (parser_error(data));
			else
			{
				pipe_node = tok_to_nod(*token);
				pipe_node->left = cmd_node;
				*token = (*token)->next;
				assign_pipe_node(*token, pipe_node, data);
				return (pipe_node);
			}
		}
		else
			return (cmd_node);
	}
	return (NULL);
}

int	parser(t_data *data)
{
	t_token	*start;

	start = data->tok_list;
	data->tree = parse_loop(&start, NULL, NULL, data);
	if (!data->tree)
		return (0);
	return (1);
}