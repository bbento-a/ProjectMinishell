/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:41:50 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 07:41:52 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_handler(int sig)
{
	data()->exit_code = 128 + sig;
}

void	child_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = &child_handler;
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = &child_handler;
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
