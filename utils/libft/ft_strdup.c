/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:41:56 by mde-maga          #+#    #+#             */
/*   Updated: 2023/10/04 16:09:27 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*c;

	len = ft_strlen(s);
	c = (char *)malloc(len + 1);
	if (c == NULL)
		return (NULL);
	ft_memcpy(c, s, len);
	c[len] = '\0';
	return (c);
}
