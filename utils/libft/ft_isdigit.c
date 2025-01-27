/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:13:49 by mde-maga          #+#    #+#             */
/*   Updated: 2023/10/03 15:37:08 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (('0' <= c) && ('9' >= c));
}

/* int main(void)
{
    printf("%d\n", ft_isdigit('a'));
    printf("%d\n", ft_isdigit('2'));
    printf("%d\n", ft_isdigit ('0'));
	printf("%d\n", ft_isdigit(' '));

    return 0;
} */