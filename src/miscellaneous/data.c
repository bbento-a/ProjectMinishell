/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:02:15 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 06:02:49 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_data(char **envp)
{
	data()->prompt_flag = true;
	data()->prompt = NULL;
	data()->cmds = NULL;
	data()->error_parse = false;
	data()->exit_code = 0;
	data()->last_exit_status = 0;
	data()->env = parse_envp(envp);
}

t_minishell	*data(void)
{
	static t_minishell	data;

	return (&data);
}
