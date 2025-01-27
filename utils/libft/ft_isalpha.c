/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:24:24 by mde-maga          #+#    #+#             */
/*   Updated: 2024/08/26 12:50:13 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((('a' <= c) && ('z' >= c)) || (('A' <= c) && ('Z' >= c)))
		return (1);
	return (0);
}

/* int main(void)
{
    printf("%d\n", ft_isalpha('a'));
    printf("%d\n", ft_isalpha('A'));
    printf("%d\n", ft_isalpha('0'));
	printf("%d\n", ft_isalpha(' '));

    return 0;
}  */