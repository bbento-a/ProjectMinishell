/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:49:36 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 02:49:57 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	*my_malloc(size_t size)
{
	unsigned char	*aux;
	size_t			 i;

	i = 0;
	aux = (unsigned char *)malloc(size);
	if(!aux)
		return(NULL);
	while(i < size)
	{
		aux[i] = 0;
		i++;
	}
	return((void *)aux);
}