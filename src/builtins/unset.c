/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:38:32 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 04:41:04 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_node(t_env *env)
{
	t_env	*tmp;

	// If it's the only node in the list
	if (data()->env == env && env->next == NULL)
	{
		ft_memdel((void **)&data()->env->value);
		// Pass the address of the pointer
		data()->env->value = NULL;
		data()->env->next = NULL;
		free(env);
		return ;
	}
	// If it's not the first node, free and adjust links
	ft_memdel((void **)&env->value); // Pass the address of the pointer
	tmp = env->next;
	free(env);
	if (env == data()->env)
		data()->env = tmp; // Adjust the head of the list if needed
}

int	ms_unset(char **cmd)
{
	t_env	*env;
	t_env	*prev;

	prev = NULL;
	while (*++cmd) // Iterate through each argument (environment variable to unset)
	{
		env = data()->env;
		while (env) // Traverse the environment linked list
		{
			// If we find the matching variable, we delete it
			if (ft_strncmp(env->value, *cmd, ft_strlen(*cmd)) == 0)
			{
				// If previous is null, we're deleting the first node
				if (!prev) // Update head if it's the first node
					data()->env = env->next;
				else // If not, just link previous to the next node
					prev->next = env->next;
				free_node(env); // Free the node
				break ;          // Stop searching as we found and deleted it
			}
			prev = env;
			env = env->next;
		}
	}
	return (0);
}
