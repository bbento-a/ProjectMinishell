/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:40:47 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 07:40:56 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// To handle Ctrl D (EOF)

int	check_input(char *line)
{
	if (line == NULL)
	{
		rl_clear_history();
		clear_env(data()->env);
		ft_printf("exit\n");
		exit(0);
	}
	else if (ft_strlen(line) == 0)
	{
		data()->exit_code = 0;
		free(line);
		return (1);
	}
	return (0);
}
