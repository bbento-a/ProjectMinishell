
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_command *command);
}	t_builtin;

#endif