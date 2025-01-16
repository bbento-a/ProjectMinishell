
#include "../minishell.h"

// This function returns the number of arguments that will be given
// to a command, ignoring files names (everything that is followed
// by a redirection)

int	handle_node_args(t_line *bgn, t_line *last)
{
	int	nb;

	nb = 0;
	while (bgn != last->next)
	{
		if (bgn->type_n < E_PIPE)
			bgn = bgn->next;
		else if (bgn->type_n != E_PIPE)
		{
			nb++;
			bgn->arg = true;
		}
		if (bgn == last)
			break ;
		bgn = bgn->next;
	}
	return (nb);
}

// Attributes arguments to the array of the command node and closes
// it with a NULL pointer. This happens because the execve must receive
// arrays of arguments that ends with NULL pointer

void	make_cmd_args(char **args, t_line *bgn, t_line *last, int size)
{
	int	i;

	i = 0;
	(void)last;
	while (i < size && bgn != last->next)
	{
		if (bgn->arg == true)
		{
			args[i] = ft_strdup(bgn->content);
			i++;
		}
		bgn = bgn->next;
	}
	args[size] = NULL;
}
