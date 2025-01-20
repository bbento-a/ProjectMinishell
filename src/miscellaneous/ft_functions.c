
#include "../inc/minishell.h"

int	ft_close(int *fd)
{
	int	close_return;

	close_return = 0;
	if (*fd > 2)
	{
		close_return = close(*fd);
		*fd = -1;
	}
	return (close_return);
}
// Compares a char c to a str of other chars
// (if it finds c in *sign, it returns true)

bool	symbol_cmp(char *sign, char c)
{
	int	i;

	i = -1;
	while (sign[++i])
	{
		if (sign[i] == c)
			return (true);
	}
	return (false);
}

// Sizes an 2d array

int	ft_mtxlen(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		i++;
	return (i);
}

void	ft_freemtx(char **mtx)
{
	int		i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
	mtx = NULL;
	return ;
}
