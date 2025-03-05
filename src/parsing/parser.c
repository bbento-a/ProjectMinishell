
#include "../../inc/minishell.h"

int	parse_line(char *line, t_command **cmds)
{
	t_line *prompt;

	prompt = NULL;
	if (syntax_checker(line, &prompt))
	{
		free(line);
		return (1);
	}
	free(line);
	if (search_expansion(&prompt))
	{
		clear_linelst(&prompt);
		return (1);
	}
	if (handle_wspaces(prompt))
	{
		clear_linelst(&prompt);
		return (1);
	}
	if (parse_list(prompt, cmds))
		return (1);
	return (0);
}

int	parsing_input(char *line)
{
	t_command	*cmds;

	cmds = NULL;
	data()->error_parse = false;
	if (parse_line(line, &cmds))
	{
		if (cmds)
			free_cmds(&cmds);
		return (1);
	}
	data()->cmds = cmds;
	return (0);
}
