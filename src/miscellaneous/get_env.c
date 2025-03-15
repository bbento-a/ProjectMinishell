/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:49:40 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 02:49:41 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env(char *var)
{
	t_env	*envp;
	char	*tmp;

	envp = data()->env;
	while(envp)
	{
		if (ft_strncmp(envp->value, var, ft_strlen(var)) == 0) // envp var name needs a size cmp before this condition
		{
			tmp = ft_strchr(envp->value, '=');
			if (!tmp || ft_strlen(envp->value) - ft_strlen(tmp) != ft_strlen(var))
				break ;
			tmp++;
			return (tmp);
		}
		envp = envp->next;
	}
	return (NULL);
}
