
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