/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:53:31 by mde-maga          #+#    #+#             */
/*   Updated: 2023/10/04 11:36:15 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*l;

	i = 0;
	b = (char *)big;
	l = (char *)little;
	if (l[0] == '\0')
		return (b);
	while (b[i] != '\0' && i < len)
	{
		j = 0;
		while (b[i + j] != '\0' && i + j < len && b[i + j] == l[j])
		{
			if (l[j + 1] == '\0')
				return (&b[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
