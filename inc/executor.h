
#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "builtins.h"

int	check_and_execute(t_command *commands);
int	check_redirections(t_command *cmds);


#endif