/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:07:49 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/09 11:35:21 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_hex(unsigned long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static char	*hex_to_str(unsigned long n, char *base)
{
	int		size;
	char	*hex;

	size = count_hex(n);
	hex = (char *)malloc(sizeof(char) * (size + 3));
	if (!hex)
		return (NULL);
	hex[size + 2] = '\0';
	hex[0] = '0';
	hex[1] = 'x';
	while (size > 0)
	{
		hex[size + 1] = base[n % 16];
		n = n / 16;
		size--;
	}
	return (hex);
}

int	ft_put_pointer(void *nbr, char *base)
{
	int				len;
	char			*str;

	if (nbr == 0)
		return (ft_putstr("(nil)"));
	str = hex_to_str((unsigned long)nbr, base);
	len = ft_putstr(str);
	free(str);
	return (len);
}
