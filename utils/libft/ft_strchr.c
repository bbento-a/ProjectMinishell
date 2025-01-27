/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:05 by mde-maga          #+#    #+#             */
/*   Updated: 2023/10/03 17:26:54 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	value;
	char	*str;

	i = 0;
	value = (char)c;
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == value)
			return (&str[i]);
		i++;
	}
	if (value == '\0')
		return (&str[i]);
	return (NULL);
}
