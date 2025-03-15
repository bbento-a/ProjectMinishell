/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 08:22:47 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 08:22:55 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static long	ft_atol(char *n)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((n[i] >= 9 && n[i] <= 13) || n[i] == 32)
		i++;
	if (n[i] == '-' || n[i] == '+')
	{
		if (n[i] == '-')
			sign *= -1;
		i++;
	}
	while (n[i] >= '0' && n[i] <= '9')
	{
		res = res * 10 + (n[i] - '0');
		i++;
	}
	return (res * sign);
}

static int	check_valid_signumber(char *str, int i, int j)
{
	char	*lng_min;
	char	*lngs_max;

	lng_min = "-9223372036854775808";
	lngs_max = "+9223372036854775807";
	if (str[i] == '+')
	{
		while (lngs_max[j] && str[i])
		{
			if (str[i] > lngs_max[j++])
				return (1);
			i++;
		}
	}
	else if (str[i] == '-')
	{
		while (lng_min[j] && str[i])
		{
			if (str[i] > lng_min[j++])
				return (1);
			i++;
		}
	}
	return (0);
}

static int	check_valid_number(char *str, int spc, int j)
{
	char	*lng_max;
	int		i;

	lng_max = "9223372036854775807";
	i = 0;
	while (str[i] == 32)
		i++;
	if (ft_strlen(str) - spc == 19)
	{
		if (str[i] == '+' || str[i] == '-')
			return (0);
		while (lng_max[j] && str[i])
		{
			if (str[i] > lng_max[j])
				return (display_err("exit: ", NULL,
						"numeric argument is too large", 1));
			i++;
			j++;
		}
	}
	if (check_valid_signumber(str, i, j))
		return (display_err("exit: ", NULL, "numeric argument is too large",
				1));
	return (0);
}

static int	check_exit_arg(char *str)
{
	int	spaces;
	int	i;

	i = 0;
	spaces = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
		spaces++;
	}
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (display_err("exit: ", NULL, "numeric argument is required", 2));
	if (ft_strlen(str) - spaces > 20)
		return (display_err("exit: ", NULL, "numeric argument is too large",
				1));
	if (ft_strlen(str) - spaces <= 18)
		return (0);
	if (check_valid_number(str, spaces, 0))
		return (1);
	return (0);
}

int	builtin_exit(char **args)
{
	long	exit_code;

	exit_code = 0;
	if (args[1])
	{
		if (!check_exit_arg(args[1]))
		{
			exit_code = ft_atol(args[1]);
			if (exit_code > 255)
				data()->exit_code = exit_code % 256;
			else
				data()->exit_code = (int)exit_code;
			if (args[2])
				return (display_err("exit: ", NULL, "too many arguments", 1));
		}
	}
	ft_printf("exit\n");
	clear_memory(data()->cmds);
	clear_env(data()->env);
	exit(data()->exit_code);
}
