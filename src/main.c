/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:40:26 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 07:40:29 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (data()->cmds)
				clear_memory(data()->cmds);
		}
	}
	return (0);
}
