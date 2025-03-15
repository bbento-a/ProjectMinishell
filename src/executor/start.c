/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:42:40 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 04:43:39 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_command *command)
{
	int	ret_val;

	if (command->next)
		ret_val = handle_pipes(command, data()->env);
	else
		ret_val = exec_bin(command, data()->env);
	return (ret_val);
}
