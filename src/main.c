
#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (argc != 2 && argv)
	{
		init_data(envp);
		while (1)
		{
			environment_signals();
			line = readline("minishell--> ");
			if (check_input(line))
				continue ;
			add_history(line);
			if (parsing_input(line))
				continue ;
			check_and_execute(data()->cmds);
			// test(data()->cmds);
			// clear_memory(data()->cmds);
		}
	}
	return (0);
}
