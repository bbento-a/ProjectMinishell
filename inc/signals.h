/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:13:10 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 08:24:38 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <termios.h>
# include <signal.h>

int		check_input(char *line);
void	environment_signals(void);
void	child_signals(void);
void	heredoc_signals(void);
void	disable_signals(void);

#endif