/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:26:06 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/17 12:58:16 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = 0;
	while (s2[j] != '\0')
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*second_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	ft_strcpy(s, (char *)s1);
	ft_strcat(s, (char *)s2);
	return (s);
}
/*
{
    size_t len;
    char *s;

    // Check if either of the input strings is NULL
    if (!s1 || !s2)
        return (NULL);

    // Calculate the total length of the new string
    len = ft_strlen(s1) + ft_strlen(s2);

    // Allocate memory for the new string
    s = (char *)malloc(sizeof(char) * (len + 1));

    // Check if memory allocation was successful
    if (s == NULL)
        return (NULL);

    // Copy the content of s1 into the new string 's'
    ft_strcpy(s, (char *)s1);

    // Concatenate the content of s2 to the end of the new string 's'
    ft_strcat(s, (char *)s2);

    // Return the pointer to the new concatenated string
    return (s);
} */
