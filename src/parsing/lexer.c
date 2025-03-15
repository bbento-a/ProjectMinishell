/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:39:49 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:40:14 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	create_node(t_line **prompt, char *line, int bgn, int len)
{
	t_line	*new_node;
	t_line	*last_node;

	new_node = my_malloc(sizeof(t_line));
	if (!new_node)
		return (display_err(NULL, NULL, "Error allocating new node", 1));
	new_node->content = ft_substr(line, bgn, len);
	new_node->type_q = data()->hld_flag;
	new_node->type_n = define_type(new_node);
	new_node->arg = false;
	new_node->next = NULL;
	if (!(*prompt))
	{
		*prompt = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last_node = find_lastnode(*prompt);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	define_white_space(new_node, line, bgn);
	return (0);
}

static int	create_redir_pipe(t_line **prompt, char *line, int bgn)
{
	if ((line[bgn] == '>' && line[bgn + 1] == '>') || (line[bgn] == '<'
			&& line[bgn + 1] == '<'))
	{
		if (create_node(prompt, line, bgn, 2))
			return (data()->error_parse = true);
		return (bgn + 2);
	}
	else if (line[bgn] == '>' || line[bgn] == '<' || line[bgn] == '|')
	{
		if (create_node(prompt, line, bgn, 1))
			return (data()->error_parse = true);
		return (bgn + 1);
	}
	return (bgn);
}

static int	create_quotes(t_line **prompt, char *line, int bgn)
{
	int	i;
	int	end;

	i = bgn;
	end = 0;
	if (line[bgn] == '\'' || line[bgn] == '\"')
	{
		i++;
		while (line[i] && line[i] != data()->hld_flag)
		{
			end++;
			i++;
		}
		if (line[i] != data()->hld_flag)
		{
			display_err(NULL, NULL, "Syntax error: Unclosed quotes", 2);
			data()->error_parse = true;
			return (0);
		}
		if (create_node(prompt, line, bgn + 1, end))
			return (data()->error_parse = true);
	}
	return (i + 1);
}

static int	create_default(t_line **prompt, char *line, int i)
{
	int	bgn;
	int	end;

	bgn = i;
	end = 0;
	while (line[i] && !symbol_cmp("|<> '\"\t", line[i]))
	{
		i++;
		end++;
	}
	if (create_node(prompt, line, bgn, end))
		return (data()->error_parse = true);
	return (i);
}

int	syntax_checker(char *line, t_line **prompt)
{
	int	i;
	int	bgn;

	i = 0;
	bgn = 0;
	while (line[i] && !data()->error_parse)
	{
		if (line[i] && (line[i] == ' ' || line[i] == '\t') && line[i++])
			continue ;
		bgn = i;
		define_flg(line[i]);
		if (!line[i] || line[i] == ' ' || line[i] == '\t')
			i = -1;
		else if (line[i] && (line[bgn] == '\'' || line[bgn] == '\"'))
			i = create_quotes(prompt, line, bgn);
		else if (line[i] && (line[bgn] == '>' || line[bgn] == '<'
				|| line[bgn] == '|'))
			i = create_redir_pipe(prompt, line, bgn);
		else
			i = create_default(prompt, line, i);
	}
	check_token_syntax(*prompt);
	if (data()->error_parse)
		return (1);
	return (0);
}
