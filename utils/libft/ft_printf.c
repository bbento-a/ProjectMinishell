/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:52:34 by mde-maga          #+#    #+#             */
/*   Updated: 2024/09/09 11:35:21 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			ret += ft_arguments(format, i, ap);
			i++;
		}
		else
			ret += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (ret);
}
/* int main() {
    char character = 'L';
    char* string = "ok dude... what the flip";
    void* pointer = (void*)0x7fff12345678;
    int decimal_integer = -42;
    unsigned int unsigned_integer = 42;
    int hexadecimal_integer = 0x1A3F;
    int uppercase_hexadecimal = 0xabcd;

    ft_printf("O Character: %c\n", character);
    ft_printf("O String: %s\n", string);
    ft_printf("O Pointer: %p\n", pointer);
    ft_printf("O Decimal Integer: %d\n", decimal_integer);
    ft_printf("O Another Decimal Integer: %i\n", decimal_integer);
    ft_printf("O Unsigned Integer: %u\n", unsigned_integer);
    ft_printf("O Hexadecimal Integer: %x\n", hexadecimal_integer);
    ft_printf("O Uppercase Hexadecimal Integer: %X\n", uppercase_hexadecimal);
    ft_printf("O Percent Sign: %%\n\n");

	printf("X Character: %c\n", character);
    printf("X String: %s\n", string);
    printf("X Pointer: %p\n", pointer);
    printf("X Decimal Integer: %d\n", decimal_integer);
    printf("X Another Decimal Integer: %i\n", decimal_integer);
    printf("X Unsigned Integer: %u\n", unsigned_integer);
    printf("X Hexadecimal Integer: %x\n", hexadecimal_integer);
    printf("X Uppercase Hexadecimal Integer: %X\n", uppercase_hexadecimal);
    printf("X Percent Sign: %%\n");

    return 0;
} */