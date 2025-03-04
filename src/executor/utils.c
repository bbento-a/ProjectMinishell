/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:24 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/04 15:32:50 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*env_to_str(t_env *env)
{
	char	*str;
	size_t	len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len += ft_strlen(tmp->value) + 1;
		tmp = tmp->next;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (env)
	{
		ft_strlcat(str, env->value, len + 1);
		ft_strlcat(str, "\n", len + 1);
		env = env->next;
	}
	return (str);
}

void	free_tab(char **array)
{
	if (!array)
		return ;
	free(array); // Only free the array container, not the strings
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->str);
		free(token);
		token = tmp;
	}
}

int	handle_error(char *path, DIR *folder, int fd)
{
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		return (UNKNOWN_COMMAND);
	return (IS_DIRECTORY);
}