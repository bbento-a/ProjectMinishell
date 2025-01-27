/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:18:03 by mde-maga          #+#    #+#             */
/*   Updated: 2024/08/26 12:49:54 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*point;

	i = 0;
	point = b;
	while (i < len)
	{
		point[i] = c;
		i++;
	}
	return (b);
}

/*  int main()
{
    char str[] = "Hello, World!";
    int value = 'X';
    size_t len = strlen(str);

    printf("Original string: %s\n", str);

    // Using ft_memset to replace characters in the string
    ft_memset(str, value, len);

    printf("Modified string: %s\n", str);

    return 0;
}  */