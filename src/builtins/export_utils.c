/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:25:52 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/23 17:31:53 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_error(char *arg)
{
	ft_putstr_fd("export: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": not a valid identifier", STDERR);
	ft_putstr_fd("\n", STDERR);
	data()->exit_code = 1;
	return (ERROR);
}

size_t	ft_strlen_equal(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	append_new_env(t_env *env, const char *name, const char *value)
{
	t_env	*tmp;
	char	*new_value;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = my_malloc(sizeof(t_env));
	if (!tmp->next)
		return (display_err(NULL, NULL, "Failed to allocate memory", -1));
	if (value)
		tmp->next->value = ft_strjoin(name, "=");
	else
		tmp->next->value = ft_strdup(name);
	if (value)
	{
		new_value = tmp->next->value;
		tmp->next->value = ft_strjoin(new_value, value);
		free(new_value);
	}
	tmp->next->next = NULL;
	return (SUCCESS);
}
