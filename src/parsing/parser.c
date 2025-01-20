
#include "../inc/minishell.h"

int	parse_line(char *line, t_line **prompt, t_command **cmds)
{
	if (syntax_checker(line, prompt))
	{
		free(line);
		return (1);
	}
	free(line);
	if (search_expansion(prompt))
		return (1);
	if (handle_wspaces(*prompt))
		return (1);
	*cmds = parse_list(*prompt);
	if (!*cmds)
		return (1);
	clear_linelst(prompt);
	return (0);
}

int	parsing_input(char *line)
{
	t_line		*prompt;
	t_command	*cmds;

	prompt = NULL;
	cmds = NULL;
	data()->error_parse = false;
	if (parse_line(line, &prompt, &cmds))
	{
		if (prompt)
			clear_linelst(&prompt);
		if (cmds)
			free_cmds(&cmds);
		return (1);
	}
	data()->cmds = cmds;
	return (0);
}
