/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:04:25 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 08:04:31 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	int	i;

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
	size_t			i;

	i = 0;
	aux = (unsigned char *)malloc(size);
	if (!aux)
		return (NULL);
	while (i < size)
	{
		aux[i] = 0;
		i++;
	}
	return ((void *)aux);
}
