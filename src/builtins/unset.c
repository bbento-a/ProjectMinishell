/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:38:32 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 08:16:07 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_node(t_env *env)
{
	t_env	*tmp;

	if (data()->env == env && env->next == NULL)
	{
		ft_memdel((void **)&data()->env->value);
		data()->env->value = NULL;
		data()->env->next = NULL;
		free(env);
		return ;
	}
	ft_memdel((void **)&env->value);
	tmp = env->next;
	free(env);
	if (env == data()->env)
		data()->env = tmp;
}

int	ms_unset(char **cmd)
{
	t_env	*env;
	t_env	*prev;

	prev = NULL;
	while (*++cmd)
	{
		env = data()->env;
		while (env)
		{
			if (ft_strncmp(env->value, *cmd, ft_strlen(*cmd)) == 0)
			{
				if (!prev)
					data()->env = env->next;
				else
					prev->next = env->next;
				free_node(env);
				break ;
			}
			prev = env;
			env = env->next;
		}
	}
	return (0);
}
