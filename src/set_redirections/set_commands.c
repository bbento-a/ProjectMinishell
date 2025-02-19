/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:30:06 by bbento-a          #+#    #+#             */
/*   Updated: 2025/02/19 15:10:45 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_and_execute(t_command *commands)
{
	if (!commands)
		return (1);
	if (check_redirections(commands)) // if terminated by SIGINT
	{
		//clean_up close_fds
		return (1);
	}
	
	return (0);
}
