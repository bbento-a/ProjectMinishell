/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:04:58 by mde-maga          #+#    #+#             */
/*   Updated: 2023/10/03 15:24:11 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (size == 0)
		return (ft_strlen(src));
	if (j > size -1)
		return (size + ft_strlen(src));
	while (src[i] != '\0' && i + j < size -1)
	{
		dst[i + j] = src [i];
		i++;
	}
	dst[i + j] = '\0';
	return (j + ft_strlen(src));
}
/* int main() {
    char destination[20] = "im gonna, ";
    const char *source = "kms :3!";
    size_t size = sizeof(destination);

    size_t result = ft_strlcat(destination, source, size);

    printf("Concatenated string: %s\n", destination);
    printf("Return value: %zu\n", result);

    return 0;
} */