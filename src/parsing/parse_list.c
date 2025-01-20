
#include "../inc/minishell.h"

// Checks for any syntax errors before parsing into lists and creating command
// nodes. If there is an error, then the list won't be created in parse_list()

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
// Creates a command node, initializes all variables, and creates an array for
// arguments, and creates lists for in/out_files (redirections)

static int	create_cmd_node(t_command **cmds, t_line *bgn, t_line *last)
{
	t_command	*node;
	int			n_args;

	node = malloc(sizeof(t_command));
	if (!node)
		return (display_err(NULL, NULL, "Error allocating command node", 1));
	node->path = NULL;
	node->args = NULL;
	n_args = handle_node_args(bgn, last);
	node->args = malloc(sizeof(char *) * (n_args + 1));
	make_cmd_args(node->args, bgn, last, n_args);
	node->previous = NULL;
	node->next = NULL;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->pipe_fd[PIPE_READ] = -1;
	node->pipe_fd[PIPE_WRITE] = -1;
	node->pipe_is_active = false;
	node->in_file = make_cmd_files(bgn, last, 'i');
	node->out_file = make_cmd_files(bgn, last, 'o');
	node->is_builtin = false;
	node->exit_status = -1;
	node->pid = -1;
	add_cmds_last(cmds, node);
	return (0);
}
// Creates a list with nodes based on pipes in the line

t_command	*create_cmd_list(t_line *tokens)
{
	t_command	*cmds;
	t_line		*last_token;

	cmds = NULL;
	while (tokens)
	{
		last_token = tokens;
		while (last_token->next && last_token->type_n != E_PIPE)
		{
			last_token = last_token->next;
		}
		if (create_cmd_node(&cmds, tokens, last_token))
			return (NULL);
		tokens = last_token->next;
	}
	return (cmds);
}
// Main function of the parsing for commands lists. It will check for syntax
// errors and if not it will proceed to creating a list of commands for the
// executor.

t_command	*parse_list(t_line *tokens)
{
	t_command	*cmds_list;

	cmds_list = NULL;
	if (!data()->error_parse)
		cmds_list = create_cmd_list(tokens);
	return (cmds_list);
}
