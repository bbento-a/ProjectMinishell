/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:57 by mde-maga          #+#    #+#             */
/*   Updated: 2023/10/03 17:27:12 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	value;
	char	*str;

	i = ft_strlen(s);
	value = (char)c;
	str = (char *)s;
	while (i >= 0)
	{
		if (str[i] == value)
			return (&str[i]);
		i--;
	}
	if (value == '\0')
		return (&str[i]);
	return (NULL);
}
