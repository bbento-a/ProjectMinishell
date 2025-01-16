/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferferre <ferferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:33:12 by bbento-a          #+#    #+#             */
/*   Updated: 2024/11/29 16:22:23 by ferferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n > i && s1[i] && s2[i] && s2[i] == s1[i])
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main(void)
{
	const char	*str1 = "Hello";
	const char	*str2 = "H";

	printf("%d\n", ft_strncmp(str1, str2, 2));
	printf("%d\n", strncmp(str1, str2, 4));
	return (0);
}
*/
