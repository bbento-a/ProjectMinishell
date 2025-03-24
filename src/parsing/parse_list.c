/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:40:32 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/24 10:54:23 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_redir_syntax(t_line *token)
{
	if (token->type_n == E_REDIN)
		display_err(NULL, NULL, "Syntax error near '<' token", 2);
	if (token->type_n == E_HERDOC)
		display_err(NULL, NULL, "Syntax error near '<<' token", 2);
	if (token->type_n == E_REDOUT)
		display_err(NULL, NULL, "Syntax error near '>' token", 2);
	if (token->type_n == E_APPEND)
		display_err(NULL, NULL, "Syntax error near '>>' token", 2);
}

void	check_token_syntax(t_line *tokens)
{
	while (tokens)
	{
		if (tokens->type_n < E_PIPE)
		{
			if (!tokens->next || tokens->next->type_n != E_OTHER)
			{
				print_redir_syntax(tokens);
				data()->error_parse = true;
				break ;
			}
		}
		if (tokens->type_n == E_PIPE)
		{
			if (!tokens->next || !tokens->prev
				|| tokens->next->type_n == E_PIPE)
			{
				display_err(NULL, NULL, "Syntax error near '|' token", 2);
				data()->error_parse = true;
				break ;
			}
		}
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
}

static int	create_cmd_node(t_command **cmds, t_line *bgn, t_line *last)
{
	t_command	*node;
	int			n_args;

	node = my_malloc(sizeof(t_command));
	if (!node)
		return (display_err(NULL, NULL, "Error allocating command node", 1));
	node->args = NULL;
	n_args = handle_node_args(bgn, last);
	node->args = my_malloc(sizeof(char *) * (n_args + 1));
	make_cmd_args(node->args, bgn, last, n_args);
	node->previous = NULL;
	node->next = NULL;
	node->files = make_cmd_files(bgn, last);
	add_cmds_last(cmds, node);
	return (0);
}

int	create_cmd_list(t_line *tokens, t_command **cmds)
{
	t_line	*last_token;

	while (tokens)
	{
		last_token = tokens;
		while (last_token->next && last_token->type_n != E_PIPE)
		{
			last_token = last_token->next;
		}
		if (create_cmd_node(cmds, tokens, last_token))
			return (1);
		tokens = last_token->next;
	}
	return (0);
}

int	parse_list(t_line *tokens, t_command **cmds)
{
	if (create_cmd_list(tokens, cmds))
	{
		clear_linelst(&tokens);
		return (1);
	}
	clear_linelst(&tokens);
	return (0);
}
