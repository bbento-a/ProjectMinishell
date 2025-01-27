/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:14:24 by mde-maga          #+#    #+#             */
/*   Updated: 2024/08/26 12:50:06 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (((('a' <= c) && ('z' >= c)) || (('A' <= c) && ('Z' >= c)))
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*  int main(void)
{
    printf("%d\n", ft_isalnum('a'));
    printf("%d\n", ft_isalnum('2'));
    printf("%d\n", ft_isalnum('0'));
	printf("%d\n", ft_isalnum(' '));
	printf("%d\n", ft_isalnum('W'));
	printf("%d\n", ft_isalnum('d'));

    return 0;
}  */